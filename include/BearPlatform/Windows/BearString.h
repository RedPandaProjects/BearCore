#pragma once
namespace BearCore
{
	inline bsize BearString::GetSize(const bchar8*text)
	{
		return strlen(text);
	}
	inline bsize BearString::GetSize(const bchar16*text)
	{
		return wcslen(text);
	}
	template<bsize sizeBuffer>
	inline void BearString::Contact(bchar(&dst)[sizeBuffer], const  bchar *src)
	{
#ifdef UNICODE
		wcscat_s(dst, sizeBuffer, src);
#else
		strcat_s(dst, sizeBuffer, src);
#endif
	}
	template<bsize sizeBuffer>
	inline void BearString::Copy(bchar(&dst)[sizeBuffer], const  bchar *src)
	{
#ifdef UNICODE
		wcscpy_s(dst, sizeBuffer, src);
#else
		strcpy_s(dst, sizeBuffer, src);
#endif
	}
	inline void BearString::Copy(bchar*dst, bsize sizeBuffer, const  bchar *src)
	{
#ifdef UNICODE
		wcscpy_s(dst, sizeBuffer, src);
#else
		strcpy_s(dst, sizeBuffer, src);
#endif
	}

	inline const bchar* BearString::ToChar(const bchar* str, bchar ch)
	{
#ifdef UNICODE
		return wcschr(str, ch);
#else
		return strchr(str, ch);
#endif
	}
	inline  bchar* BearString::ToChar(bchar* str, bchar ch)
	{
#ifdef UNICODE
		return wcschr(str, ch);
#else
		return strchr(str, ch);
#endif
	}
	inline const bchar* BearString::ToCharWithEnd(const bchar* str, bchar ch)
	{
		const bchar*end = str + GetSize(str);
		const bchar*find = bear_find_if_of_end(str, end, [ch](bchar item) {return item == ch; });
		if (find == end)
		{
			return 0;
		}
		return find;
	}
	inline  bchar* BearString::ToCharWithEnd(bchar* str, bchar ch)
	{
		bchar*end = str + GetSize(str);
		bchar*find = bear_find_if_of_end(str, end, [ch](bchar item) {return item == ch; });
		if (find == end)
		{
			return 0;
		}
		return find;
	}
	inline const bchar* BearString::Find(const bchar* str, const  bchar *subStr)
	{
#ifdef UNICODE
		return wcsstr(str, subStr);
#else
		return strstr(str, subStr);
#endif
	}
	inline bchar* BearString::Find(bchar* str, const bchar *subStr)
	{
#ifdef UNICODE
		return wcsstr(str, subStr);
#else
		return strstr(str, subStr);
#endif
	}

	template<bsize sizeBuffer>
	inline void BearString::Printf(bchar(&dst)[sizeBuffer], const bchar*str, ...)
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
	inline void BearString::Scanf(const bchar*text, const bchar*str, ...)
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
	 inline void  BearString::ToLower(bchar* str)
	{
#ifdef UNICODE
		_wcslwr_s(str, wcslen(str) + 1);
#else
		_strlwr_s(str, wcslen(str) + 1);
#endif
	}
	 inline void  BearString::ToUpper(bchar* str)
	{
#ifdef UNICODE
		_wcsupr_s(str,wcslen(str)+1);
#else
		_strupr_s(str, stren(str) + 1);
#endif
	}
	 inline int32   BearString::Compare(const bchar*str1, const bchar*str2)
	{
#ifdef UNICODE
		return wcscmp(str1,str2);
#else
		return strcmp(str1, str2);
#endif
	}
};
#define BEAR_PATH TEXT("\\")