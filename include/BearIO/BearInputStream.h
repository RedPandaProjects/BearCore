#pragma once
namespace BearCore
{
	class BEARTOOL_API BearInputStream
	{
	public:
		uint8 ReadUint8()const;
		uint16 ReadUint16()const;
		uint32 ReadUint32()const;
		uint64 ReadUint64()const;
		
		int8 ReadInt8()const;
		int16 ReadInt16()const;
		int32 ReadInt32()const;
		int64 ReadInt64()const;
		
		float ReadFloat()const;
		double ReadDouble()const;
		
		bsize Read(void*data, bsize size)const;
		BearMemoryRef<uint8>Read()const;
		BearMemoryRef<uint8>Read(bsize size)const;

		void ReadString(BearString&str)const;
	
		void ReadString(BearString&str, bsize size, BearEncoding::Encoding encoding)const;
		void ToString(BearString&str, BearEncoding::Encoding encoding)const;
		
		bsize GoToChunk(uint32 type)const;
		
		virtual BearStreamRef<BearInputStream> ReadChunkAsInputStream(uint32 type)const = 0;
		
		virtual bool Eof() const = 0;
		
		virtual  void read_impl(void*data, bsize size)const = 0;
		virtual bsize Seek(bsize tell) const = 0;
		virtual bsize Tell()const = 0;
		virtual bsize Size()const = 0;
		virtual void Destory() = 0;
	};
};