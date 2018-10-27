#include "BearCore.hpp"

BearCore::BearMemoryStream::BearMemoryStream():m_tell(0), m_data(0), m_size(0)
{
}

BearCore::BearMemoryStream::~BearMemoryStream()
{
	clear();
}

bool BearCore::BearMemoryStream::eof() const
{
	return m_tell == size();
}

bsize BearCore::BearMemoryStream::seek(bsize tell) const
{
	if (size() < 0)return 0;
	if (m_tell <= static_cast<bsize>(size()))m_tell = tell;
	return BearMemoryStream::tell();
}

bsize BearCore::BearMemoryStream::tell() const
{
	return m_tell;
}

bsize BearCore::BearMemoryStream::size() const
{
	return m_size;
}

void BearCore::BearMemoryStream::resize(bsize size)
{
	m_data = bear_realloc(m_data, size);
	m_size = size;
	if (m_tell > size)m_tell = size;
}

void * BearCore::BearMemoryStream::begin()
{
	return m_data+m_tell;
}

const void * BearCore::BearMemoryStream::begin() const
{
	return m_data + m_tell;
}

void * BearCore::BearMemoryStream::end()
{
	return m_data + m_size;
}

const void * BearCore::BearMemoryStream::end() const
{
	return m_data + m_size;
}

void BearCore::BearMemoryStream::clear()
{
	m_tell = 0;
	bear_free(m_data);
	m_data = 0;
	m_size = 0;
}

BearCore::BearStreamRef< BearCore::BearBufferedReader> BearCore::BearMemoryStream::readChunkAsBufferedReader(uint32 type) const
{
	auto size = goToChunk(type);
	if (!size)return BearCore::BearStreamRef<BearCore::BearBufferedReader>();
	BearMemoryStream *temp = bear_new<BearMemoryStream>();
	temp->resize(size);
	read(temp->begin(), size);
	return temp;
}

BearCore::BearMemoryStream::BearMemoryStream(BearMemoryStream && stream) :m_tell(0), m_data(0), m_size(0)
{
	swap(stream);
}

void BearCore::BearMemoryStream::swap(BearMemoryStream & stream)
{
	bear_swap(m_tell, stream.m_tell);
	bear_swap(m_data, stream.m_data);
	bear_swap(m_size, stream.m_size);
}

void BearCore::BearMemoryStream::copy(const BearMemoryStream & right)
{
	clear();
	write(right.m_data, right.m_size);
	m_tell = right.m_tell;
}

BearCore::BearMemoryStream::BearMemoryStream(const BearMemoryStream & right) :m_tell(0), m_data(0), m_size(0)
{
	copy(right);
}

BearCore::BearMemoryStream::BearMemoryStream(const BearInputStream & right) : m_tell(0), m_data(0), m_size(0)
{
	if (right.size() - right.tell())
	{
		resize(right.size() - right.tell());
		right.read(m_data, right.size());
	}
}

BearCore::BearMemoryStream & BearCore::BearMemoryStream::operator=(const BearMemoryStream & right)
{
	copy(right);
	return *this;
}

BearCore::BearMemoryStream & BearCore::BearMemoryStream::operator=(BearMemoryStream && right)
{
	swap(right);
	return *this;
}

void BearCore::BearMemoryStream::destory()
{
	clear();
	BearMemory::Free(this);
}

void BearCore::BearMemoryStream::read_impl(void * data, bsize size) const
{
	bear_copy(data, m_data + m_tell, size + m_tell>m_size ? m_size - m_tell : size);
	seek(size + m_tell);
}

bool BearCore::BearMemoryStream::write_impl(void * data, bsize & size)
{
	if (size + m_tell >m_size)resize(bear_recommended_size(size + m_tell));
	bear_copy(m_data + m_tell, data, size);
	seek(size + m_tell);
	return true;
}
