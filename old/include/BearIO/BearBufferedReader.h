#pragma once
namespace BearCore
{
	class BEARTOOL_API BearBufferedReader:public BearInputStream
	{
	public:
		virtual const void*begin()const = 0;
		virtual void*begin() = 0;
		virtual const void*end()const=0;
		virtual void*end()=0;
		void readStringToLine(BearString&str, Encoding::Encoding encoding)const;
		virtual BearStreamPtr<BearBufferedReader> readChunkAsBufferedReader(uint32 type)const = 0;
		void readStringToZero(BearString&str, Encoding::Encoding encoding)const;
		virtual BearStreamPtr<BearInputStream> readChunkAsInputStream(uint32 type)const;

	};
}