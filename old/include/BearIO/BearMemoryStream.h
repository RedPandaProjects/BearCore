#pragma once
namespace  BearCore
{
	class BEARTOOL_API BearMemoryStream :public BearBufferedReader, public BearOutputStream
	{
	public:
		BearMemoryStream();
		~BearMemoryStream();

		virtual bool eof() const;
		virtual int64 seek(bsize tell) const;
		virtual int64 tell()const;
		virtual int64 size()const;
		void resize(bsize size);
		virtual void*begin();
		virtual const void*begin()const;
		virtual void*end();
		virtual const void*end()const;
		virtual void clear();
		virtual BearStreamPtr<BearBufferedReader> readChunkAsBufferedReader(uint32 type)const;

		BearMemoryStream(BearMemoryStream&&right);
		void swap(BearMemoryStream&right);
		void copy(const BearMemoryStream&right);
		BearMemoryStream(const BearMemoryStream&right);
		BearMemoryStream& operator=(const BearMemoryStream&right);
		BearMemoryStream& operator=(BearMemoryStream&&right);
	private:
		virtual void destory();
		virtual void read_impl(void*data, bsize size) const;
		virtual bool write_impl(void*data, bsize &size);
	private:
		mutable bsize m_tell;
		uint8* m_data;
		bsize m_size;
	};
};