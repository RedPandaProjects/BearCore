#include "BearCore.hpp"
#define WRITENUMBER write(&data,sizeof(data)); 
BearCore::BearOutputStream::BearOutputStream():m_tell_Chunk(-1)
{
}
void BearCore::BearOutputStream::writeUint8(uint8 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeUint16(uint16 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeUint32(uint32 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeUint64(uint64 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeInt8(int8 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeInt16(int16 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeInt32(int32 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeInt64(int64 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeFloat(float data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::writeDouble(double data)
{
	WRITENUMBER
}

bsize BearCore::BearOutputStream::write(void * data, bsize size)
{
	if (write_impl(data, size))
		return size;
	return 0;
}

void BearCore::BearOutputStream::beginChunk(int32 id)
{
	if (tell() < 0)return;
	writeInt32(id);
	m_tell_Chunk = tell();
	if (m_tell_Chunk < -1)return;
	writeInt32(0);
}

void BearCore::BearOutputStream::endChunk()
{
	BEAR_ASSERT(m_tell_Chunk >= 0);
	if (tell() < 0)return;
	int64 size = tell() - m_tell_Chunk;
	seek(static_cast<bsize>(m_tell_Chunk));
	writeInt32(static_cast<int32>(size));
	seek(static_cast<bsize>(tell() + m_tell_Chunk - 4));
	m_tell_Chunk = -1;
}

void BearCore::BearOutputStream::writeString(const BearString & str, BearEncoding::Encoding encoding, bool info)
{
	if (info)
	{
		uint8 type_info = 0b10000001;
		switch (encoding)
		{
		case BearEncoding::ANSI:
			type_info |= 0b10;
			writeUint8(type_info);
			writeUint32(static_cast<uint32>(str.size()));
			break;
		case BearEncoding::UTF8:
			type_info |= 0b100;
			writeUint8(type_info);
			break;
		case BearEncoding::UTF16:
			type_info |= 0b1000;
			writeUint8(type_info);
			writeUint32(static_cast<uint32>(str.size())*2);
			break;
		default:
			return;
		}

	}

	switch (encoding)
	{
	case BearEncoding::ANSI:
	{
		write((void*)*BearEncoding::ToANSI(*str), str.size());
	}
	break;
	case BearEncoding::UTF8:
	{
	
		auto ptr = BearEncoding::ToUTF8(*str);
		if (info)
			writeUint32(static_cast<uint32>(str.GetSize(reinterpret_cast<const bchar8*>(*ptr))));
		write(*ptr, str.GetSize(reinterpret_cast<const bchar8*>(*ptr)));
	}
	break;
	case BearEncoding::UTF16:
	{
#ifndef UNICODE
		write((void*)*BearEncoding::ToUTF16(*str), str.size()*2);
#else
		write((void*)(*str), str.size()*2);
#endif
	}
	break;
	default:
		break;
	};
}

void BearCore::BearOutputStream::writeStringWithZero(const BearString & str, BearEncoding::Encoding encoding)
{
	writeString(str, encoding, false);
	switch (encoding)
	{
	case BearEncoding::ANSI:
	case BearEncoding::UTF8:
		writeInt8((int8)0);	
		break;
	case BearEncoding::UTF16:
		writeInt16((int16)0);
		break;
	default:
		break;
	}
}

void BearCore::BearOutputStream::writeStringAndNewLine(const BearString & str, BearEncoding::Encoding encoding)
{
	writeString(str, encoding, false);
	switch (encoding)
	{
	case BearEncoding::ANSI:
	case BearEncoding::UTF8:
		writeInt8((int8)'\r');		writeInt8((int8)'\n');
		break;
	case BearEncoding::UTF16:
		writeInt16((int16)L'\r');		writeInt16((int16)L'\n');
		break;
	default:
		break;
	}
}

bool BearCore::BearOutputStream::write_impl(void * data, bsize & size)
{
	return false;
}

bool BearCore::BearOutputStream::eof() const
{
	return false;
}

bsize BearCore::BearOutputStream::seek(bsize tell) const
{
	return bsize();
}

bsize BearCore::BearOutputStream::tell() const
{
	return bsize();
}

bsize BearCore::BearOutputStream::size() const
{
	return bsize();
}
