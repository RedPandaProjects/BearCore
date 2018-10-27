#include "BearCore.hpp"
#define READT(type) type t=0; read(&t,sizeof(t)); return t;
uint8 BearCore::BearInputStream::readUint8()const
{
	READT(uint8);
}

uint16 BearCore::BearInputStream::readUint16()const
{
	READT(uint16);
}

uint32 BearCore::BearInputStream::readUint32()const
{
	READT(uint32);
}

uint64 BearCore::BearInputStream::readUint64()const
{
	READT(uint64);
}

int8 BearCore::BearInputStream::readInt8()const
{
	READT(int8);
}

int16 BearCore::BearInputStream::readInt16()const
{
	READT(int16);
}

int32 BearCore::BearInputStream::readInt32()const
{
	READT(int32);
}

int64 BearCore::BearInputStream::readInt64()const
{
	READT(int64);
}

float BearCore::BearInputStream::readFloat() const
{
	READT(float);
}

double BearCore::BearInputStream::readDouble() const
{
	READT(double);
}

bsize BearCore::BearInputStream::read(void * data, bsize size) const
{
	int64 t = tell();
	read_impl(data, size);
	if (t >= 0)
		return static_cast<bsize>(tell() - t);
	return 0;
}

BearCore::BearPtr<uint8> BearCore::BearInputStream::read() const
{
	return read(size() - tell());
}

BearCore::BearPtr<uint8> BearCore::BearInputStream::read(bsize size) const
{
	uint8*data = bear_alloc<uint8>(static_cast<bsize>(size));
	read(data, static_cast<bsize>(size));
	return BearPtr<uint8>(data);
}

void BearCore::BearInputStream::readString(BearString & str) const
{
	int64 t = tell();
	if (t < 0)return;
	uint8 flags = readUint8();
	if (!(flags & uint8(0b10000001)))
		return;
	bool ansi = (flags & 0b10);
	bool utf8 = (flags & 0b100);
	bool utf16 = (flags & 0b1000);
	if (ansi + utf8 + utf16 != 1)return;
	uint32 size = readUint32();
	Encoding::Encoding type;
	if (ansi)type = Encoding::ANSI;
	if (utf8)type = Encoding::UTF8;
	if (utf16)type = Encoding::UTF16;
	readString(str, size, type);
}


void BearCore::BearInputStream::readString(BearString & str, bsize size, Encoding::Encoding type) const
{
	BearPtr<uint8> text(bear_alloc<uint8>(size));
	read(*text, size);

	if (type == Encoding::UTF8)
	{
#ifdef UNICODE
		auto te = str.ConvertUTF8ToUTF16((bchar8*)*text, size);
#else
		auto te = str.ConvertUTF8ToANIS((bchar16*)*text, size);
#endif
		str.append(*te);
	}
	else if (type == Encoding::ANSI)
	{
#ifdef UNICODE
		auto te = str.ConvertToUTF16((bchar8*)*text,size);
		str.append(*te);
#else 
		str.append((bchar8*)*text,size);
#endif
	
	}
	else if (type == Encoding::UTF16)
	{
#ifdef UNICODE
		str.append((bchar16*)*text, size);
#else 
		auto te = str.ConvertToANSI((bchar16*)*text, size);
		str.append(*te);
#endif
	}
	return;
}

void BearCore::BearInputStream::toString(BearString & str, Encoding::Encoding type) const
{
	if (tell() == 0)
	{
		uint8 utf_bod[3];
		read(utf_bod, 3);
		if (utf_bod[0] == 0xef && utf_bod[1] == 0xbb && utf_bod[2] == 0xbf)
			goto jump_01;
		seek(0);
	}
jump_01:
	readString(str, static_cast<bsize>(size() - tell()), type);
}

bsize BearCore::BearInputStream::goToChunk(uint32 type_) const
{
	while (!eof())
	{
		uint32 type = readUint32();
		uint32 size_ = readUint32();
		BEAR_FATALERROR((size_ + tell()) <= size(), TEXT("для части [%d] не верный размер [%d]"), type_, size_);
		if (type_ == type)
			return size_;
		seek(static_cast<bsize>(tell() + size_));
	}
	return 0;
}
