#include "BearCore.hpp"
#include <codecvt>
#include <string>
#include <locale>

template <typename I, typename E, typename S>
struct codecvt : public std::codecvt<I, E, S>
{
	~codecvt()
	{
	}
};
template <typename I, typename E, typename S>
struct codecvt_byname : public std::codecvt_byname<I, E, S>
{
	codecvt_byname(const char *l) : std::codecvt_byname<I, E, S>(l) {}
	~codecvt_byname()
	{
	}
};

std::wstring_convert<::codecvt_byname<bchar16, bchar8, std::mbstate_t>, bchar16> *ConverterUTF16;
std::wstring_convert<std::codecvt_utf8_utf16<bchar16>, bchar16> *ConverterUTF8;

#if defined(WINDOWS) || defined(UNIX)
static uint32 LAnsiCode = 1251; /*RUS*/
;
#endif

struct Initializer
{
	Initializer() {}
	inline void Initialize(const char *lg = "en_US.UTF-8")
	{
		if (ConverterUTF16)
		{
			return;
		}
		ReInitialize(lg);
	}
	inline void ReInitialize(const char *lg = "en_US.UTF-8")
	{
		if (ConverterUTF16)
		{
			BearCore::bear_delete(ConverterUTF16);
			BearCore::bear_delete(ConverterUTF8);
		}
		ConverterUTF16 = new std::wstring_convert<::codecvt_byname<bchar16, bchar8, std::mbstate_t>, bchar16>(new ::codecvt_byname<bchar16, bchar8, std::mbstate_t>(lg));
		ConverterUTF8 = new std::wstring_convert<std::codecvt_utf8_utf16<bchar16>, bchar16>;
	}
	~Initializer()
	{
		BearCore::bear_delete(ConverterUTF16);
		BearCore::bear_delete(ConverterUTF8);
	}
};
Initializer initializer;

inline bchar8 ToANSI(bchar16 c)
{

	if ((bchar16)(bchar8)c != c)
	{  
#ifdef UNIX
		if (LAnsiCode == 1251)
		{ 
			if (c >= L'А' && c <= L'Я'+32)
				return ((bchar8)(c - L'А')) + 0xC0;
			if (c >= L'а' && c <= L'я'+32)
				return ((bchar8)(c - L'а')) + 0xE0;
			if (c == L'ё')
				return 0xB8;
			if (c ==L'Ё' )
				return 0xA8;
		}
		return L'?';
#else
		initializer.Initialize();
		return ConverterUTF16->to_bytes(c)[0];
#endif
	}
	return (bchar8)c;
}

inline bchar16 ToUTF16(bchar8 c_)
{
	uint8 c=c_;
	if (c>=0x80)
	{
#ifdef WINDOWS
		bchar16 res[2]; 
		MultiByteToWideChar(LAnsiCode, 0, &c_, 2, res, 2);
		return res[0];
#else
		if (LAnsiCode == 1251)
		{
			if (c >= 0xC0 && c <= 0xDF)
				return ((bchar16)(c - 0xC0)) + L'А';
			if (c >= 0xE0 && c <= 0xFF)
				return ((bchar16)(c - 0xE0)) + L'а';
			if (c == 0xB8)
				return L'ё';
			if (c == 0xA8)
				return L'Ё';
		}
#endif
	}
	return (bchar16)c;
}

BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bchar8 *text, const bchar8 *end)
{
	bchar8 *temp = bear_alloc<bchar8>(end - text + 1);
	bear_copy(temp, text, end - text + 1);
	temp[end - text] = 0;
	return BearCore::BearMemoryRef<bchar8>(temp);
}

BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bchar16 *begin, const bchar16 *end)
{
	bchar8 *res = bear_alloc<bchar8>(end - begin + 1);
	res[end - begin] = 0;
	bsize i = 0;
	while (begin != end)
	{
		res[i++] = ::ToANSI(*(begin++));
	}
	return res;
	/*initializer.Initialize();
	std::wstring_convert<::codecvt<bchar16, bchar8, std::mbstate_t>, bchar16> convert;
	std::string str = convert.to_bytes(text, end);
	return ToANSI(&*str.begin(),(&*str.begin())+str.size());*/
}

BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bchar_utf8 *text, const bchar_utf8 *end)
{
	return ToANSI(*ToUTF16(text, end));
}

BearCore::BearMemoryRef<bchar16> BearCore::BearEncoding::ToUTF16(const bchar8 *begin, const bchar8 *end)
{
	bchar16 *res = bear_alloc<bchar16>(end - begin + 1);
	res[end - begin] = 0;
	bsize i = 0;
	while (begin != end)
	{
		res[i++] = ::ToUTF16(*(begin++));
	}
	return res;
	/*
#ifdef WINDOWS
	bchar16  *res = bear_alloc<bchar16>(end - text + 1);
	MultiByteToWideChar(LAnsiCode, 0, text,end-text, res, end - text + 1);
	res[end - text] = 0;
	return res;
#else
	initializer.Initialize();
	std::wstring str = ConverterUTF16->from_bytes(text, end);
	return ToUTF16(&*str.begin(), (&*str.begin())+str.size());
#endif*/
}

BearCore::BearMemoryRef<bchar16> BearCore::BearEncoding::ToUTF16(const bchar16 *begin, const bchar16 *end)
{
	bchar16 *temp = bear_alloc<bchar16>(end - begin + 1);
	bear_copy(temp, begin, end - begin);
	temp[end - begin] = 0;
	return BearCore::BearMemoryRef<bchar16>(temp);
}

BearCore::BearMemoryRef<bchar16> BearCore::BearEncoding::ToUTF16(const bchar_utf8 *text, const bchar_utf8 *end)
{
	initializer.Initialize();
	std::wstring str = ConverterUTF8->from_bytes(reinterpret_cast<const char *>(text), reinterpret_cast<const char *>(end));
	return ToUTF16(&*str.begin(), (&*str.begin()) + str.size());
}

BearCore::BearMemoryRef<bchar_utf8> BearCore::BearEncoding::ToUTF8(const bchar8 *text, const bchar8 *end)
{
	return ToUTF8(*ToUTF16(text, end));
}

BearCore::BearMemoryRef<bchar_utf8> BearCore::BearEncoding::ToUTF8(const bchar16 *text, const bchar16 *end)
{
	initializer.Initialize();
	std::string str = ConverterUTF8->to_bytes(text, end);
	return ToUTF8((const bchar_utf8 *)&*str.begin(), (const bchar_utf8 *)((&*str.begin()) + str.size()));
}

BearCore::BearMemoryRef<bchar_utf8> BearCore::BearEncoding::ToUTF8(const bchar_utf8 *text, const bchar_utf8 *end)
{
	bchar_utf8 *temp = bear_alloc<bchar_utf8>(end - text + 1);
	bear_copy(temp, text, end - text);
	temp[end - text] = 0;
	return BearCore::BearMemoryRef<bchar_utf8>(temp);
}

bchar8 BearCore::BearEncoding::ToANSI(bchar16 c)
{
	return ::ToANSI(c);
}

bchar8 BearCore::BearEncoding::ToANSI(bchar8 c)
{
	return c;
}

bchar16 BearCore::BearEncoding::ToUTF16(bchar16 c)
{
	return c;
}

bchar16 BearCore::BearEncoding::ToUTF16(bchar8 c)
{
	return ::ToUTF16(c);
}

void BearCore::BearEncoding::SetLang(Lang lang)
{
#if defined(WINDOWS) || defined(UNIX)
	switch (lang)
	{
	case BearCore::BearEncoding::E_RUS:
		LAnsiCode = 1251;
		break;
	case BearCore::BearEncoding::E_ENG:
		LAnsiCode = 0;
		break;
	default:
		LAnsiCode = 0;
		break;
	} 
#endif
	switch (lang)
	{
	case BearCore::BearEncoding::E_RUS:
		setlocale(LC_CTYPE, "ru_RU.UTF-8");
#ifdef WINDOWS
		initializer.ReInitialize("Russian");
#else
		initializer.ReInitialize("ru_RU.UTF-8");
#endif

		break;
	case BearCore::BearEncoding::E_ENG:
	default:
		setlocale(LC_CTYPE, "en_US.UTF-8");
		initializer.ReInitialize("en_US.UTF-8");
		break;
	}
	{
	}
	setlocale(LC_NUMERIC, "en_US.UTF-8");
}
