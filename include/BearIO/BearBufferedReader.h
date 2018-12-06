#pragma once
namespace BearCore
{
	class BEARTOOL_API BearBufferedReader:public BearInputStream
	{
	public:
		virtual const void*Begin()const = 0;
		virtual void*Begin() = 0;
		virtual const void*End()const=0;
		virtual void*End()=0;
		void ReadStringToLine(BearString&str, BearEncoding::Encoding encoding)const;
		virtual BearStreamRef<BearBufferedReader> ReadChunkAsBufferedReader(uint32 type)const = 0;
		void ReadStringToZero(BearString&str, BearEncoding::Encoding encoding)const;
		virtual BearStreamRef<BearInputStream> ReadChunkAsInputStream(uint32 type)const;

	};
}