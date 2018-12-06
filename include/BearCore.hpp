#pragma once
#ifdef WINDOWS
#include "BearPlatform/Windows/BearWindowsType.h"
#include "BearPlatform/Windows/BearProjectsDefines.h"
#elif LINUX
#else
#error BearCore на данной платформе не поддерживается
#endif

#ifdef BEAR_CORE_EXPORTS
#define BEARTOOL_API  BEARPROJECT_EXPORT
#else
#define BEARTOOL_API  BEARPROJECT_IMPORT
#endif

#include <stdio.h>
#include <string.h>
#include <vector>
#include<map>
#include <typeinfo>

#include "BearTools/BearClass.h"
#include "BearMemory/BearMemory.h"
#include "BearMemory/BearMemoryTemplate.h"
#include "BearMemory/BearMemoryRef.h"
#include "BearMemory/BearMemoryAllocator.h"
#include "BearMemory/BearMemoryMultiRef.h"

#include "BearCoreInitializer.h"

#include "BearTemplate/BearAlgorithm.h"

#include "BearTools/BearString.h"

#include "BearTools/BearCheakSum.h"

#include "BearTools/BearStringConteniar.h"

#include "BearDebug/BearDebug.h"

#include "BearDebug/BearDebugDefines.h"

#include "BearTemplate/BearFunctional.h"

#include "BearTools/BearFlags.h"

#include "BearTools/BearVector.h"

#include "BearTools/BearVector2.h"
#include "BearTools/BearVector3.h"
#include "BearTools/BearVector4.h"

#include "BearTools/BearMap.h"

#include "BearDebug/BearLog.h"

#include "BearTools/BearEncoding.h"

#include "BearIO/BearStreamRef.h"
#include "BearIO/BearInputStream.h"
#include "BearIO/BearOutputStream.h"
#include "BearIO/BearBufferedReader.h"
#include "BearIO/BearFileStream.h"
#include "BearIO/BearMemoryStream.h"
#include "BearIO/BearMemoryTranslationStream.h"

#include "BearIO/BearFileManager.h"

#include "BearProjects/BearProjectTool.h"

#include "BearTools/BearDefines.h"

#include "BearTools/BearFraction.h"

#include "BearTools/BearMatrix.h"
#include "BearTools/BearColor.h"

#include "BearTools/BearTime.h"
#include "BearTime/BearTimer.h"

#include "BearParser/BearXML.h"
#include "BearTools/BearIncluder.h"
#include "BearParser/BearINI.h"

#include "BearIO/BearFileSystem.h"

#include "BearTemplate/BearMultiplicatorDefine.h"
#include "BearTemplate/BearFunctionReflector.h"

#include "BearTools/BearThread.h"
#include "BearTools/BearMutex.h"
