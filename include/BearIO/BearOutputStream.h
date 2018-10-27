#pragma once
namespace BearCore
{
	class BEARTOOL_API BearOutputStream
	{
	public:
		BearOutputStream();
		void writeUint8(uint8 data);
		void writeUint16(uint16 data);
		void writeUint32(uint32 data);
		void writeUint64(uint64 data);
		
		void writeInt8(int8 data);
		void writeInt16(int16 data);
		void writeInt32(int32 data);
		void writeInt64(int64 data);
		
		void writeFloat(float data);
		void writeDouble(double data);
		
		bsize write(void*data, bsize size);
		
		void beginChunk(int32 id);
		void endChunk(); 
		
		void writeString(const BearString&base,BearEncoding::Encoding encoding,bool info=true);
		void writeStringWithZero(const BearString&base, BearEncoding::Encoding encoding);
		void writeStringAndNewLine(const BearString &str, BearEncoding::Encoding encoding);
		
		virtual  bool write_impl(void*data, bsize &size) = 0;
		virtual bool eof() const=0;
		virtual bsize seek(bsize tell) const = 0;
		virtual bsize tell()const = 0;
		virtual bsize size()const = 0;
		virtual void destory() = 0;
	private:
		int64 m_tell_Chunk;

	};
};