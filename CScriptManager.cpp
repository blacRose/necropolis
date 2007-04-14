#include "CScriptManager.h"
#include "asScriptFunctions.h"
#include "CObject.h"
#include "CGlobal.h"
#include "scriptstring/scriptstring.h"
#include <algorithm>
extern necropolis::CGlobal* Global;
namespace necropolis
	{
		std::vector<SContextInfo> CScriptManager::contexts;
		void RegisterTypes ( asIScriptEngine *Engine );
		void RegisterGlobalFunctions ( asIScriptEngine *Engine );

		void MessageCallback ( const asSMessageInfo *msg, void *param )
		{
			///make use of the speed boost given by using
			///the ternary operator

			const char *type = ( msg->type == asMSGTYPE_WARNING ) ? type = "WARN"
												 : ( msg->type == asMSGTYPE_INFORMATION ) ? type = "INFO" : type = "ERR";

			DBGOUT( "AngelScript", "MessageCallback", "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message );
		}

		void CScriptManager::Initialize()
		{
			/// Create the script engine
			engine = asCreateScriptEngine ( ANGELSCRIPT_VERSION );

			if ( engine == 0 )
				{
					DBGOUT( "Script Manager", "Constructor", "%s", "Failed to create script engine." );
					return;
				}

			/// The script compiler will send any compiler messages to the callback function
			engine->SetMessageCallback ( asFUNCTION ( MessageCallback ), 0, asCALL_CDECL );

			/// Register the script string type
			/// Look at the implementation for this function for more information
			/// on how to register a custom string type, and other object types.
			/// The implementation is in "/add_on/scriptstring/scriptstring.cpp"
			RegisterScriptString ( engine );

			/// Register the functions that the scripts will be allowed to use
			RegisterTypes ( engine );

			RegisterGlobalFunctions ( engine );
		};

		int CScriptManager::CompileScript ( std::string &str, std::string &module, std::string &scriptname )
		{
			/// Build the two script into separate modules. This will make them have
			/// separate namespaces, which allows them to use the same name for functions
			/// and global variables.

			if ( engine->AddScriptSection ( module.c_str(), scriptname.c_str(),
																			str.c_str(), str.length(), 0, false ) < 0 )
				{
					DBGOUT( "Script Manager", "CompileScript", "%s", "AddScriptSection() failed." );
					return -1;
				}

			if ( engine->Build ( scriptname.c_str() ) < 0 )
				{
					DBGOUT( "Script Manager", "CompileScript", "%s", "Build() failed." );
					return -1;
				}

			AddContext ( engine->GetFunctionIDByDecl ( scriptname.c_str(), "void main()" ) );

			return 0;
		}
		int CScriptManager::CompileScriptFromFile(std::string fname)
		{
			CompileScriptFromFile(fname,fname,fname);
		}
		int CScriptManager::CompileScriptFromFile ( std::string &fname, std::string &module, std::string &scriptname )
		{
			std::ifstream s_in1 ( fname.c_str() );
			std::string str = std::string ( std::istreambuf_iterator<char> ( s_in1 ),
																			std::istreambuf_iterator<char>() );
			s_in1.close();
			/// Build the two script into separate modules. This will make them have
			/// separate namespaces, which allows them to use the same name for functions
			/// and global variables.

			if ( engine->AddScriptSection ( module.c_str(),	scriptname.c_str(),
																			str.c_str(), str.length(), 0, false ) < 0 )
				{
					DBGOUT( "Script Manager", "CompileScript", "%s", "AddScriptSection() failed." );
					return -1;
				}

			if ( engine->Build ( scriptname.c_str() ) < 0 )
				{
					DBGOUT( "Script Manager", "CompileScript", "%s", "Build() failed." );
					return -1;
				}

			AddContext ( engine->GetFunctionIDByDecl ( scriptname.c_str(), "void main()" ) );

			return 0;
		}

		void CScriptManager::ExecuteScripts()
		{
			/// Check if the system time is higher than the time set for the contexts
			UINT time = SDL_GetTicks();

			for ( iter = contexts.begin(); iter != contexts.end(); iter++ )
				{
					if ( ( iter->ctx ) && ( iter->sleepUntil < time ) )
						{
							if ( iter->ctx->Execute() != asEXECUTION_SUSPENDED )
								{
									iter->ctx->Release();
									iter->ctx = 0;
								}
						}
				}
		}

		/// Aborts a single script context (thread)
		void ContextAbort ( SContextInfo context )
		{
			if ( context.ctx )
				{
					context.ctx->Abort();
					context.ctx->Release();
					context.ctx = 0;
				}
		}

		/// Aborts ALL script contexts
		void CScriptManager::AbortAll()
		{
			/// Abort all contexts and release them. The script engine will make
			/// sure that all resources held by the scripts are properly released.
			std::for_each ( contexts.begin(), contexts.end(), ContextAbort );
		}

		void CScriptManager::AddContext ( int funcID )
		{
			/// Create the new context
			asIScriptContext *ctx = engine->CreateContext();

			if ( ctx == NULL )
				{
					DBGOUT( "Script Manager", "AddContext", "%s", "Failed to create context - \"%n\"", funcID );
					return;
				}

			/// Prepare it to execute the function
			if ( ctx->Prepare ( funcID ) < 0 )
				{
					DBGOUT( "Script Manager", "AddContext", "%s", "Failed to prepare the context - \"%n\"", funcID );
					return;
				}

			/// Add the context to the list for execution
			SContextInfo info = {0, ctx};
			contexts.push_back ( info );
		}

		void CScriptManager::SetSleeping ( asIScriptContext *ctx, UINT milliSeconds )
		{
			/// Find the context and update the timeStamp
			/// for when the context is to be continued
			std::vector<SContextInfo>::iterator curCtx;
			for (	curCtx = contexts.begin(); curCtx != contexts.end(); curCtx++ )
				{
					if ( curCtx->ctx == ctx )
						{
							curCtx->sleepUntil = SDL_GetTicks() + milliSeconds;
						}
				}
		}

		int cKey_Left = SDLK_LEFT;
		int cKey_Right = SDLK_RIGHT;
		int cKey_Up = SDLK_UP;
		int cKey_Down = SDLK_DOWN;
		void RegisterTypes ( asIScriptEngine *engine )
		{
			engine->RegisterObjectType (     "sprite_t",   sizeof ( textureRef_t ), asOBJ_PRIMITIVE );
			engine->RegisterObjectType (     "object_t",   sizeof ( objectRef_t	 ), asOBJ_PRIMITIVE );
			engine->RegisterObjectType (     "object_c",   sizeof ( CObject ), asOBJ_CLASS_CD );
			engine->RegisterObjectBehaviour( "object_c", asBEHAVE_CONSTRUCT,   "void f()",
																			 asMETHOD(CObject ,Constructor), asCALL_CDECL_OBJLAST);
			engine->RegisterObjectBehaviour( "object_c", asBEHAVE_DESTRUCT,    "void f()",
																			 asMETHOD(CObject ,Destructor), asCALL_CDECL_OBJLAST);
			engine->RegisterGlobalProperty ( "const int KEY_LEFT",   &cKey_Left );
			engine->RegisterGlobalProperty ( "const int KEY_RIGHT",  &cKey_Right );
			engine->RegisterGlobalProperty ( "const int KEY_UP",     &cKey_Up );
			engine->RegisterGlobalProperty ( "const int KEY_DOWN",   &cKey_Down );
			engine->RegisterGlobalProperty ( "const int	FPS  ", &Global->framesPerSecond );
		}

		///Registers all global functions used in the scripting language.
		///if the function library becomes too large, this function can
		///be branched off into several other functions that register
		///them by category.
		void RegisterGlobalFunctions ( asIScriptEngine *engine )
		{
			engine->RegisterGlobalFunction ( "void			WindowSetTitle  (string &in)", asFUNCTION ( as_WindowSetTitle ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "void			LoadScript  		(string &in)", asFUNCTION ( as_LoadScript ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "void			Print           (string &in)", asFUNCTION ( as_PrintString ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "void			Print           (int)", asFUNCTION ( as_PrintNumber ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "void			Sleep           (uint)", asFUNCTION ( as_ScriptSleep ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "bool			GetKeyPressed   (uint)", asFUNCTION ( as_GetKeyPressed ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "void			SetObjectTag    (object_t, string)", asFUNCTION ( as_SetObjectTag ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "string		GetObjectTag    (object_t)", asFUNCTION ( as_GetObjectTag ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "void			SetObjectX      (object_t, int)", asFUNCTION ( as_SetObjectX ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "int				GetObjectX      (object_t)", asFUNCTION ( as_GetObjectX ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "void			SetObjectY      (object_t, int)", asFUNCTION ( as_SetObjectY ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "int				GetObjectY      (object_t)", asFUNCTION ( as_GetObjectY ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "int				SetObjectSprite (object_t, string)", asFUNCTION ( as_SetObjectSprite ), asCALL_CDECL );
			engine->RegisterGlobalFunction ( "object_t	_object         (int, int)", asFUNCTION ( as_New_object ), asCALL_CDECL );
		}
	}
