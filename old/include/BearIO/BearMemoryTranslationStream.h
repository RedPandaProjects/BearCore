#pragma once
namespace  BearCore
{
	class BEARTOOL_API BearMemoryTranslationStream :public BearBufferedReader, public BearOutputStream
	{
	public:
		BearMemoryTranslationStream();
		BearMemoryTranslationStream(const BearInputStream&stream);
		BearMemoryTranslationStream(void*ptr,bsize size,bool free=false);
		~BearMemoryTranslationStream();
		bool empty()const;
		virtual bool eof() const;
		virtual int64 seek(bsize tell) const;
		virtual int64 tell()const;
		virtual int64 size()const;
		virtual void*begin();
		virtual const void*begin()const;
		virtual void*end();
		virtual const void*end()const;
		virtual void clear();
		virtual BearStreamPtr<BearBufferedReader> readChunkAsBufferedReader(uint32 type)const;

		void swap(BearMemoryTranslationStream&right);
		void copy(const BearMemoryTranslationStream&right);

		BearMemoryTranslationStream( BearMemoryTranslationStream&&right);
		BearMemoryTranslationStream(const BearMemoryTranslationStream&right);
		BearMemoryTranslationStream& operator=(const BearMemoryTranslationStream&right);
		BearMemoryTranslationStream& operator=(BearMemoryTranslationStream&&right);
	private:
		virtual void destory();
		virtual void read_impl(void*data, bsize size) const;
		virtual bool write_impl(void*data, bsize &size);
	private:
		struct data
		{
			mutable bsize m_tell;
			BearPtr<uint8> m_ptr;
			bsize m_size;
		};
		
		BearMultiPtr<data> m_data;
	
	};
};