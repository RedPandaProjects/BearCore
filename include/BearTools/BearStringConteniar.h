#pragma once
namespace BearCore
{
	class BearStringConteniar
	{
	public:
		BearStringConteniar() :m_text(0), m_crc32(0), m_size(0)
		{

		}
		BearStringConteniar(const bchar*text,bool copy=true):m_text(0),m_crc32(0),m_size(0)
		{
			set(text);
		}
		BearStringConteniar(BearStringConteniar&&right)
		{
			swap(right);
		}
		inline void swap(BearStringConteniar&right)
		{
			bear_swap(m_crc32, right.m_crc32);
			bear_swap(m_size, right.m_size);
			bear_swap(m_text, right.m_text);
		}
		inline void copy(const BearStringConteniar&right)
		{
			set(*right);
		}
		inline BearStringConteniar(const BearStringConteniar&right)
		{
			copy(right);
		}
		inline BearStringConteniar& operator=(const BearStringConteniar&right)
		{
			copy(right);
			return *this;
		}
		inline BearStringConteniar& operator=(BearStringConteniar&&right)
		{
			swap(right);
			return *this;
		}
		inline void set(const bchar*str,bool copy=true)
		{
			clear();
			m_size = BearString::GetSize(str);
			if (m_size)
			{
				if (copy)
				{
					m_text = bear_alloc<bchar>(m_size + 1);
					BearString::Copy(const_cast<bchar*>(*m_text), m_size + 1, str);
				}
				else
				{
					m_text = BearMemoryRef<bchar>(const_cast<bchar*>(str), false);
				}
				m_crc32 = BearCheckSum::CRC32(*m_text, m_size);
			}
		}
		inline const bchar* operator*() const
		{
			if (*m_text)return *m_text;
			return TEXT("");
		}
		inline void clear()
		{
			m_text.clear();
			m_size = 0;
			m_text = 0;
			m_crc32 = 0;
		}
		inline bool operator<(const BearStringConteniar& strc)const
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
		inline bool operator==(const BearStringConteniar& strc)const
		{
			return *this==*strc;
		}
		inline bool operator<(const bchar* str)const
		{
			if (BearString::Compare(**this, str) < 0)
				return true;
			return false;
		}
		inline bool operator==(const bchar* str)const
		{
			if (BearString::Compare(**this, str) == 0)
				return true;
			return false;
		}
		~BearStringConteniar()
		{
			clear();
		}
	private:
		BearMemoryRef<bchar> m_text;
		uint32  m_crc32;
		bsize m_size;
	};
}