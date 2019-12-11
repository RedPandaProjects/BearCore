#pragma once
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <typeinfo>
#include <math.h>
#include <cmath>
#include <string>

#include "BearTypes.h"


#ifdef BEAR_CORE_EXPORTS
#define BEARTOOL_API  BEARPROJECT_EXPORT
#else
#define BEARTOOL_API  BEARPROJECT_IMPORT
#endif

#ifdef MSVC
#pragma warning(disable:4251 4100 4201 4200)
#endif


#include "BearTemplate/BearUtilsForClass.h"

#include "BearMemory/BearMemory.h"
#include "BearMemory/BearMemoryTemplate.h"
#include "BearMemory/BearMemoryAllocator.h"
#include "BearMemory/BearMemoryMultiRef.h"
#include "BearMemory/BearMemoryRef.h"

#include "BearTemplate/BearDefines.h"

#include "BearTemplate/BearFunctional.h"
#include "BearTemplate/BearAlgorithm.h"

#include "BearDebug/BearDebug.h"
#include "BearDebug/BearDebugDefines.h"

#include "BearTemplate/BearVector.h"
#include "BearTemplate/BearMap.h"

#include "BearTemplate/BearString.h"
#include "BearTemplate/BearStringConteniar.h"

#include "BearDebug/BearLog.h"

#include "BearUtils/BearEncoding.h"

#include "BearIO/BearInputStream.h"
#include "BearIO/BearBufferedReader.h"
#include "BearIO/BearOutputStream.h"

#include "BearUtils/BearFlags.h"

#include "BearIO/BearFileStream.h"
#include "BearIO/BearMemoryStream.h"

#include "BearIO/BearFileManager.h"

#include "BearIO/BearFilePackageStream.h"
#include "BearIO/BearPackage.h"

#include "BearUtils/BearIncluder.h"

#include "BearParser/BearINI.h"
#include "BearParser/BearXML.h"

#include "BearIO/BearFileSystem.h"

#include "BearMath/BearMath.h"

#include "BearMath/BearVector2.h"
#include "BearMath/BearVector3.h"
#include "BearMath/BearVector4.h"

#include "BearIO/BearInput.h"

#include "BearMath/BearColor.h"

#include "BearMath/BearFraction.h"

#include "BearMath/BearMatrix.h"
#include "BearMath/BearCamera.h"

#include "BearMath/BearTime.h"


#include "BearTemplate/BearMultiplicatorDefine.h"

#include "BearTemplate/BearFunctionReflector.h"

#include "BearUtils/BearCheakSum.h"

#include "BearUtils/BearCompressor.h"

#include "BearUtils/BearGlobalTime.h"
#include "BearUtils/BearTimer.h"


#include "BearUtils/BearThread.h"
#include "BearUtils/BearMutex.h"

#include "BearUtils/BearManagerProjects.h"

#include "BearUtils/BearSystem.h"

class BEARTOOL_API BearCore
{
	BEAR_CLASS_STATIC(BearCore);
public:
	static void Initialize(const bchar*App);
	static void Destroy();
};
