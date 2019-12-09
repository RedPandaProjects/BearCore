#include "BearCore.hpp"

BearCore::BearMemoryStream::BearMemoryStream():m_tell(0), m_data(0), m_size(0)
{
}

BearCore::BearMemoryStream::~BearMemoryStream()
{
	Clear();
}

bool BearCore::BearMemoryStream::Eof() const
{
	return m_tell == Size();
}

bsize BearCore::BearMemoryStream::Seek(bsize tell) const
{
	if (Size() < 0)return 0;
	if (tell <= static_cast<bsize>(Size()))m_tell = tell;
	else m_tell = Size();
	return BearMemoryStream::Tell();
}

bsize BearCore::BearMemoryStream::Tell() const
{
	return m_tell;
}

bsize BearCore::BearMemoryStream::Size() const
{
	return m_size;
}

void BearCore::BearMemoryStream::Resize(bsize size)
{
	m_data = bear_realloc(m_data, size);
	m_size = size;
	if (m_tell > size)m_tell = size;
}

void * BearCore::BearMemoryStream::Begin()
{
	return m_data+m_tell;
}

const void * BearCore::BearMemoryStream::Begin() const
{
	return m_data + m_tell;
}

void * BearCore::BearMemoryStream::End()
{
	return m_data + m_size;
}

const void * BearCore::BearMemoryStream::End() const
{
	return m_data + m_size;
}

void BearCore::BearMemoryStream::Clear()
{
	m_tell = 0;
	bear_free(m_data);
	m_data = 0;
	m_size = 0;
}

BearCore::BearStreamRef< BearCore::BearBufferedReader> BearCore::BearMemoryStream::ReadChunkAsBufferedReader(uint32 type) const
{
	auto size = GoToChunk(type);
	if (!size)return BearCore::BearStreamRef<BearCore::BearBufferedReader>();
	BearMemoryStream *temp = bear_new<BearMemoryStream>();
	temp->Resize(size);
	Read(temp->Begin(), size);
	return temp;
}

BearCore::BearMemoryStream::BearMemoryStream(BearMemoryStream && stream) :m_tell(0), m_data(0), m_size(0)
{
	Swap(stream);
}

void BearCore::BearMemoryStream::Swap(BearMemoryStream & stream)
{
	bear_swap(m_tell, stream.m_tell);
	bear_swap(m_data, stream.m_data);
	bear_swap(m_size, stream.m_size);
}

void BearCore::BearMemoryStream::Copy(const BearMemoryStream & right)
{
	Clear();
	Write(right.m_data, right.m_size);
	m_tell = right.m_tell;
}

BearCore::BearMemoryStream::BearMemoryStream(const BearMemoryStream & right) :m_tell(0), m_data(0), m_size(0)
{
	Copy(right);
}

BearCore::BearMemoryStream::BearMemoryStream(const BearInputStream & right) : m_tell(0), m_data(0), m_size(0)
{
	if (right.Size() - right.Tell())
	{
		Resize(right.Size() - right.Tell());
		right.Read(m_data, right.Size());
	}
}

BearCore::BearMemoryStream & BearCore::BearMemoryStream::operator=(const BearMemoryStream & right)
{
	Copy(right);
	return *this;
}

BearCore::BearMemoryStream & BearCore::BearMemoryStream::operator=(BearMemoryStream && right)
{
	Swap(right);
	return *this;
}

void BearCore::BearMemoryStream::Destory()
{
	Clear();
	BearMemory::Free(this);
}

void BearCore::BearMemoryStream::read_impl(void * data, bsize size) const
{
	bear_copy(data, m_data + m_tell, size + m_tell>m_size ? m_size - m_tell : size);
	Seek(size + m_tell);
}

bool BearCore::BearMemoryStream::write_impl(const void * data, bsize & size)
{
	if (size + m_tell >m_size)Resize(bear_recommended_size(size + m_tell));
	bear_copy(m_data + m_tell, data, size);
	Seek(size + m_tell);
	return true;
}
