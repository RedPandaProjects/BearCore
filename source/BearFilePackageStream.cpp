#include "BearCore.hpp"

BearCore::BearFilePackageStream::BearFilePackageStream():m_tell(0),m_ptr(0),m_size(0)
{

}

BearCore::BearFilePackageStream::~BearFilePackageStream()
{
}

BearCore::BearFilePackageStream::BearFilePackageStream(const BearFilePackageStream & right) :m_tell(0), m_ptr(0), m_size(0)
{
	Copy(right);
}

BearCore::BearFilePackageStream::BearFilePackageStream(BearFilePackageStream && right) : m_tell(0), m_ptr(0), m_size(0)
{
	Swap(right);
}

void BearCore::BearFilePackageStream::Copy(const BearFilePackageStream & right)
{
	m_file_name = right.m_file_name;
	m_ptr = right.m_ptr;
	m_tell = right.m_tell;
	m_size = right.m_size;
	OpenFile();
}

void BearCore::BearFilePackageStream::Swap(BearFilePackageStream & right)
{
	m_file_name.swap(right.m_file_name);
	m_file.Swap(right.m_file);
	bear_swap(m_ptr , right.m_ptr);
	bear_swap(m_tell , right.m_tell);
	bear_swap(m_size, right.m_size);
}

BearCore::BearFilePackageStream & BearCore::BearFilePackageStream::operator=(BearFilePackageStream && right)
{
	Swap(right);
	return *this;
}

BearCore::BearFilePackageStream & BearCore::BearFilePackageStream::operator=(const BearFilePackageStream & right)
{
	Copy(right);
	return *this;
}

bool BearCore::BearFilePackageStream::Eof() const
{
	return m_size+m_ptr==m_file.Tell();
}

bsize BearCore::BearFilePackageStream::Seek(bsize tell) const
{
	if (tell > m_size)
		m_tell = m_size;
	else 
		m_tell = tell;
	if (m_size)m_file.Seek(m_ptr + m_tell);
	return m_tell;
}

bsize BearCore::BearFilePackageStream::Tell() const
{
	return m_tell;
}

bsize BearCore::BearFilePackageStream::Size() const
{
	return m_size;
}

void BearCore::BearFilePackageStream::Close()
{
	m_file.Close();
	m_file_name.clear();
	m_ptr =0;
	m_tell =0;
	m_size = 0;
}

BearCore::BearStreamRef<BearCore::BearInputStream> BearCore::BearFilePackageStream::ReadChunkAsInputStream(uint32 type) const
{
	auto size = GoToChunk(type);
	if (!size)return BearCore::BearStreamRef<BearCore::BearInputStream>();

	BearFilePackageStream *temp = bear_new<BearFilePackageStream>();
	*temp = *this;
	return temp;
}

void BearCore::BearFilePackageStream::Destory()
{
	bear_delete(this);
}

void BearCore::BearFilePackageStream::read_impl(void * data, bsize size) const
{
	if (m_tell + size > m_size)size = m_size - m_tell;
	m_file.Read(data, size);
	m_tell += size;
}


void BearCore::BearFilePackageStream::OpenFile()
{
	if (m_size == 0)return;
	BEAR_ASSERT(m_file.Open(*m_file_name));
	m_file.Seek(m_ptr + m_tell);

}
