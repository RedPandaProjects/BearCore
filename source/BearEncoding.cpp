#include "BearCore.hpp"
#include <codecvt>
#include <string>
#include <locale>

template<typename I, typename E, typename S>
struct codecvt :public std::codecvt<I, E, S>
{
~codecvt()
{ }
};



std::wstring_convert<::codecvt<bchar16, bchar8, std::mbstate_t>, bchar16>* ConverterUTF16;
std::wstring_convert<std::codecvt_utf8_utf16<bchar16>, bchar16> *ConverterUTF8;

#ifdef WINDOWS
static uint32 LAnsiCode = 1251;/*RUS*/;
#endif

struct Initializer
{
	Initializer() {}
	inline void Initialize()
	{
		if (ConverterUTF16)return;
		ConverterUTF16 = new std::wstring_convert<::codecvt<bchar16, bchar8, std::mbstate_t>, bchar16 >;
		ConverterUTF8 = new std::wstring_convert<std::codecvt_utf8_utf16<bchar16>, bchar16 >;

	}
	~Initializer()
	{
		BearCore::bear_delete(ConverterUTF16);
		BearCore::bear_delete(ConverterUTF8);
	}
};
Initializer initializer;


BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bchar8 * text, const bchar8 * end)
{
	bchar8 * temp = bear_alloc<bchar8>(end-text+1);
	bear_copy(temp, text, end - text + 1);
	temp[end - text] = 0;
	return BearCore::BearMemoryRef<bchar8>(temp);
}

BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bchar16 * text, const bchar16 * end)
{
	initializer.Initialize();
	std::wstring_convert<::codecvt<bchar16, bchar8, std::mbstate_t>, bchar16> convert;
	std::string str = convert.to_bytes(text, end);
	return ToANSI(&*str.begin(),(&*str.begin())+str.size());
}

BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bcharu8 * text, const bcharu8 * end)
{
	return ToANSI(*ToUTF16(text, end));
}

BearCore::BearMemoryRef<bchar16> BearCore::BearEncoding::ToUTF16(const bchar8 * text, const bchar8 * end)
{
#ifdef WINDOWS
	bchar16  *res = bear_alloc<bchar16>(end - text + 1);
	MultiByteToWideChar(LAnsiCode, 0, text,end-text, res, end - text + 1);
	res[end - text] = 0;
	return res;
#else
	initializer.Initialize();
	std::wstring str = ConverterUTF16->from_bytes(text, end);
	return ToUTF16(&*str.begin(), (&*str.begin())+str.size());
#endif
}

BearCore::BearMemoryRef<bchar16> BearCore::BearEncoding::ToUTF16(const bchar16 * begin, const bchar16 * end)
{
	bchar16 * temp = bear_alloc<bchar16>(end-begin+1);
	bear_copy(temp, begin, end - begin);
	temp[end - begin] = 0;
	return BearCore::BearMemoryRef<bchar16>(temp);
}

BearCore::BearMemoryRef<bchar16> BearCore::BearEncoding::ToUTF16(const bcharu8 * text, const bcharu8 * end)
{
	initializer.Initialize();
	std::wstring str = ConverterUTF8->from_bytes(reinterpret_cast<const char *> (text), reinterpret_cast<const char *> (end));
	return ToUTF16(&*str.begin(),(&*str.begin())+str.size());
}

BearCore::BearMemoryRef<bcharu8> BearCore::BearEncoding::ToUTF8(const bchar8 * text, const bchar8 * end)
{
	return ToUTF8(*ToUTF16(text, end));
}

BearCore::BearMemoryRef<bcharu8> BearCore::BearEncoding::ToUTF8(const bchar16 * text, const bchar16 * end)
{
	initializer.Initialize();
	std::string str = ConverterUTF8->to_bytes(text, end);
	return ToUTF8((const bcharu8*)&*str.begin(), (const bcharu8*)((&*str.begin())+str.size()));
}

BearCore::BearMemoryRef<bcharu8> BearCore::BearEncoding::ToUTF8(const bcharu8 * text, const bcharu8 * end)
{
	bcharu8 * temp = bear_alloc<bcharu8>(end-text+1 );
	bear_copy(temp, text, end - text );
	temp[end - text] = 0;
	return BearCore::BearMemoryRef<bcharu8>(temp);
}

bchar8 BearCore::BearEncoding::ToANSI(bchar16 c)
{
	initializer.Initialize();
	return ConverterUTF16->to_bytes(c)[0];

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
#ifdef WINDOWS
	bchar16  res[2];
	MultiByteToWideChar(LAnsiCode, 0, &c, 2, res, 2);
	return res[0];
#else
	initializer.Initialize();
	return ConverterUTF16->from_bytes(c)[0];
#endif
}

void BearCore::BearEncoding::SetLang(Lang lang)
{
#ifdef WINDOWS
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
}
