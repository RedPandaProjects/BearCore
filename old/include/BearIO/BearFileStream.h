#pragma once
namespace  BearCore
{
	class BEARTOOL_API BearFileStream :public BearInputStream, public BearOutputStream
	{
	public:
		BEAR_CLASS_NO_COPY(BearFileStream);
		enum Mode
		{
			Read = 1 << 0,
			Write = 1 << 1
		};
		BearFileStream();
		BearFileStream(const bchar* name, BearFlags<uint8> mode = Read);
		~BearFileStream();
		bool open(const bchar* name, BearFlags<uint8> mode = Read);
		virtual bool eof() const;
		virtual int64 seek(bsize tell) const;
		virtual int64 tell()const;
		virtual int64 size()const;
		void close();
		virtual BearStreamPtr<BearInputStream> readChunkAsInputStream(uint32 type)const;

		void swap(BearFileStream&right);
	private:
		virtual void destory();
		virtual void read_impl(void*data, bsize size) const;
		virtual bool write_impl(void*data, bsize &size);
	private:
		BearFlags<uint8> m_mode;
		mutable void* m_file;
	};
}