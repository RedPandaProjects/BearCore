#pragma once
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <typeinfo>
#include <math.h>
#include <cmath>

#include "BearTypes.h"


#ifdef BEAR_CORE_EXPORTS
#define BEARTOOL_API  BEARPROJECT_EXPORT
#else
#define BEARTOOL_API  BEARPROJECT_IMPORT
#endif

#include "BearTemplate/BearUtilsForClass.h"

#include "BearMemory/BearMemory.h"
#include "BearMemory/BearMemoryAllocator.h"
#include "BearMemory/BearMemoryTemplate.h"
#include "BearMemory/BearMemoryMultiRef.h"
#include "BearMemory/BearMemoryRef.h"

#include "BearTemplate/BearDefines.h"


#include "BearTemplate/BearFunctional.h"
#include "BearTemplate/BearAlgorithm.h"

#include "BearTemplate/BearVector.h"
#include "BearTemplate/BearMap.h"


#include "BearDebug/BearDebug.h"
#include "BearDebug/BearDebugDefines.h"
#include "BearDebug/BearLog.h"



	class BEARTOOL_API BearCore
	{
		BEAR_CLASS_STATIC(BearCore);
	public:
		 void Initialize(const bchar*App);
		 void Destroy();
	};
