///////////////////////////////////////////////////////////////////////////////////
//-------------------------------------Main.cpp----------------------------------//
//                                      v 1.0                                    //
//                                                                               //
// This file controls the main game logic.																			 //
//                                                                               //
// Developers: Zerotri                                                       		 //
// Created on: 4.12.2007                                                         //
//                                                                               //
//--------------------------------------Notes------------------------------------//
//                                                                               //
//																																							 //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////
//							Includes				 		 //
///////////////////////////////////////
#include "main.h"


///////////////////////////////////////
//			Function Declarations				 //
///////////////////////////////////////
CEvent ProcessEvents(SDL_Event event);

///////////////////////////////////////
//		Global Variable Declarations	 //
///////////////////////////////////////

necropolis::CLog* Log;
necropolis::CGlobal* Global;
necropolis::CVideo* Video;
necropolis::CScriptManager* ScriptManager;
necropolis::CObjectCollector* ObjCollector;
necropolis::CTextureManager* TexMan;

///////////////////////////////////////
//	Function: main									 //
//	Arguments:											 //
//		[int argc]										 //
//			-number of program arguments //
//		[char** argv]									 //
//			-string array containing the //
//			 program's arguments				 //
//	Returns: Error code(zero if none)//
///////////////////////////////////////
int main ( int argc, char** argv )
{
    //Setup Main Class Objects
    //CLog allows the developer to write debug information
    //into a nice clean console window that can be disabled
    //by changing to release mode
    Log  					= new necropolis::CLog;
    //CGlobal allows the developer to create a set of variables
    //into a single class that is meant to be a container(of
    //sorts)
    Global 				= new necropolis::CGlobal;
    //CScriptManager gives application control to the
    //AngelScript scripting language
    ScriptManager = new necropolis::CScriptManager;
    //CVideo is used to Initialize the SDL window and also
    Video 				= new necropolis::CVideo;
    ObjCollector 	= new necropolis::CObjectCollector;
    TexMan 				= new necropolis::CTextureManager;

    //and Initialize whatever ones need to e initialized
    Video->Initialize();
    ScriptManager->Initialize();

    //define and compile the two scripts that will run
    ScriptManager->CompileScriptFromFile(T("script1.as"));
    ScriptManager->CompileScriptFromFile(T("script2.as"));

    // create a new window

    // program main loop
    Global->setRunning(true);
		SDL_Event event;
		Global->framesPerSecond = 0;
		Global->resetFPS();
    while (Global->isRunning())
    {
				Global->tickFPS();
        ScriptManager->ExecuteScripts();
        // message processing loop
				while (SDL_PollEvent(&event))
				{
					CEvent evt = ProcessEvents(event);
					switch(evt.EventType){
						case CEvent::EVT_WINDOWCLOSE:
							Global->setRunning(false);
							break;
						case CEvent::EVT_KEYPRESS:
							if(evt.data.keyPress.key == SDLK_ESCAPE)
								Global->setRunning(false);
							break;
					}
				}
        // clear screen
        SDL_Surface* screen = Video->getScreen();
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        //Draw All objects
        std::vector<necropolis::CObject*>::iterator it = ObjCollector->mObjectList.begin();
        for(;it != ObjCollector->mObjectList.end(); it++)
        {
          TexMan->DrawTexture((*it)->_surface,(*it)->physics.x,(*it)->physics.y,screen);
        }
        // finally, update the screen :)
        SDL_Flip(screen);
				Global->framesPerSecond++;
    } // end main loop
    // all is well ;)
    SDL_Quit();
    Log->dbgOut( NULL, NULL, "Exited cleanly");
    return 0;
}
///////////////////////////////////////
//	Function: ProcessEvents					 //
//	Arguments:											 //
//		[SDL_Event event]							 //
//			-the SDL_Event that needs to //
//			 be parsed into a nice CEvent//
//	Returns: CEvent object containing//
//				the most recently processed//
//				events in a nice wrapper	 //
///////////////////////////////////////
CEvent ProcessEvents(SDL_Event event)
{
	CEvent t_evt;
			// check for messages
			switch (event.type)
			{
					// exit if the window is closed
			case SDL_QUIT:
							t_evt.EventType = CEvent::EVT_WINDOWCLOSE;
							return t_evt;
							break;

					// check for keypresses
			case SDL_KEYDOWN:
					{
							t_evt.EventType = CEvent::EVT_KEYPRESS;
							t_evt.data.keyPress.key = event.key.keysym.sym;
							return t_evt;
							break;
					}
			case SDL_KEYUP:
					{
							t_evt.EventType = CEvent::EVT_KEYRELEASE;
							t_evt.data.keyRelease.key = event.key.keysym.sym;
							return t_evt;
							break;
					}
			case SDL_MOUSEBUTTONDOWN:
					{
							t_evt.EventType = CEvent::EVT_MOUSEPRESS;
							t_evt.data.mousePress.button = event.button.button;
							t_evt.data.mousePress.x = event.button.x;
							t_evt.data.mousePress.y = event.button.y;
							return t_evt;
							break;
					}
			case SDL_MOUSEBUTTONUP:
					{
							t_evt.EventType = CEvent::EVT_MOUSERELEASE;
							t_evt.data.mouseRelease.button = event.button.button;
							t_evt.data.mouseRelease.x = event.button.x;
							t_evt.data.mouseRelease.y = event.button.y;
							return t_evt;
							break;
					}
			default:
					break;
			} // end switch
}
