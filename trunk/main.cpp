#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <fstream>
#include <string>
#include <iterator>
#include <SDL.h>
#include "CLog.h"
#include "CGlobal.h"
#include "CObjectCollector.h"
#include "CObject.h"
#include "CScriptManager.h"

necropolis::CLog* gLog;
necropolis::CGlobal* gGlobal;
necropolis::CObjectCollector* gObjCollector;
necropolis::CScriptManager* gScriptManager;

int main ( int argc, char** argv )
{
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
    int obj = gObjCollector->NewObject(necropolis::CObject(0,0));
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

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

        // draw bitmap
        SDL_BlitSurface(bmp, 0, screen, &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
