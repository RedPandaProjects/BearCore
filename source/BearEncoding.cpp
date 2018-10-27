#include "BearCore.hpp"
#include <codecvt>
BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bchar8 * text, const bchar8 * end)
{
	bchar8 * temp = bear_alloc<bchar8>(end-text+1);
	bear_copy(temp, text, end - text + 1);
	temp[end - text] = 0;
	return BearCore::BearMemoryRef<bchar8>(temp);
}

BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bchar16 * text, const bchar16 * end)
{
	std::wstring_convert<std::codecvt<bchar16, bchar8, std::mbstate_t>, bchar16> convert;
	std::string str = convert.to_bytes(text, end);
	return ToANSI(&*str.begin(), str.end()._Ptr);
}

BearCore::BearMemoryRef<bchar8> BearCore::BearEncoding::ToANSI(const bcharu8 * text, const bcharu8 * end)
{
	return ToANSI(*ToUTF16(text, end));
}

BearCore::BearMemoryRef<bchar16> BearCore::BearEncoding::ToUTF16(const bchar8 * text, const bchar8 * end)
{
	std::wstring_convert<std::codecvt<bchar16, bchar8, std::mbstate_t>, bchar16> convert;
	std::wstring str = convert.from_bytes(text, end);
	return ToUTF16(&*str.begin(), str.end()._Ptr);
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
	std::wstring_convert<std::codecvt_utf8_utf16<bchar16>, bchar16> conversion;
	std::wstring str = conversion.from_bytes(reinterpret_cast<const char *> (text), reinterpret_cast<const char *> (end));
	return ToUTF16(&*str.begin(), str.end()._Ptr);
}

BearCore::BearMemoryRef<bcharu8> BearCore::BearEncoding::ToUTF8(const bchar8 * text, const bchar8 * end)
{
	return ToUTF8(*ToUTF16(text, end));
}

BearCore::BearMemoryRef<bcharu8> BearCore::BearEncoding::ToUTF8(const bchar16 * text, const bchar16 * end)
{
	std::wstring_convert<std::codecvt_utf8_utf16<bchar16>, bchar16> conversion;
	std::string str = conversion.to_bytes(text, end); 
	return ToUTF8(&*str.begin(), str.end()._Ptr);
}

BearCore::BearMemoryRef<bcharu8> BearCore::BearEncoding::ToUTF8(const bcharu8 * text, const bcharu8 * end)
{
	bcharu8 * temp = bear_alloc<bcharu8>(end-text+1 );
	bear_copy(temp, text, end - text );
	temp[end - text] = 0;
	return BearCore::BearMemoryRef<bcharu8>(temp);
}
