#pragma once
namespace BearCore
{
	class BearStringAnsiConteniar
	{
	public:
		BearStringAnsiConteniar() :m_text(0), m_crc32(0), m_size(0)
		{

		}
		BearStringAnsiConteniar(const bchar8*text,bool copy=true):m_text(0),m_crc32(0),m_size(0)
		{
			set(text, copy);
		}
		BearStringAnsiConteniar(BearStringAnsiConteniar&&right)
		{
			swap(right);
		}
		inline void swap(BearStringAnsiConteniar&right)
		{
			bear_swap(m_crc32, right.m_crc32);
			bear_swap(m_size, right.m_size);
			bear_swap(m_text, right.m_text);
		}
		inline void copy(const BearStringAnsiConteniar&right)
		{
			set(*right);
		}
		inline BearStringAnsiConteniar(const BearStringAnsiConteniar&right)
		{
			copy(right);
		}
		inline BearStringAnsiConteniar& operator=(const BearStringAnsiConteniar&right)
		{
			copy(right);
			return *this;
		}
		inline BearStringAnsiConteniar& operator=(BearStringAnsiConteniar&&right)
		{
			swap(right);
			return *this;
		}
		inline bsize size()const
		{
			return m_size;
		}
		inline void set(const bchar8*str,bool copy=true)
		{
			clear();
			m_size = BearString::GetSize(str);
			if (m_size)
			{
				if (copy)
				{
					m_text = bear_alloc<bchar8>(m_size + 1);
					BearString::Copy(const_cast<bchar8*>(*m_text), m_size + 1, str);
				}
				else
				{
					m_text = BearMemoryRef<bchar8>(const_cast<bchar8*>(str), false);
				}
				m_crc32 = BearCheckSum::CRC32(*m_text, m_size);
			}
		}
		inline const bchar8* operator*() const
		{
			if (*m_text)return *m_text;
			return "";
		}
		inline void clear()
		{
			m_text.clear();
			m_size = 0;
			m_text = 0;
			m_crc32 = 0;
		}
		inline bool operator<(const BearStringAnsiConteniar& strc)const
		{
			if (m_size == strc.m_size)
			{
				if (m_crc32 == strc.m_crc32)
				{
					return BearString::Compare(**this, *strc) < 0;
				}
				else
				{
					return m_crc32 < strc.m_crc32;
				}
			}
			return m_size < strc.m_size;
		}
		inline bool operator==(const BearStringAnsiConteniar& strc)const
		{
			return *this==*strc;
		}
		inline bool operator<(const bchar8* str)const
		{
			if (BearString::Compare(**this, str) < 0)
				return true;
			return false;
		}
		inline bool operator==(const bchar8* str)const
		{
			if (BearString::Compare(**this, str) == 0)
				return true;
			return false;
		}
		~BearStringAnsiConteniar()
		{
			clear();
		}
	private:
		BearMemoryRef<bchar8> m_text;
		uint32  m_crc32;
		bsize m_size;
	};
	class BearStringUnicodeConteniar
	{
	public:
		BearStringUnicodeConteniar() :m_text(0), m_crc32(0), m_size(0)
		{

		}
		BearStringUnicodeConteniar(const bchar16*text, bool copy = true) :m_text(0), m_crc32(0), m_size(0)
		{
			set(text, copy);
		}
		BearStringUnicodeConteniar(BearStringUnicodeConteniar&&right)
		{
			swap(right);
		}
		inline void swap(BearStringUnicodeConteniar&right)
		{
			bear_swap(m_crc32, right.m_crc32);
			bear_swap(m_size, right.m_size);
			bear_swap(m_text, right.m_text);
		}
		inline void copy(const BearStringUnicodeConteniar&right)
		{
			set(*right);
		}
		inline BearStringUnicodeConteniar(const BearStringUnicodeConteniar&right)
		{
			copy(right);
		}
		inline BearStringUnicodeConteniar& operator=(const BearStringUnicodeConteniar&right)
		{
			copy(right);
			return *this;
		}
		inline BearStringUnicodeConteniar& operator=(BearStringUnicodeConteniar&&right)
		{
			swap(right);
			return *this;
		}
		inline void set(const bchar16*str, bool copy = true)
		{
			clear();
			m_size = BearString::GetSize(str);
			if (m_size)
			{
				if (copy)
				{
					m_text = bear_alloc<bchar16>(m_size + 1);
					BearString::Copy(const_cast<bchar16*>(*m_text), m_size + 1, str);
				}
				else
				{
					m_text = BearMemoryRef<bchar16>(const_cast<bchar16*>(str), false);
				}
				m_crc32 = BearCheckSum::CRC32(*m_text, m_size*2);
			}
		}
		inline bsize size()const
		{
			return m_size;
		}
		inline const bchar16* operator*() const
		{
			if (*m_text)return *m_text;
			return L"";
		}
		inline void clear()
		{
			m_text.clear();
			m_size = 0;
			m_text = 0;
			m_crc32 = 0;
		}
		inline bool operator<(const BearStringUnicodeConteniar& strc)const
		{
			if (m_size == strc.m_size)
			{
				if (m_crc32 == strc.m_crc32)
				{
					return BearString::Compare(**this, *strc) < 0;
				}
				else
				{
					return m_crc32 < strc.m_crc32;
				}
			}
			return m_size < strc.m_size;
		}
		inline bool operator==(const BearStringUnicodeConteniar& strc)const
		{
			return *this == *strc;
		}
		inline bool operator<(const bchar16* str)const
		{
			if (BearString::Compare(**this, str) < 0)
				return true;
			return false;
		}
		inline bool operator==(const bchar16* str)const
		{
			if (BearString::Compare(**this, str) == 0)
				return true;
			return false;
		}
		~BearStringUnicodeConteniar()
		{
			clear();
		}
	private:
		BearMemoryRef<bchar16> m_text;
		uint32  m_crc32;
		bsize m_size;
	};
#ifdef UNICODE
	typedef BearStringUnicodeConteniar BearStringConteniar;
#else
	typedef BearStringAnsiConteniar BearStringConteniar;
#endif
}