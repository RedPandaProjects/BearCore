#pragma once
namespace BearCore
{
	template<typename C>
	class BearStringConteniarUnknown
	{
	public:
		BearStringConteniarUnknown() :m_text(0), m_crc32(0), m_size(0)
		{

		}
		BearStringConteniarUnknown(const C*text,bool copy=true):m_text(0),m_crc32(0),m_size(0)
		{
			set(text, copy);
		}
		BearStringConteniarUnknown( BearStringConteniarUnknown<C>&&right)
		{
			swap(right);
		}
		inline void swap( BearStringConteniarUnknown<C>&right)
		{
			bear_swap(m_crc32, right.m_crc32);
			bear_swap(m_size, right.m_size);
			bear_swap(m_text, right.m_text);
		}
		inline void copy(const BearStringConteniarUnknown<C>&right)
		{
			set(*right);
		}
		inline BearStringConteniarUnknown(const  BearStringConteniarUnknown<C>&right)
		{
			copy(right);
		}
		inline BearStringConteniarUnknown& operator=(const  BearStringConteniarUnknown<C>&right)
		{
			copy(right);
			return *this;
		}
		inline BearStringConteniarUnknown& operator=( BearStringConteniarUnknown<C>&&right)
		{
			swap(right);
			return *this;
		}
		inline bsize size()const
		{
			return m_size;
		}
		inline void set(const C*str,bool copy=true)
		{
			clear();
			m_size = BearString::GetSize(str);
			if (m_size)
			{
				if (copy)
				{
					m_text = bear_alloc<C>(m_size + 1);
					BearString::Copy(const_cast<C*>(*m_text), m_size + 1, str);
				}
				else
				{
					m_text = BearMemoryRef<C>(const_cast<C*>(str), false);
				}
				m_crc32 = BearCheckSum::CRC32(*m_text, m_size);
			}
		}
		inline const C* operator*() const
		{
			if (*m_text)return *m_text;
			return (C*)L"";
		}
		inline void clear()
		{
			m_text.clear();
			m_size = 0;
			m_text = 0;
			m_crc32 = 0;
		}
		inline bool operator<(const  BearStringConteniarUnknown<C>& strc)const
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
		inline bool operator==(const  BearStringConteniarUnknown<C>& strc)const
		{
			return *this==*strc;
		}
		inline bool operator<(const C* str)const
		{
			if (BearString::Compare(**this, str) < 0)
				return true;
			return false;
		}
		inline bool operator==(const C* str)const
		{
			if (BearString::Compare(**this, str) == 0)
				return true;
			return false;
		}
		~BearStringConteniarUnknown()
		{
			clear();
		}
	private:
		BearMemoryRef<C> m_text;
		uint32  m_crc32;
		bsize m_size;
	};
typedef BearStringConteniarUnknown<bchar16> BearStringConteniarUnicode;
typedef BearStringConteniarUnknown<bchar8> BearStringConteniarAnsi;
typedef BearStringConteniarUnknown<bchar_utf8> BearStringConteniarUtf8;
typedef BearStringConteniarUnknown<bchar> BearStringConteniar;
}