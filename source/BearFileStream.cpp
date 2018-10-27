#include "BearCore.hpp"

BearCore::BearFileStream::BearFileStream():m_file(0),m_mode(0)
{
}

BearCore::BearFileStream::BearFileStream(const bchar * name, BearFlags<uint8> mode) : m_file(0), m_mode(0)
{
	open(name, mode);
}

BearCore::BearFileStream::~BearFileStream()
{
	close();
}

bool BearCore::BearFileStream::open(const bchar * name, BearFlags<uint8> flags)
{
	close();
	const bchar*mode = TEXT("");
	m_mode = flags;
	if (flags.test(Write))
		mode = TEXT("wb");
	if (flags.test(Read))
		mode = TEXT("rb");
	if (m_file) close();
#ifdef UNICODE
	_wfopen_s(reinterpret_cast<FILE**>(&m_file), name, mode);
#else
	fopen_s(reinterpret_cast<FILE**>(&m_file), name, mode);
#endif
	if (m_file)
	{
		seek(0);
		//BearString::Copy(m_name, name);
	}
	else
	{
		close();
	}
	return m_file;
}

bool BearCore::BearFileStream::eof() const
{
	return tell() == size();
}

bsize BearCore::BearFileStream::seek(bsize tell1) const
{
	if (!m_file)
		return 0;

	_fseeki64((FILE*)m_file, tell1, SEEK_SET);
	return tell();
}

bsize BearCore::BearFileStream::tell() const
{
	if (m_file)
		return	static_cast<bsize>(_ftelli64((FILE*)m_file));
	else
		return 0;
}

bsize BearCore::BearFileStream::size() const
{
	if (!m_file)
		return 0;
	bsize pos = tell();
	fseek((FILE*)m_file, 0, SEEK_END);
	bsize size_ = tell();
	seek(static_cast<bsize>(pos));
	return size_;
}

void BearCore::BearFileStream::close()
{
	if (m_file)fclose((FILE*)m_file);
	m_file = 0;
	m_mode = 0;
}

BearCore::BearStreamRef< BearCore::BearInputStream> BearCore::BearFileStream::readChunkAsInputStream(uint32 type) const
{
	auto size = goToChunk(type);
	if (!size)return BearCore::BearStreamRef<BearCore::BearInputStream>();

	BearMemoryStream *temp = bear_new<BearMemoryStream>();
	temp->write(*read(size),size);
	return temp;
}

void BearCore::BearFileStream::swap(BearFileStream & right)
{
	bear_swap(right.m_file, m_file);
	bear_swap(right.m_mode, m_mode);
}





void BearCore::BearFileStream::destory()
{
	close();
	BearMemory::Free(this);
}

void BearCore::BearFileStream::read_impl(void * data, bsize size) const
{
	if (m_file&&m_mode.test(Read))
		fread(data, size, 1, (FILE*)m_file);
}

bool BearCore::BearFileStream::write_impl(void * data, bsize & size)
{
	if (m_file&&m_mode.test(Write)) {
		size = fwrite(data, 1, size, (FILE*)m_file);
		return true;
	}
	else
		return false;
}
