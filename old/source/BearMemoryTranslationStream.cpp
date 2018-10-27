#include "BearCore.hpp"

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream()
{
}

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream(const BearInputStream & stream)
{
	m_data.create();
	m_data.get()->m_size = stream.size()-stream.tell();
	m_data.get()->m_tell = 0;
	m_data.get()->m_ptr = stream.read();
}

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream(void * ptr, bsize size,bool free)
{
	m_data.create();
	m_data.get()->m_size = size;
	m_data.get()->m_tell = 0;
	m_data.get()->m_ptr = BearPtr<uint8>(reinterpret_cast<uint8*>(ptr), free);

}

BearCore::BearMemoryTranslationStream::~BearMemoryTranslationStream()
{
	clear();
}

bool BearCore::BearMemoryTranslationStream::empty() const
{
	return m_data.empty();
}

bool BearCore::BearMemoryTranslationStream::eof() const
{
	return tell() == size();;
}

int64 BearCore::BearMemoryTranslationStream::seek(bsize tell1) const
{
	if (empty())return -1;
	m_data.get()->m_tell = tell1;
	if (tell() > size())
		m_data.get()->m_tell = m_data.get()->m_size;
	return m_data.get()->m_tell;
}

int64 BearCore::BearMemoryTranslationStream::tell() const
{
	if (empty())return -1;
	return m_data.get()->m_tell;
}

int64 BearCore::BearMemoryTranslationStream::size() const
{
	if (empty())return -1;
	return m_data.get()->m_size;
}


void * BearCore::BearMemoryTranslationStream::begin()
{
	if (empty())return 0;
	return *(m_data.get()->m_ptr)+ m_data.get()->m_tell;
}

const void * BearCore::BearMemoryTranslationStream::begin() const
{
	if (empty())return 0;
	return *(m_data.get()->m_ptr) + m_data.get()->m_tell;
}

void * BearCore::BearMemoryTranslationStream::end()
{
	if (empty())return 0;
	return *(m_data.get()->m_ptr) + m_data.get()->m_size;
}

const void * BearCore::BearMemoryTranslationStream::end() const
{
	if (empty())return 0;
	return *(m_data.get()->m_ptr) + m_data.get()->m_size;
}

void BearCore::BearMemoryTranslationStream::clear()
{
	m_data.clear();
}

BearCore::BearStreamPtr<BearCore::BearBufferedReader> BearCore::BearMemoryTranslationStream::readChunkAsBufferedReader(uint32 type) const
{
	auto size = goToChunk(type);
	if (!size)return BearCore::BearStreamPtr<BearCore::BearBufferedReader>();
	BearMemoryTranslationStream *temp = bear_new<BearMemoryTranslationStream>();
	*temp = *this;
	seek(tell() + size);
	return temp;
}

void BearCore::BearMemoryTranslationStream::swap(BearMemoryTranslationStream & right)
{
	m_data.swap(right.m_data);
}

void BearCore::BearMemoryTranslationStream::copy(const BearMemoryTranslationStream & right)
{
	clear();
	m_data = right.m_data;
}

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream(BearMemoryTranslationStream && right)
{
	swap(right);
}

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream(const BearMemoryTranslationStream & right)
{
	copy(right);
}

BearCore::BearMemoryTranslationStream & BearCore::BearMemoryTranslationStream::operator=(const BearMemoryTranslationStream & right)
{
	copy(right);
	return *this;
}

BearCore::BearMemoryTranslationStream & BearCore::BearMemoryTranslationStream::operator=(BearMemoryTranslationStream && right)
{
	swap(right);
	return *this;
}

void BearCore::BearMemoryTranslationStream::destory()
{
	clear();
	BearMemory::Free(this);
}

void BearCore::BearMemoryTranslationStream::read_impl(void * data, bsize size) const
{
	if (empty())return ;
	bear_copy(data, *m_data.get()->m_ptr + m_data.get()->m_tell, size + m_data.get()->m_tell>m_data.get()->m_size ? m_data.get()->m_size - m_data.get()->m_tell : size);
	seek(size + m_data.get()->m_tell);
}

bool BearCore::BearMemoryTranslationStream::write_impl(void * data, bsize & size)
{
	if (empty())return false;
	if (size + m_data.get()->m_tell > m_data.get()->m_size)size = m_data.get()->m_size - m_data.get()->m_tell;
	bear_copy(*m_data.get()->m_ptr + m_data.get()->m_tell, data, size);
	seek(size + m_data.get()->m_tell);
	return size + m_data.get()->m_tell < m_data.get()->m_size;
}
