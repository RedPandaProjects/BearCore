#pragma once
//#include "BearMyClass.h"
namespace BearCore
{

	class BEARTOOL_API BearIncluder
	{
		BEAR_CLASS_NO_COPY(BearIncluder);
	public:
		BearIncluder();
		virtual BearStreamRef<BearInputStream> OpenAsStream(const bchar*name);
		virtual BearStreamRef<BearBufferedReader> OpenAsBuffer(const bchar*name);
		~BearIncluder();
		
	};
	extern BEARTOOL_API BearIncluder GIncluderDefault;
}