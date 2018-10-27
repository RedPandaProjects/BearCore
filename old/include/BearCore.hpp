/*
-----------------------------------------------------------------------
----Медвежий инструмент 1.0.0.0
----Автор:Соболевский Иван
----2015.07.XX
-----------------------------------------------------------------------`
*/
#pragma once

#ifdef WINDOWS
#include "BearPlatform/BearWindows.h" 
#elif LINUX
#include "BearPlatform/BearLinux.h"
#else
#error "Данная платформа не поддерживаеться!!!"
#endif
#include "BearMemory.h"
#include "BearDebug.h"
#include "BearTools/BearFunctional.h"
#include "BearTools/BearAlgorithm.h"
#include "BearTools/BearCheakSum.h"
#include "BearTools/BearStringEditor.h"
#include "BearTools/BearString.h"
#include "BearTools/BearVector.h"
#include "BearTools/BearMap.h"
#include "BearTools/BearFlags.h"
#include "BearIO/BearInputStream.h"
#include "BearIO/BearOutputStream.h"
#include "BearIO/BearBufferedReader.h"
#include "BearIO/BearMemoryStream.h"
#include "BearIO/BearMemoryTranslationStream.h"
#include "BearIO/BearFileManager.h"
#include "BearIO/BearFileStream.h"
//#include "BearScript/BearLua.h"