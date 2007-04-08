#include "main.h"

using namespace necropolis;
std::vector<SDL_Surface*> mTextureList;
necropolis::CLog* Log;
necropolis::CGlobal* Global;
necropolis::CVideo* Video;
necropolis::CScriptManager* ScriptManager;
necropolis::CObjectCollector* ObjCollector;
necropolis::CTextureManager* TexMan;
necropolis::CEventDirector* EvtDirector;
template <> CLog *Singleton<CLog>::my_singleton = 0;
template <> CGlobal *Singleton<CGlobal>::my_singleton = 0;
template <> CVideo *Singleton<CVideo>::my_singleton = 0;
template <> CScriptManager *Singleton<CScriptManager>::my_singleton = 0;
template <> CObjectCollector *Singleton<CObjectCollector>::my_singleton = 0;
template <> CTextureManager *Singleton<CTextureManager>::my_singleton = 0;
template <> CEventDirector *Singleton<CEventDirector>::my_singleton = 0;

int main ( int argc, char** argv )
{
    mTextureList.reserve(32);
    //Setup Singleton Objects
    Log = Singleton<necropolis::CLog>::getPtr();
    Global = Singleton<necropolis::CGlobal>::getPtr();
    ScriptManager = Singleton<necropolis::CScriptManager>::getPtr();
    Video = Singleton<necropolis::CVideo>::getPtr();
    ObjCollector = Singleton<necropolis::CObjectCollector>::getPtr();
    TexMan = Singleton<necropolis::CTextureManager>::getPtr();
    EvtDirector = Singleton<necropolis::CEventDirector>::getPtr();
    //and Initialize whatever ones need to e initialized
    Video->Initialize();
    ScriptManager->Initialize();
    //output a short diagnostic of the video hardware
    Log->dbgOut( NULL, NULL, "Hello World");
    Log->dbgOut( "global", "main", "Hello World");

    //define and compile the two scripts that will run
    std::string script1name = "script1.as";
    std::string script2name = "script2.as";
    ScriptManager->CompileScriptFromFile(script1name,script1name,script1name);
    ScriptManager->CompileScriptFromFile(script2name,script2name,script2name);
    //and create an object to test object collector
    int obj = ObjCollector->NewObject(necropolis::CObject());
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window

    // program main loop
    Global->setRunning(true);
    while (Global->isRunning())
    {
        ScriptManager->ExecuteScripts();
        // message processing loop
        EvtDirector->ProcessEvents();
        while(EvtDirector->eventOnStack())
        {
        	Global->ProcessEvent(EvtDirector->peekEvent());
        	EvtDirector->popEvent();
        }

        // clear screen
        SDL_Surface* screen = Video->getScreen();
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        //Draw All objects
        std::vector<necropolis::CObject*>::iterator it = necropolis::CObjectCollector::mObjectList.begin();
        for(;it != necropolis::CObjectCollector::mObjectList.end(); it++)
        {
          CTextureManager::DrawTexture((*it)->_surface,(*it)->physics.x,(*it)->physics.y,screen);
        }
        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop
    // all is well ;)
    Log->dbgOut( NULL, NULL, "Exited cleanly");
    return 0;
}
