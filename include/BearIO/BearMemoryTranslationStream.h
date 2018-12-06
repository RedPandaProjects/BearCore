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
		bool Empty()const;
		virtual bool Eof() const;
		virtual bsize Seek(bsize tell) const;
		virtual bsize Tell()const;
		virtual bsize Size()const;
		virtual void*Begin();
		virtual const void*Begin()const;
		virtual void*End();
		virtual const void*End()const;
		virtual void Clear();
		virtual BearStreamRef<BearBufferedReader> ReadChunkAsBufferedReader(uint32 type)const;

		void Swap(BearMemoryTranslationStream&right);
		void Copy(const BearMemoryTranslationStream&right);

		BearMemoryTranslationStream( BearMemoryTranslationStream&&right);
		BearMemoryTranslationStream(const BearMemoryTranslationStream&right);
		BearMemoryTranslationStream& operator=(const BearMemoryTranslationStream&right);
		BearMemoryTranslationStream& operator=(BearMemoryTranslationStream&&right);
	private:
		virtual void Destory();
		virtual void read_impl(void*data, bsize size) const;
		virtual bool write_impl(void*data, bsize &size);
	private:
		struct data
		{
			mutable bsize m_tell;
			BearMemoryRef<uint8> m_ptr;
			bsize m_size;
		};
		
		BearMemoryMultiRef<data> m_data;
	
	};
};