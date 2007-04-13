#ifndef MAIN_H
#define MAIN_H
#ifndef NULL
  #define NULL 0
#endif

#define _SGE_NO_CLASSES
///SDL Includes
#include <SDL.h>
#include <SDL_syswm.h>
#include <SGE.h>
///STL Includes
#include <stdio.h>
#include <stdarg.h>
///ltimer
#include "ltimer.h"
///Engine Includes
#include "CGlobal.h"
#include "CObjectCollector.h"
#include "CObject.h"
#include "CScriptManager.h"
#include "CTextureManager.h"
#include "CEventDirector.h"
#include "CLog.h"
#include "CVideo.h"
#include "template_singleton.h"
#define	 T(x) std::string(x)
///Type Definitions
///Global Definitions
extern std::vector<SDL_Surface*> mTextureList;
extern necropolis::CLog* Log;
extern necropolis::CGlobal* Global;
extern necropolis::CVideo* Video;
extern necropolis::CScriptManager* ScriptManager;
extern necropolis::CObjectCollector* ObjCollector;
extern necropolis::CTextureManager* TexMan;
extern necropolis::CEventDirector* EvtDirector;

#endif
