#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <fstream>
#include <string>
#include <iterator>
#include <SDL.h>
#include <sge.h>
#include "CLog.h"
#include "CGlobal.h"
#include "CObjectCollector.h"
#include "CObject.h"
#include "CScriptManager.h"
#include "CTextureManager.h"

std::vector<SDL_Surface*> mTextureList;
necropolis::CLog* gLog;
necropolis::CGlobal* gGlobal;
necropolis::CObjectCollector* gObjCollector;
necropolis::CTextureManager* gTexMan = necropolis::CTextureManager::getInstance();
necropolis::CScriptManager* gScriptManager;

int main ( int argc, char** argv )
{

    mTextureList.reserve(32);
  // This script prints a message 3 times per second
    std::ifstream s_in1("script1.as");
    std::ifstream s_in2("script2.as");
    if (!s_in1)return false;
    if (!s_in2)return false;
    std::string script1 = std::string(std::istreambuf_iterator<char>(s_in1),
                                      std::istreambuf_iterator<char>());
    std::string script2 = std::string(std::istreambuf_iterator<char>(s_in2),
                                      std::istreambuf_iterator<char>());
    s_in1.close();
    s_in2.close();

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    gGlobal = necropolis::CGlobal::getInstance();
    gLog = necropolis::CLog::getInstance();
    gLog->dbgOut( "global", "main", "Hello World");
    gScriptManager = necropolis::CScriptManager::getInstance();
    std::string script1name = "script1";
    std::string script2name = "script2";
    gScriptManager->CompileScript(script1, script1name, script1name);
    gScriptManager->CompileScript(script2, script2name, script2name);
    int obj = gObjCollector->NewObject(necropolis::CObject());
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 24,
                                           SDL_SWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // program main loop
    bool done = false;
    while (!done)
    {
        gScriptManager->ExecuteScripts();
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        //Draw All objects
        std::vector<necropolis::CObject*>::iterator it = necropolis::CObjectCollector::mObjectList.begin();
        for(;it != necropolis::CObjectCollector::mObjectList.end(); it++)
        {
          gTexMan->DrawTexture((*it)->_surface,(*it)->physics.x,(*it)->physics.y,screen);
        }
        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
