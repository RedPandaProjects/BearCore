#pragma once
namespace BearCore
{
	class BEARTOOL_API BearInputStream
	{
	public:
		uint8 readUint8()const;
		uint16 readUint16()const;
		uint32 readUint32()const;
		uint64 readUint64()const;
		
		int8 readInt8()const;
		int16 readInt16()const;
		int32 readInt32()const;
		int64 readInt64()const;
		
		float readFloat()const;
		double readDouble()const;
		
		bsize read(void*data, bsize size)const;
		BearMemoryRef<uint8>read()const;
		BearMemoryRef<uint8>read(bsize size)const;

		void readString(BearString&str)const;
	
		void readString(BearString&str, bsize size, BearEncoding::Encoding encoding)const;
		void toString(BearString&str, BearEncoding::Encoding encoding)const;
		
		bsize goToChunk(uint32 type)const;
		
		virtual BearStreamRef<BearInputStream> readChunkAsInputStream(uint32 type)const = 0;
		
		virtual bool eof() const = 0;
		
		virtual  void read_impl(void*data, bsize size)const = 0;
		virtual bsize seek(bsize tell) const = 0;
		virtual bsize tell()const = 0;
		virtual bsize size()const = 0;
		virtual void destory() = 0;
	};
};