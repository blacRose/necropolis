#ifndef COBJECT_H
#define COBJECT_H
#include "CTextureManager.h"
#include "CScriptManager.h"
extern necropolis::CTextureManager* TexMan;

namespace necropolis{
		typedef unsigned int objectRef_t;
		class CObject{

			private:
				objectRef_t _instance;

			public:
				///the physics struct contains all information related to
				///the objects location, speed, and direction

				struct{
						int x;
						int y;
						int hspeed;
						int vspeed;
						int direction;
					}physics;
				///this is a texture reference
				textureRef_t _surface;
				std::string _tag;
				SContextInfo* _ctx;
				CObject()
				{
					physics.x = 0;
					physics.y = 0;
				};

				void Constructor ( CObject *obj )
				{
					obj = new CObject();
					obj->physics.x = 0;
					obj->physics.y = 0;
					obj->_tag = "";
					obj->_surface = 0;
					DBGOUT("CObject","Constructor","New object: %i");
				};

				void Destructor ( CObject *obj )
				{
					obj->~CObject();
					obj = 0;
				}

				void Update ( CObject *obj )
				{
					//CScriptManager::();
					//obj->_surface->clip_rect.x = obj->physics.x;
					//obj->_surface->clip_rect.y = obj->physics.y;
				}

				int setSprite ( std::string fname )
				{
					if ( !_surface )
						{
							_surface = TexMan->LoadTexture ( fname.c_str() );
						}else{
							_surface = TexMan->LoadTexture ( fname.c_str() );
						}

					if ( !_surface )
						{
							return false;
						}else{
							return true;
						}
				}

				virtual ~CObject() {};

				virtual void setInstance ( int a_inst ) {};
			};
	}

#endif
