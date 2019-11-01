
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
	inline void BearString::Contact(bchar8(&dst)[sizeBuffer], const  bchar8 *src)
	{
		strcat_s(dst, sizeBuffer, src);
	}

	inline void BearString::Contact(bchar8*dst, bsize sizeBuffer, const  bchar8 *src)
	{
		strcat_s(dst, sizeBuffer, src);

	}
	template<bsize sizeBuffer>
	inline void BearString::Contact(bchar16(&dst)[sizeBuffer], const  bchar16 *src)
	{
		wcscat_s(dst, sizeBuffer, src);
	}
	inline void BearString::Contact(bchar16*dst, bsize sizeBuffer, const  bchar16 *src)
	{
		wcscat_s(dst, sizeBuffer, src);

	}

	template<bsize sizeBuffer>
	inline void BearString::Copy(bchar16(&dst)[sizeBuffer], const  bchar16 *src)
	{
		wcscpy_s(dst, sizeBuffer, src);
	}
	inline void BearString::Copy(bchar16*dst, bsize sizeBuffer, const  bchar16 *src)
	{
		wcscpy_s(dst, sizeBuffer, src);
		
	}
	template<bsize sizeBuffer>
	inline void BearString::Copy(bchar8(&dst)[sizeBuffer], const  bchar8 *src)
	{
		strcpy_s(dst, sizeBuffer, src);
	}
	inline void BearString::Copy(bchar8*dst, bsize sizeBuffer, const  bchar8 *src)
	{
		strcpy_s(dst, sizeBuffer, src);
	}
	
	inline const bchar8* BearString::ToChar(const bchar8* str, bchar8 ch)
	{
		return strchr(str, ch);
	}
	inline  bchar8* BearString::ToChar(bchar8* str, bchar8 ch)
	{
		return strchr(str, ch);
	}
	inline const bchar8* BearString::ToCharWithEnd(const bchar8* str, bchar8 ch)
	{
		const bchar8*end = str + GetSize(str);
		const bchar8*find = bear_find_if_of_end(str, end, [ch](bchar8 item) {return item == ch; });
		if (find == end)
		{
			return 0;
		}
		return find;
	}
	inline  bchar8* BearString::ToCharWithEnd(bchar8* str, bchar8 ch)
	{
		bchar8*end = str + GetSize(str);
		bchar8*find = bear_find_if_of_end(str, end, [ch](bchar8 item) {return item == ch; });
		if (find == end)
		{
			return 0;
		}
		return find;
	}


	inline const bchar16* BearString::ToChar(const bchar16* str, bchar16 ch)
	{
		return wcschr(str, ch);
	}
	inline  bchar16* BearString::ToChar(bchar16* str, bchar16 ch)
	{
		return wcschr(str, ch);
	}
	inline const bchar16* BearString::ToCharWithEnd(const bchar16* str, bchar16 ch)
	{
		const bchar16*end = str + GetSize(str);
		const bchar16*find = bear_find_if_of_end(str, end, [ch](bchar16 item) {return item == ch; });
		if (find == end)
		{
			return 0;
		}
		return find;
	}
	inline  bchar16* BearString::ToCharWithEnd(bchar16* str, bchar16 ch)
	{
		bchar16*end = str + GetSize(str);
		bchar16*find = bear_find_if_of_end(str, end, [ch](bchar16 item) {return item == ch; });
		if (find == end)
		{
			return 0;
		}
		return find;
	}


	inline const bchar8* BearString::Find(const bchar8* str, const  bchar8 *subStr)
	{
		return strstr(str, subStr);
	}
	inline bchar8* BearString::Find(bchar8* str, const bchar8 *subStr)
	{
		return strstr(str, subStr);
	}

	inline const bchar16* BearString::Find(const bchar16* str, const  bchar16 *subStr)
	{
		return wcsstr(str, subStr);
	}
	inline bchar16* BearString::Find(bchar16* str, const bchar16 *subStr)
	{
		return wcsstr(str, subStr);
	}

	template<bsize sizeBuffer>
	inline bsize BearString::Printf(bchar8(&dst)[sizeBuffer], const bchar8*str, ...)
	{
		va_list va;
		va_start(va, str);
		int result = vsprintf_s(dst, sizeBuffer, str, va);
		va_end(va);
		return static_cast<bsize>(result);
	}
	template<bsize sizeBuffer>
	inline bsize BearString::PrintfVa(bchar8(&dst)[sizeBuffer], const bchar8*str, va_list va)
	{
		int result =  vsprintf_s(dst, sizeBuffer, str, va);
		return static_cast<bsize>(result);
	}

	inline bsize  BearString::Printf(bchar8*dst, bsize sizeBuffer, const bchar8*str, ...)
	{

		va_list va;
		va_start(va, str);
		int result = vsprintf_s(dst, sizeBuffer, str, va);
		va_end(va);
		return static_cast<bsize>(result);
	}
	inline bsize  BearString::PrintfVa(bchar8*dst, bsize sizeBuffer, const bchar8*str, va_list va)
	{
		int result =  vsprintf_s(dst, sizeBuffer, str, va);
		return static_cast<bsize>(result);
	}

	template<bsize sizeBuffer>
	inline bsize BearString::Printf(bchar16(&dst)[sizeBuffer], const bchar16*str, ...)
	{
		va_list va;
		va_start(va, str);
		int result =  vswprintf_s(dst, sizeBuffer, str, va);
		va_end(va);
		return static_cast<bsize>(result);
	}
	template<bsize sizeBuffer>
	inline bsize BearString::PrintfVa(bchar16(&dst)[sizeBuffer], const bchar16*str, va_list va)
	{
		int result =  vswprintf_s(dst, sizeBuffer, str, va);
		return static_cast<bsize>(result);
	}
	inline bsize  BearString::Printf(bchar16*dst, bsize sizeBuffer, const bchar16*str, ...)
	{

		va_list va;
		va_start(va, str);
		int result =  vswprintf_s(dst, sizeBuffer, str, va);
		va_end(va);
		return static_cast<bsize>(result);
	}
	inline bsize  BearString::PrintfVa(bchar16*dst, bsize sizeBuffer, const bchar16*str, va_list va)
	{
		int result = vswprintf_s(dst, sizeBuffer, str, va);
		return static_cast<bsize>(result);
	}
	template<bsize sizeBuffer>
	inline bsize BearString::Printf(bchar_utf8(&dst)[sizeBuffer], const bchar_utf8*str, ...)
	{
		va_list va;
		va_start(va, str);
		int result =  vsprintf_s((char*)dst, sizeBuffer,(const char*)str, va);
		va_end(va);
		return static_cast<bsize>(result);
	}
	template<bsize sizeBuffer>
	inline bsize BearString::PrintfVa(bchar_utf8(&dst)[sizeBuffer], const bchar_utf8*str, va_list va)
	{
		int result =  vsprintf_s((char*)dst, sizeBuffer, (const char*)str, va);
		return static_cast<bsize>(result);
	}
	inline bsize  BearString::Printf(bchar_utf8*dst, bsize sizeBuffer, const bchar_utf8*str, ...)
	{

		va_list va;
		va_start(va, str);
		int result =  vsprintf_s((char*)dst, sizeBuffer, (const char*)str, va);
		va_end(va);
		return static_cast<bsize>(result);
	}
	inline bsize  BearString::PrintfVa(bchar_utf8*dst, bsize sizeBuffer, const bchar_utf8*str, va_list va)
	{
		int result =  vsprintf_s((char*)dst, sizeBuffer, (const char*)str, va);
		return static_cast<bsize>(result);
	}


	inline int32 BearString::Scanf(const bchar8*text, const bchar8*str, ...)
	{
		va_list va;
		va_start(va, str);
		int32 result = vsscanf(text, str, va);
		va_end(va);
		return result;
	}
	inline int32 BearString::Scanf(const bchar16*text, const bchar16*str, ...)
	{
		va_list va;
		va_start(va, str);
		int32 result = vswscanf(text, str, va);
		va_end(va);
		return result;
	}
	 inline void  BearString::ToLower(bchar8* str)
	{
		_strlwr_s(str, strlen(str) + 1);
	}
	 inline void  BearString::ToUpper(bchar8* str)
	{
		_strupr_s(str, strlen(str) + 1);
	}
	 inline void  BearString::ToLower(bchar16* str)
	 {
		 _wcslwr_s(str, wcslen(str) + 1);
	 }
	 inline void  BearString::ToUpper(bchar16* str)
	 {
		 _wcsupr_s(str, wcslen(str) + 1);
	 }
	 inline int32   BearString::Compare(const bchar8*str1, const bchar8*str2)
	{
		return strcmp(str1, str2);
	}
	 inline int32   BearString::Compare(const bchar16*str1, const bchar16*str2)
	 {
		 return wcscmp(str1, str2);
	 }
	 inline int32  BearString::CompareWithoutCase(const bchar8*str1, const bchar8*str2)
	 {
		 return _stricmp(str1, str2);
	 }
	 inline int32   BearString::CompareWithoutCase(const bchar16*str1, const bchar16*str2)
	 {
		 return _wcsicmp(str1, str2);
	 }

	 



	 template<bsize sizeBuffer>
	 inline void BearString::CopyWithSizeLimit(bchar16(&dst)[sizeBuffer], const  bchar16 *src,bsize size)
	 {
		 wcsncpy_s(dst, sizeBuffer, src, size);
	 }
	 inline void BearString::CopyWithSizeLimit(bchar16*dst, bsize sizeBuffer, const  bchar16 *src, bsize size)
	 {
		 wcsncpy_s(dst, sizeBuffer, src,size);

	 }
	 template<bsize sizeBuffer>
	 inline void BearString::CopyWithSizeLimit(bchar8(&dst)[sizeBuffer], const  bchar8 *src, bsize size)
	 {
		 strncpy_s(dst, sizeBuffer, src, size);
	 }
	 inline void BearString::CopyWithSizeLimit(bchar8*dst, bsize sizeBuffer, const  bchar8 *src, bsize size)
	 {
		 strncpy_s(dst, sizeBuffer, src, size);
	 }
	 
};
#define BEAR_PATH TEXT("\\")