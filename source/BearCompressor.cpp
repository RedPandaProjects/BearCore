#include "BearCore.hpp"
#include <lzo/lzoconf.h>
#include <lzo/lzo1x.h>
#include <zlib/zlib.h>
lzo_voidp GLZOWrkmem =0;

bsize BearCore::BearLZO::Compressor(const void * in_, void * out_, bsize size_block)
{
	if(GLZOWrkmem ==0)
		GLZOWrkmem = (lzo_voidp)bear_alloc<uint8>(LZO1X_1_MEM_COMPRESS);

	int r;
	lzo_bytep in= static_cast<lzo_bytep>( const_cast<void*>(in_));
	lzo_bytep out= static_cast<lzo_bytep>(out_);
	lzo_uint in_len= size_block;
	lzo_uint out_len;
	r = lzo1x_1_compress(in, in_len, out, &out_len, GLZOWrkmem);
	BEAR_FATALERROR(r == LZO_E_OK, TEXT("LZO:Неудачная компресия"));
	return static_cast<bsize>(out_len);
}

bsize BearCore::BearLZO::Decompressor(const void * in_, void * out_, bsize size_block)
{
	int r;
	lzo_bytep in = static_cast<lzo_bytep>(const_cast<void*>(in_));
	lzo_bytep out = static_cast<lzo_bytep>(out_);
	lzo_uint in_len = size_block; lzo_uint out_len;
	r = lzo1x_decompress(in, in_len, out, &out_len, NULL);
	BEAR_FATALERROR(r == LZO_E_OK, TEXT("LZO:Неудачная декомпресия"));
	return static_cast<bsize>(out_len);
}


BearCore::BearZLIB::BearZLIB(ZLIBType type):m_type(type)
{
	m_ptr = bear_alloc<z_stream>(1);
	bear_fill(*reinterpret_cast<z_stream*>(m_ptr));
	int ret = Z_ERRNO;
	switch (type)
	{
	case BearCore::BearZLIB::Z_Best:
		ret = deflateInit(reinterpret_cast<z_stream*>( m_ptr), Z_BEST_COMPRESSION);
		break;
	case BearCore::BearZLIB::Z_Fast:
		ret = deflateInit(reinterpret_cast<z_stream*>(m_ptr), Z_BEST_SPEED);
		break;
	case BearCore::BearZLIB::Z_Decompressor:
		ret = inflateInit(reinterpret_cast<z_stream*>(m_ptr));
		break;
	}
	BEAR_ASSERT(ret == Z_OK);
}

BearCore::BearZLIB::~BearZLIB()
{
	switch (m_type)
	{
	case BearCore::BearZLIB::Z_Fast:
	case BearCore::BearZLIB::Z_Best:
		deflateEnd(reinterpret_cast<z_stream*>(m_ptr));
		
		break;
	default:
		inflateEnd(reinterpret_cast<z_stream*>(m_ptr));
		break;
	}
	bear_free(m_ptr);
}

void BearCore::BearZLIB::SetIn(const void * in, bsize size)
{
	reinterpret_cast<z_stream*>(m_ptr)->avail_in = static_cast<uInt>(size);
	reinterpret_cast<z_stream*>(m_ptr)->next_in =reinterpret_cast<Bytef*>( const_cast<void*>( in));
}

void BearCore::BearZLIB::SetOut(void * out, bsize size)
{
	m_buffer_out = out;
	reinterpret_cast<z_stream*>(m_ptr)->avail_out = static_cast<uInt>(size);
	reinterpret_cast<z_stream*>(m_ptr)->next_out= reinterpret_cast<Bytef*>(out);
}

bool BearCore::BearZLIB::IsInNull() const
{
	return reinterpret_cast<z_stream*>(m_ptr)->avail_in == 0;
}

bool BearCore::BearZLIB::IsOutNull() const
{
	return reinterpret_cast<z_stream*>(m_ptr)->avail_out == 0;;
}

bool BearCore::BearZLIB::Run()
{
	if (m_type == Z_Decompressor)
	{
		auto &strm = *reinterpret_cast<z_stream*>(m_ptr);
		while (strm.avail_in != 0 && strm.avail_out != 0)
		{
			int res = inflate(&strm, Z_NO_FLUSH);
			if (res == Z_STREAM_END)return true;
			BEAR_ASSERT(res == Z_OK);
		}
		return strm.avail_in == 0;
	}
	else
	{
		auto &strm = *reinterpret_cast<z_stream*>(m_ptr);
		while (strm.avail_in != 0 && strm.avail_out != 0)
		{
			int res = deflate(&strm, Z_NO_FLUSH);
			BEAR_ASSERT(res == Z_OK);
		}
		return strm.avail_in == 0;
	}
}

bool BearCore::BearZLIB::Stop()
{
	auto &strm = *reinterpret_cast<z_stream*>(m_ptr);
	int deflate_res = Z_OK;
	while (deflate_res == Z_OK)
	{
		if (strm.avail_out == 0)return false;
		deflate_res = deflate(&strm, Z_FINISH);
	}
	BEAR_ASSERT(deflate_res == Z_STREAM_END);
	return true;
}

bsize BearCore::BearZLIB::GetWriteSize()const
{
	return reinterpret_cast<z_stream*>(m_ptr)->next_out - reinterpret_cast<Bytef*>(m_buffer_out);
}
