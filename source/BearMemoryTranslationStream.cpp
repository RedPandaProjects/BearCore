#include "BearCore.hpp"

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream()
{
}

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream(const BearInputStream & stream)
{
	m_data.create();
	m_data.get()->m_size = stream.Size()-stream.Tell();
	m_data.get()->m_tell = 0;
	m_data.get()->m_ptr = stream.Read();
}

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream(void * ptr, bsize size,bool free)
{
	m_data.create();
	m_data.get()->m_size = size;
	m_data.get()->m_tell = 0;
	m_data.get()->m_ptr = BearMemoryRef<uint8>(reinterpret_cast<uint8*>(ptr), free);

}

BearCore::BearMemoryTranslationStream::~BearMemoryTranslationStream()
{
	Clear();
}

bool BearCore::BearMemoryTranslationStream::Empty() const
{
	return m_data.empty();
}

bool BearCore::BearMemoryTranslationStream::Eof() const
{
	return Tell() == Size();;
}

bsize BearCore::BearMemoryTranslationStream::Seek(bsize tell1) const
{
	if (Empty())return 0;
	m_data.get()->m_tell = tell1;
	if (Tell() >Size())
		m_data.get()->m_tell = m_data.get()->m_size;
	return m_data.get()->m_tell;
}

bsize BearCore::BearMemoryTranslationStream::Tell() const
{
	if (Empty())return 0;
	return m_data.get()->m_tell;
}

bsize BearCore::BearMemoryTranslationStream::Size() const
{
	if (Empty())return 0;
	return m_data.get()->m_size;
}


void * BearCore::BearMemoryTranslationStream::Begin()
{
	if (Empty())return 0;
	return *(m_data.get()->m_ptr)+ m_data.get()->m_tell;
}

const void * BearCore::BearMemoryTranslationStream::Begin() const
{
	if (Empty())return 0;
	return *(m_data.get()->m_ptr) + m_data.get()->m_tell;
}

void * BearCore::BearMemoryTranslationStream::End()
{
	if (Empty())return 0;
	return *(m_data.get()->m_ptr) + m_data.get()->m_size;
}

const void * BearCore::BearMemoryTranslationStream::End() const
{
	if (Empty())return 0;
	return *(m_data.get()->m_ptr) + m_data.get()->m_size;
}

void BearCore::BearMemoryTranslationStream::Clear()
{
	m_data.clear();
}

BearCore::BearStreamRef<BearCore::BearBufferedReader> BearCore::BearMemoryTranslationStream::ReadChunkAsBufferedReader(uint32 type) const
{
	auto size = GoToChunk(type);
	if (!size)return BearCore::BearStreamRef<BearCore::BearBufferedReader>();
	BearMemoryTranslationStream *temp = bear_new<BearMemoryTranslationStream>();
	*temp = *this;
	Seek(Tell() + size);
	return temp;
}

void BearCore::BearMemoryTranslationStream::Swap(BearMemoryTranslationStream & right)
{
	m_data.swap(right.m_data);
}

void BearCore::BearMemoryTranslationStream::Copy(const BearMemoryTranslationStream & right)
{
	Clear();
	m_data = right.m_data;
}

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream(BearMemoryTranslationStream && right)
{
	Swap(right);
}

BearCore::BearMemoryTranslationStream::BearMemoryTranslationStream(const BearMemoryTranslationStream & right)
{
	Copy(right);
}

BearCore::BearMemoryTranslationStream & BearCore::BearMemoryTranslationStream::operator=(const BearMemoryTranslationStream & right)
{
	Copy(right);
	return *this;
}

BearCore::BearMemoryTranslationStream & BearCore::BearMemoryTranslationStream::operator=(BearMemoryTranslationStream && right)
{
	Swap(right);
	return *this;
}

void BearCore::BearMemoryTranslationStream::Destory()
{
	Clear();
	BearMemory::Free(this);
}

void BearCore::BearMemoryTranslationStream::read_impl(void * data, bsize size) const
{
	if (Empty())return ;
	bear_copy(data, *m_data.get()->m_ptr + m_data.get()->m_tell, size + m_data.get()->m_tell>m_data.get()->m_size ? m_data.get()->m_size - m_data.get()->m_tell : size);
	Seek(size + m_data.get()->m_tell);
}

bool BearCore::BearMemoryTranslationStream::write_impl(void * data, bsize & size)
{
	if (Empty())return false;
	if (size + m_data.get()->m_tell > m_data.get()->m_size)size = m_data.get()->m_size - m_data.get()->m_tell;
	bear_copy(*m_data.get()->m_ptr + m_data.get()->m_tell, data, size);
	Seek(size + m_data.get()->m_tell);
	return size + m_data.get()->m_tell < m_data.get()->m_size;
}
