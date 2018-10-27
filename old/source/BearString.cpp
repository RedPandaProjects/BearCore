#include "BearCore.hpp"
uint32 GANSICodePage = 1251;
static BearCore::BearPtr<bchar8> ConvertToANSI(const bchar16 *text, bsize size)
{

	bchar8 * res = BearCore::bear_alloc<bchar8>(size + 1);
	WideCharToMultiByte(GANSICodePage, 0, text, -1, res, static_cast<int>(size), NULL, 0);
	res[size] = 0;
	return res;

}

static BearCore::BearPtr<bchar16>  ConvertToUTF16(const bchar8 *text, bsize size)
{

	bchar16 * res= BearCore::bear_alloc<bchar16>(size + 1);;
	int32 res_len = static_cast<int32>(size);

	MultiByteToWideChar(GANSICodePage, 0, text, res_len, res, res_len);
	res[size] = 0;
	return res;
}
static BearCore::BearPtr<bchar8> ConvertToANSI(const bchar8 *text, bsize size)
{
	return BearCore::BearPtr<bchar8>((bchar8*)text, false);
}
static BearCore::BearPtr<bchar16> ConvertToUTF16(const bchar16 *text, bsize size)
{
	return BearCore::BearPtr<bchar16>((bchar16*)text, false);
}

static BearCore::BearPtr<bchar16> ConvertUTF8ToUTF16(const bchar8*pointer, bsize size)
{
	size_t i = 0;
	BearCore::BearVector<bchar16> unicodeToUrf8;
	while (i < size)
	{
		unsigned long uni;
		size_t todo;
		bool error = false;
		unsigned char ch = pointer[i++];
		if (ch <= 0x7F)
		{
			uni = ch;
			todo = 0;
		}
		else if (ch <= 0xBF)
		{
			return 0;
		}
		else if (ch <= 0xDF)
		{
			uni = ch & 0x1F;
			todo = 1;
		}
		else if (ch <= 0xEF)
		{
			uni = ch & 0x0F;
			todo = 2;
		}
		else if (ch <= 0xF7)
		{
			uni = ch & 0x07;
			todo = 3;
		}
		else
		{
			unicodeToUrf8.push_back(L'\0');
			return unicodeToUrf8.popData();
		}
		for (size_t j = 0; j < todo; ++j)
		{
			if (i == size)
			{
				unicodeToUrf8.push_back(L'\0');
				return unicodeToUrf8.popData();
			}
			unsigned char ch = pointer[i++];
			if (ch < 0x80 || ch > 0xBF)
			{
				unicodeToUrf8.push_back(L'\0');
				return unicodeToUrf8.popData();
			}
			uni <<= 6;
			uni += ch & 0x3F;
		}
		if (uni >= 0xD800 && uni <= 0xDFFF)
		{
			unicodeToUrf8.push_back(L'\0');
			return unicodeToUrf8.popData();
		}
		if (uni > 0x10FFFF)
		{
			unicodeToUrf8.push_back(L'\0');
			return unicodeToUrf8.popData();
		}
		if (uni <= 0xFFFF)
		{
			unicodeToUrf8.push_back((bchar16)uni);
		}
		else
		{
			uni -= 0x10000;
			unicodeToUrf8.push_back((bchar16)((uni >> 10) + 0xD800));
			unicodeToUrf8.push_back((bchar16)((uni & 0x3FF) + 0xDC00));
		}
	}
	unicodeToUrf8.push_back(L'\0');
	return unicodeToUrf8.popData();
}


static BearCore::BearPtr<bchar8>  ConvertToUTF8(const bchar16* pszTextUTF16) {
	if (pszTextUTF16 == NULL) return BearCore::bear_new<bchar8>(1);

	int utf16len = static_cast<int>(wcslen(pszTextUTF16));
	int utf8len = WideCharToMultiByte(CP_UTF8, 0, pszTextUTF16, utf16len,
		NULL, 0, NULL, NULL);

	bchar8 *utf8= BearCore::bear_alloc<bchar8>(utf8len);;

	WideCharToMultiByte(CP_UTF8, 0, pszTextUTF16, utf16len,
		(LPSTR)utf8, utf8len, 0, 0);
	return utf8;
}


BearCore::BearPtr<bchar8> BearCore::BearString::ConvertToANSI(const bchar8 * text)
{
	return ::ConvertToANSI(text, GetSize(text));
}

BearCore::BearPtr<bchar8> BearCore::BearString::ConvertToANSI(const bchar16 * text)
{
	return ::ConvertToANSI(text, GetSize(text));
}

BearCore::BearPtr<bchar8> BearCore::BearString::ConvertUTF8ToANSI(const bchar8 * utf8)
{
	return ConvertToANSI(*ConvertUTF8ToUTF16(utf8));
}

BearCore::BearPtr<bchar16> BearCore::BearString::ConvertToUTF16(const bchar8 * text)
{
	return ::ConvertToUTF16(text,GetSize(text));
}

BearCore::BearPtr<bchar16> BearCore::BearString::ConvertUTF8ToUTF16(const bchar8 * utf8)
{
	return ::ConvertUTF8ToUTF16(utf8, GetSize(utf8));
}

BearCore::BearPtr<bchar16> BearCore::BearString::ConvertToUTF16(const bchar16 * text)
{
	return ::ConvertToUTF16(text, GetSize(text));
}

BearCore::BearPtr<bchar8> BearCore::BearString::ConvertToANSI(const bchar8 * text, bsize size)
{
	return ::ConvertToANSI(text,size);
}

BearCore::BearPtr<bchar8> BearCore::BearString::ConvertToANSI(const bchar16 * text, bsize size)
{
	return ::ConvertToANSI(text, size);
}

BearCore::BearPtr<bchar8> BearCore::BearString::ConvertUTF8ToANSI(const bchar8 * utf8, bsize size)
{
	return  ConvertToANSI(*ConvertUTF8ToUTF16(utf8,size));
}

BearCore::BearPtr<bchar16> BearCore::BearString::ConvertToUTF16(const bchar8 * text, bsize size)
{
	return ::ConvertToUTF16(text, size);
}

BearCore::BearPtr<bchar16> BearCore::BearString::ConvertUTF8ToUTF16(const bchar8 * utf8, bsize size)
{
	return ::ConvertUTF8ToUTF16(utf8, size);
}

BearCore::BearPtr<bchar16> BearCore::BearString::ConvertToUTF16(const bchar16 * text, bsize size)
{
	return ::ConvertToUTF16(text, size);
}

BearCore::BearPtr<bchar8> BearCore::BearString::ConvertToUTF8(const bchar8 * text)
{
	return ConvertToUTF8(*ConvertToUTF16(text));
}

BearCore::BearPtr<bchar8> BearCore::BearString::ConvertToUTF8(const bchar16 * text)
{
	return ::ConvertToUTF8(text);
}
