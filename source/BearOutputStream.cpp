#include "BearCore.hpp"
#define WRITENUMBER Write(&data,sizeof(data)); 
BearCore::BearOutputStream::BearOutputStream():m_tell_Chunk(-1)
{
}
void BearCore::BearOutputStream::WriteUint8(uint8 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteUint16(uint16 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteUint32(uint32 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteUint64(uint64 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteInt8(int8 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteInt16(int16 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteInt32(int32 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteInt64(int64 data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteFloat(float data)
{
	WRITENUMBER
}

void BearCore::BearOutputStream::WriteDouble(double data)
{
	WRITENUMBER
}

bsize BearCore::BearOutputStream::Write(void * data, bsize size)
{
	if (write_impl(data, size))
		return size;
	return 0;
}

void BearCore::BearOutputStream::BeginChunk(int32 id)
{
	if (Tell() < 0)return;
	WriteInt32(id);
	m_tell_Chunk = Tell();
	if (m_tell_Chunk < -1)return;
	WriteInt32(0);
}

void BearCore::BearOutputStream::EndChunk()
{
	BEAR_ASSERT(m_tell_Chunk >= 0);
	if (Tell() < 0)return;
	int64 size = Tell() - m_tell_Chunk;
	Seek(static_cast<bsize>(m_tell_Chunk));
	WriteInt32(static_cast<int32>(size));
	Seek(static_cast<bsize>(Tell() + m_tell_Chunk - 4));
	m_tell_Chunk = -1;
}

void BearCore::BearOutputStream::WriteString(const BearString & str, BearEncoding::Encoding encoding, bool info)
{
	if (info)
	{
		uint8 type_info = 0b10000001;
		switch (encoding)
		{
		case BearEncoding::ANSI:
			type_info |= 0b10;
			WriteUint8(type_info);
			WriteUint32(static_cast<uint32>(str.size()));
			break;
		case BearEncoding::UTF8:
			type_info |= 0b100;
			WriteUint8(type_info);
			break;
		case BearEncoding::UTF16:
			type_info |= 0b1000;
			WriteUint8(type_info);
			WriteUint32(static_cast<uint32>(str.size())*2);
			break;
		default:
			return;
		}

	}

	switch (encoding)
	{
	case BearEncoding::ANSI:
	{
		Write((void*)*BearEncoding::ToANSI(*str), str.size());
	}
	break;
	case BearEncoding::UTF8:
	{
	
		auto ptr = BearEncoding::ToUTF8(*str);
		if (info)
			WriteUint32(static_cast<uint32>(str.GetSize(reinterpret_cast<const bchar8*>(*ptr))));
		Write(*ptr, str.GetSize(reinterpret_cast<const bchar8*>(*ptr)));
	}
	break;
	case BearEncoding::UTF16:
	{
#ifndef UNICODE
		Write((void*)*BearEncoding::ToUTF16(*str), str.size()*2);
#else
		Write((void*)(*str), str.size()*2);
#endif
	}
	break;
	default:
		break;
	};
}

void BearCore::BearOutputStream::WriteStringWithZero(const BearString & str, BearEncoding::Encoding encoding)
{
	WriteString(str, encoding, false);
	switch (encoding)
	{
	case BearEncoding::ANSI:
	case BearEncoding::UTF8:
		WriteInt8((int8)0);	
		break;
	case BearEncoding::UTF16:
		WriteInt16((int16)0);
		break;
	default:
		break;
	}
}

void BearCore::BearOutputStream::WriteStringAndNewLine(const BearString & str, BearEncoding::Encoding encoding)
{
	WriteString(str, encoding, false);
	switch (encoding)
	{
	case BearEncoding::ANSI:
	case BearEncoding::UTF8:
		WriteInt8((int8)'\r');		WriteInt8((int8)'\n');
		break;
	case BearEncoding::UTF16:
		WriteInt16((int16)L'\r');		WriteInt16((int16)L'\n');
		break;
	default:
		break;
	}
}

bool BearCore::BearOutputStream::write_impl(void * data, bsize & size)
{
	return false;
}

bool BearCore::BearOutputStream::Eof() const
{
	return false;
}

bsize BearCore::BearOutputStream::Seek(bsize Tell) const
{
	return bsize();
}

bsize BearCore::BearOutputStream::Tell() const
{
	return bsize();
}

bsize BearCore::BearOutputStream::Size() const
{
	return bsize();
}
