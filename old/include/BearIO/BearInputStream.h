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
		BearPtr<uint8>read()const;
		BearPtr<uint8>read(bsize size)const;

		void readString(BearString&str)const;
	
		void readString(BearString&str, bsize size, Encoding::Encoding encoding)const;
		void toString(BearString&str, Encoding::Encoding encoding)const;
		
		bsize goToChunk(uint32 type)const;
		
		virtual BearStreamPtr<BearInputStream> readChunkAsInputStream(uint32 type)const = 0;
		
		virtual bool eof() const = 0;
		
		virtual  void read_impl(void*data, bsize size)const = 0;
		virtual int64 seek(bsize tell) const = 0;
		virtual int64 tell()const = 0;
		virtual int64 size()const = 0;
		virtual void destory() = 0;
	};
};