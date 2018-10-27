#pragma once
namespace BearCore
{
	typedef bchar BearString8[8];
	typedef bchar BearString16[16];
	typedef bchar BearString32[32];
	typedef bchar BearString64[64];
	typedef bchar BearString128[128];
	typedef bchar BearString256[256];
	typedef bchar BearString512[512];
	typedef bchar BearString1024[1024];
	typedef bchar BearString2048[2048];
	typedef bchar BearString4096[4096];
	typedef bchar BearString8192[8192];
	typedef bchar BearStringPath[MAX_PATH*2];
	class BearString :public std::basic_string<bchar, std::char_traits<bchar>, bear_allocator<bchar>>
	{
		typedef std::basic_string<bchar, std::char_traits<bchar>, bear_allocator<bchar>> basic_string;
	public:
		static inline bsize GetSize(const bchar8*text)
		{
			return strlen(text);
		}
		static inline bsize GetSize(const bchar16*text)
		{
			return wcslen(text);
		}
		template<bsize sizeBuffer>
		static	inline void Contact(bchar(&dst)[sizeBuffer], const  bchar *src)
		{
#ifdef UNICODE
			wcscat_s(dst, sizeBuffer, src);
#else
			strcat_s(dst, sizeBuffer, src);
#endif
		}
		template<bsize sizeBuffer>
		static inline void Copy(bchar(&dst)[sizeBuffer], const  bchar *src)
		{
#ifdef UNICODE
			wcscpy_s(dst, sizeBuffer, src);
#else
			strcpy_s(dst, sizeBuffer, src);
#endif
		}
		static inline void Copy(bchar*dst,bsize sizeBuffer, const  bchar *src)
		{
#ifdef UNICODE
			wcscpy_s(dst, sizeBuffer, src);
#else
			strcpy_s(dst, sizeBuffer, src);
#endif
		}

		static inline const bchar* ToChar(const bchar* str, bchar ch)
		{
#ifdef UNICODE
			return wcschr(str, ch);
#else
			return strchr(str, ch);
#endif
		}
		static inline  bchar* ToChar(bchar* str, bchar ch)
		{
#ifdef UNICODE
			return wcschr(str, ch);
#else
			return strchr(str, ch);
#endif
		}
		static inline const bchar* ToCharWithEnd(const bchar* str, bchar ch)
		{
			const bchar*end = str + GetSize(str);
			const bchar*find = bear_find_if_of_end(str, end, [ch](bchar item) {return item == ch; });
			if (find == end)
			{
				return 0;
			}
			return find;
		}
		static inline  bchar* ToCharWithEnd(bchar* str, bchar ch)
		{
			bchar*end = str + GetSize(str);
			bchar*find = bear_find_if_of_end(str, end, [ch](bchar item) {return item == ch; });
			if (find == end)
			{
				return 0;
			}
			return find;
		}
		static inline const bchar* Find(const bchar* str, const  bchar *subStr)
		{
#ifdef UNICODE
			return wcsstr(str, subStr);
#else
			return strstr(str, subStr);
#endif
		}
		static inline bchar* Find(bchar* str, const bchar *subStr)
		{
#ifdef UNICODE
			return wcsstr(str, subStr);
#else
			return strstr(str, subStr);
#endif
		}
		static inline bchar* FindWithEnd(bchar* str, const bchar *subStr)
		{
			bsize sizeSubStr = GetSize(subStr);
			bchar*end = str + GetSize(str);
			bchar*find = bear_find_if_of_end(str, end, [subStr, sizeSubStr](const bchar&item) {return bear_compare(&item, subStr, sizeSubStr) == 0; });
			if (find == end)
			{
				return 0;
			}
			return find;
		}
		static inline const bchar* FindWithEnd(const bchar* str, const bchar *subStr)
		{
			bsize sizeSubStr = GetSize(str);
			const bchar*end = str + GetSize(str);
			const bchar*find = bear_find_if_of_end(str, end, [subStr, sizeSubStr](const bchar&item) {return bear_compare(&item, subStr, sizeSubStr) == 0; });
			if (find == end)
			{
				return 0;
			}
			return find;
		}
		template<bsize sizeBuffer>
		static inline void Printf(bchar(&dst)[sizeBuffer], const bchar*str, ...)
		{
			va_list va;
			va_start(va, str);
#ifdef UNICODE
			vswprintf_s(dst, sizeBuffer, str, va);
#else
			vsprintf_s(dst, sizeBuffer, str, va);
#endif
			va_end(va);
		}
		static inline void Scanf(const bchar*text, const bchar*str, ...)
		{
			va_list va;
			va_start(va, str);
#ifdef UNICODE
			vswscanf(text, str, va);
#else
			vsscanf(text, str, va);
#endif
			va_end(va);
		}
		static inline const bchar* SubSpaceInBegin(const bchar*text)
		{
			while (true)
			{
				if (*text == TEXT('\n') || *text == TEXT('\r') || *text == TEXT(' ') || *text == TEXT('\t'))
					text++;
				else
					return text;
			}
		}
		static inline bchar* SubSpaceInBegin(bchar*text)
		{
			while (*text)
			{
				if (*text == TEXT('\n') || *text == TEXT('\r') || *text == TEXT(' ') || *text == TEXT('\t'))
					text++;
				else
					return text;
			}
			return text;
		}
		static inline bchar* SubSpaceInEnd(bchar*text)
		{
			bchar*end = text + GetSize(text);
			if (text != end)end--;
			while (text <= end)
			{
				if (*end == TEXT('\n') || *end == TEXT('\r') || *end == TEXT(' ') || *end == TEXT('\t'))
				{
					*end = 0;
					end--;

				}
				else
				{
					return text;
				}
			}
			return text;
		}
		template<bsize sizeBuffer>
		static inline const bchar* ReadTo(const bchar*text, bchar ch, bchar(&out)[sizeBuffer])
		{
			const bchar*end = ToChar(text, ch);
			if (end)
			{
				bsize size = end - text;
				if (size > sizeBuffer - 1)
				{
					size = sizeBuffer - 1;
				}
				bear_copy(out, text, size);
				out[size] = 0;
				return text + size+1;
			}
			else
			{
				Copy(out, text);
				return text + GetSize(text);
			}
		}
		template<bsize sizeBuffer>
		static inline bchar* ReadTo(bchar*text, bchar ch, bchar(&out)[sizeBuffer])
		{
			bchar*end = ToChar(text, ch);
			if (end)
			{
				bsize size = end - text;
				if (size > sizeBuffer - 1)
				{
					size = sizeBuffer - 1;
				}
				bear_copy(out, text, size);
				out[size] = 0;
				return text + size+1;
			}
			else
			{
				Copy(out, text);
				return text + GetSize(text);
			}
		}

		template<bsize sizeBuffer>
		static inline const bchar* ReadTo(const bchar*text, const bchar* substr, bchar(&out)[sizeBuffer])
		{
			const bchar*end = Find(text, substr);
			if (end)
			{
				bsize size = end - text;
				if (size > sizeBuffer - 1)
				{
					size = sizeBuffer - 1;
				}
				bear_copy(out, text, size);
				out[size] = 0;
				return text + size + GetSize(substr);
			}
			else
			{
				Copy(out, text);
				return text + GetSize(text);
			}
		}

		template<bsize sizeBuffer>
		static inline bchar* ReadTo(bchar*text, const bchar* substr, bchar(&out)[sizeBuffer])
		{
			bchar*end = Find(text, substr);
			if (end)
			{
				bsize size = end - text;
				if (size > sizeBuffer - 1)
				{
					size = sizeBuffer - 1;
				}
				bear_copy(out, text, size);
				out[size] = 0;
				return text + size + GetSize(substr);
			}
			else
			{
				Copy(out, text);
				return text + GetSize(text);
			}
		}


		static inline bsize CountElement(const bchar*text, const bchar* substr)
		{
			bsize count = 0;
			while (text)
			{
				text = Find(text, substr);
				if (text)
				{
					count++;
					text++;
				}
			}
			return count;
		}
		static inline bsize CountElement(const bchar*text, bchar ch)
		{
			bsize count = 0;
			while (text)
			{
				text = ToChar(text, ch);
				if (text)
				{
					count++;
					text++;
				}
			}
			return count;
		}


		static inline bool Exist(const bchar*text, const bchar* substr)
		{
			return Find(text, substr);
		}
		static inline bool ExistPossition(const bchar*text, bsize pos, const bchar*substr)
		{
			return bear_compare(text + pos, substr, GetSize(substr)) == 0;
		}
		template<bsize sizeBuffer>
		static inline void GetElement(const bchar*text, bchar element, bsize id, bchar(&out)[sizeBuffer])
		{
			if (id)
			{
				while (id)
				{
					text = ToChar(text, element) + 1;
					id--;
				}
			}
			ReadTo(text, element, out);
		}
		template<bsize sizeBuffer>
		static inline void GetElement(const bchar*text, const bchar *element, bsize id, bchar(&out)[sizeBuffer])
		{
			bsize selement = GetSize(element);
			if (id)
			{
				while (id)
				{
					text = Find(text, element) + selement;
					id--;
				}
			}
			ReadTo(text, element, out);
		}
		static inline void  ToLower(bchar* str)
		{
#ifdef UNICODE
			_wcslwr_s(str, GetSize(str) + 1);
#else
			_strlwr_s(str, GetSize(str) + 1);
#endif
		}
		static inline void  ToUpper(bchar* str)
		{
#ifdef UNICODE
			_wcsupr_s(str, GetSize(str) + 1);
#else
			_strupr_s(str, GetSize(str) + 1);
#endif
		}
	public:

		BearString() :basic_string(),m_tell(0) {}
		BearString(const bchar*text):basic_string(text),m_tell(0){}
		BearString(const BearString&string ) :basic_string(string),m_tell(string.m_tell) {}
		BearString(BearString&&string) :basic_string(), m_tell(0) { swap(string); }
		inline void swap(BearString&str) { basic_string::swap(str); bear_swap(m_tell, str.m_tell); }
		inline void copy(const BearString& str){ basic_string::operator=(str);  m_tell=str.m_tell; }
		inline 	BearString&operator=(const BearString&str) { copy(str); return*this; }
		inline 	BearString&operator=(BearString&&str) { swap(str); return*this; }
		inline	void seek(bsize tell)
		{
			if (size()+m_tell > tell)m_tell = tell;
			else m_tell = size() + m_tell;
		}
		inline	bsize tell()const
		{
			return m_tell;
		}
		inline void	operator++(int) { seek(m_tell + 1); }
		inline void	operator--(int) {if(m_tell) seek(m_tell - 1); }
		inline const bchar* operator*() const
		{
			if (!basic_string::size())return TEXT("");
			return &at(m_tell);
		}
		inline bchar* operator*()
		{
			if (!basic_string::size())return TEXT("");
			return &at(m_tell);
		}


		inline bsize size() const
		{
			return GetSize(**this);
		}
		inline bool to_char(bchar ch)
		{
			const bchar*begin = **this;
			const bchar*item = 0;
#ifdef UNICODE
			item = wcschr(begin, ch);
#else
			item = strchr(begin, ch);
#endif
			if (!item) {
				seek(size() + m_tell);
				return false;
			}
			else
			{
				seek(item - begin + m_tell);
				return true;
			}
			return true;

		}
		inline bool to_char_with_end(bchar ch)
		{
			const bchar*begin = **this;
			const bchar*end = begin + size();
			const bchar*find = bear_find_if_of_end(begin, end, [ch](bchar item) {return item == ch; });
			seek(find - begin + m_tell);
			if (find == end)return false;
			return true;
		}
		
		inline bool find(const  bchar *subStr)
		{
			bchar*begin = **this;
			//bchar*end = begin + size();
			bchar*item = 0;
#ifdef UNICODE
			item = wcsstr(begin, subStr);
#else
			item = strstr(begin, subStr);
#endif
		
			if (!item) {
				seek(size() + m_tell);
				return false;
			}
			else
			{
				seek(item - begin + m_tell);
				return true;
			}
			return true;
		}
		inline void find_with_end( const bchar *subStr)
		{
			bsize sizeSubStr = GetSize(subStr);
			bchar*end = **this+ size();
			bchar*find = bear_find_if_of_end(**this, end, [subStr, sizeSubStr](const bchar&item) {return bear_compare(&item, subStr, sizeSubStr) == 0; });
			if (find == end)
			{
				seek(m_tell + size());
			}
			seek(find - **this + m_tell);
		}
		template<typename...A>
		inline void append_printf(const bchar*str, A&...a)
		{
			BearString8192 out;
			Printf(out, str, a...);
			append(out);
		}
		template<typename...A>
		inline void scanf(const bchar*str, A...a)const
		{
			Scanf(**this, str, a...);
		}
		inline void sub_space_in_begin()
		{
			bchar*begin = **this;
			bchar*item=	SubSpaceInBegin(begin);
			seek(item - begin + m_tell);
		}
		inline void sub_space_in_end()
		{
			bchar*end = **this+size();
			SubSpaceInEnd(end);
		}
		template<bsize sizeBuffer>
		inline void read_to( bchar ch, bchar(&out)[sizeBuffer])
		{
			const bchar*text = **this;
			const bchar*end = ToChar(text, ch);
			if (end)
			{
				bsize size = end - text;
				if (size > sizeBuffer - 1)
				{
					size = sizeBuffer - 1;
				}
				bear_copy(out, text, size);
				out[size] = 0;
				return seek(m_tell+ size + 1);
			}
			else
			{
				Copy(out, text);
				return seek(m_tell + size());
			}
		}

		inline void read_to(bchar ch,BearString&out)
		{
			const bchar*text = **this;
			const bchar*end = ToChar(text, ch);
			if (end)
			{
				bsize size = end - text;
				out.assign( text, size);
				return seek(m_tell + size + 1);
			}
			else
			{
				out.assign(text);
				return seek(m_tell + size());
			}
		}
		template<bsize sizeBuffer>
		inline void read_to(const bchar* subStr, bchar(&out)[sizeBuffer])
		{
			const bchar*text = **this;
			const bchar*end = Find(text, subStr);
			if (end)
			{
				bsize size = end - text;
				if (size > sizeBuffer - 1)
				{
					size = sizeBuffer - 1;
				}
				bear_copy(out, text, size);
				out[size] = 0;
				return seek(m_tell + size + GetSize(subStr));
			}
			else
			{
				Copy(out, text);
				return seek(m_tell + size());
			}
		}

		inline void read_to(const bchar* subStr, BearString&out)
		{
			const bchar*text = **this;
			const bchar*end = Find(text, subStr);
			if (end)
			{
				bsize size = end - text;
				out.assign(text, size);
				return seek(m_tell + size + GetSize(subStr));
			}
			else
			{
				out.assign(text);
				return seek(m_tell + size());
			}
		}

		inline bsize count_element( const bchar* substr)
		{
			 return CountElement(**this, substr);
		}
		inline bsize count_element(bchar ch)
		{
			return CountElement(**this, ch);
		}
		inline bool exist(const bchar* substr)
		{
			return Find(**this, substr);
		}
		inline bool exist_possition( bsize pos, const bchar*substr)
		{
			return ExistPossition(**this, pos, substr);
		}
		inline void get_element(bchar element, bsize id, BearString&str)
		{
			bsize tl = tell();
			if (id)
			{
				while (id)
				{
					to_char(element);
					seek(m_tell + 1);
					id--;
				}
			}
			read_to(element, str);
			seek(tl);
		}
		inline void get_element(const bchar *element, bsize id, BearString&str)
		{
			bsize selement = GetSize(element);
			bsize tl = tell();
			if (id)
			{
				while (id)
				{
					find(element);
					seek(m_tell + selement);
					id--;
				}
			}
			read_to(element, str);
			seek(tl);
		}
		template<bsize sizeBuffer>
		inline void get_element(const bchar *element, bsize id, bchar(&out)[sizeBuffer])
		{
			GetElement(**this, element, id, out);
		}
		template<bsize sizeBuffer>
		inline void get_element(bchar element, bsize id, bchar(&out)[sizeBuffer])
		{
			GetElement(**this, element, id, out);
		}
		inline void clear()
		{
			m_tell = 0;
			basic_string::clear();
		}
		inline void clear_no_free()
		{
			m_tell = 0;
			if(basic_string::size())
				at(0) = 0;
			this->_Get_data()._Mysize = 0;
		}
		BEAR_FUNCTION_DELETE(const bchar*, c_str);
		BEAR_FUNCTION_DELETE(size_type, find_first_not_of);
		BEAR_FUNCTION_DELETE(size_type, find_first_of);
		BEAR_FUNCTION_DELETE(size_type, find_last_not_of);
		BEAR_FUNCTION_DELETE(size_type, find_last_of);

		static  BearPtr<bchar8> ConvertToANSI(const bchar8* text);
		static  BearPtr<bchar8> ConvertToANSI(const bchar16* text);
		static  BearPtr<bchar8> ConvertUTF8ToANSI(const bchar8* UTF8);

		static BearPtr<bchar16> ConvertToUTF16(const bchar8* text);
		static BearPtr<bchar16> ConvertUTF8ToUTF16(const bchar8* UTF8);
		static BearPtr<bchar16> ConvertToUTF16(const bchar16* text);

		static BearPtr<bchar8> ConvertToANSI(const bchar8* text, bsize size);
		static BearPtr<bchar8> ConvertToANSI(const bchar16* text, bsize size);
		static BearPtr<bchar8> ConvertUTF8ToANSI(const bchar8* UTF8, bsize size);

		static BearPtr<bchar16> ConvertToUTF16(const bchar8* text, bsize size);
		static BearPtr<bchar16> ConvertUTF8ToUTF16(const bchar8* UTF8, bsize size);
		static BearPtr<bchar16> ConvertToUTF16(const bchar16* text, bsize size);



		static BearPtr<bchar8>  ConvertToUTF8(const bchar8* text);
		static BearPtr<bchar8>  ConvertToUTF8(const bchar16* text);
		private:
			bsize m_tell;
	};
	
};