#include "BearCore.hpp"
extern "C" bsize  __cdecl __BearStringFindBeginUtf16(char*string, bsize size, bchar16 ch);
extern "C" bsize  __cdecl __BearStringFindBeginChar(char*string, bsize size, bchar8 ch);
#ifdef X32
#define BEND 0xffffffff
#else
#define BEND 0xffffffffffffffff
#endif

void BearCore::BearBufferedReader::readStringToLine(BearString&str, Encoding::Encoding encoding) const
{
	if (tell() == 0&&size()>3)	
		if (((char*)begin())[0] == 0xef && ((char*)begin())[1] == 0xbb && ((char*)begin())[2] == 0xbf)
			seek(3);
	str.seek(0);
	str.clear_no_free();
	switch (encoding)
	{
	case Encoding::ANSI:
	{
		const bchar8*begin1 = reinterpret_cast<const bchar8*>(begin());
		const bchar8*end1 = reinterpret_cast<const bchar8*>(end());
		const bchar8*begin2 = strchr(begin1, '\n');
		if (!begin2)
		{
			begin2 = end1;
		}
#ifdef UNICODE
		str.append(*str.ConvertToUTF16( begin1), begin2 - begin1);
#else
		str.append(begin1, begin2 - begin1);
#endif
	
		seek(begin2-begin1 + tell()+1);
	}
		break;
	case Encoding::UTF8:
	{
		const bchar8*begin1 = reinterpret_cast<const bchar8*>(begin());
		const bchar8*end1 = reinterpret_cast<const bchar8*>(end());
		const bchar8*begin2 = strchr(begin1, '\n');
		if (!begin2)
		{
			begin2 = end1;
		}
#ifdef UNICODE
		str.append(*str.ConvertUTF8ToUTF16(begin1, begin2 - begin1));
#else
		str.append(*str.ConvertUTF8ToANSI(begin1, begin2 - begin1));
#endif

		seek(begin2 - begin1 + tell() + 1);
	
		break;
	}
	case  Encoding::UTF16:
	{
		const bchar16*begin1 = reinterpret_cast<const bchar16*>(begin());
		const bchar16*end1 = reinterpret_cast<const bchar16*>(end());

		const bchar16*begin2 = wcschr(begin1, L'\n');


#ifndef UNICODE
		str.append(*str.ConvertToANSI(begin1), begin2 - begin1);
#else
		str.append(begin1, begin2 - begin1);
#endif
		seek(begin2 - begin1 + tell()+1);
		break;
	}
	default:
		break;
	} 
}

void BearCore::BearBufferedReader::readStringToZero(BearString&str, Encoding::Encoding encoding) const
{
	switch (encoding)
	{
	case Encoding::ANSI:
	{
		const bchar8*begin1 = reinterpret_cast<const bchar8*>(begin());
		const bchar8*end1 = reinterpret_cast<const bchar8*>(end());
		const bchar8*begin2 = strchr(begin1, '0');
		if (!begin2)
		{
			begin2 = end1;
		}
#ifdef UNICODE
		str.append(*str.ConvertToUTF16(begin1), begin2 - begin1);
#else
		str.append(begin1, begin2 - begin1);
#endif

		seek(begin2 - begin1 + tell() + 1);
	}
	break;
	case Encoding::UTF8:
	{
		const bchar8*begin1 = reinterpret_cast<const bchar8*>(begin());
		const bchar8*end1 = reinterpret_cast<const bchar8*>(end());
		const bchar8*begin2 = strchr(begin1, '0');
		if (!begin2)
		{
			begin2 = end1;
		}
#ifdef UNICODE
		str.append(*str.ConvertUTF8ToUTF16(begin1, begin2 - begin1));
#else
		str.append(*str.ConvertUTF8ToANSI(begin1, begin2 - begin1));
#endif

		seek(begin2 - begin1 + tell() + 1);

		break;
	}
	case  Encoding::UTF16:
	{
		const bchar16*begin1 = reinterpret_cast<const bchar16*>(begin());
		const bchar16*end1 = reinterpret_cast<const bchar16*>(end());

		const bchar16*begin2 = wcschr(begin1, L'0');


#ifndef UNICODE
		str.append(*str.ConvertToANSI(begin1), begin2 - begin1);
#else
		str.append(begin1, begin2 - begin1);
#endif
		seek(begin2 - begin1 + tell() + 1);
		break;
	}
	default:
		break;
	}
}

BearCore::BearStreamPtr<BearCore::BearInputStream> BearCore::BearBufferedReader::readChunkAsInputStream(uint32 type) const
{
	auto ptr=readChunkAsBufferedReader(type);
	auto strem = *ptr;
	ptr.clearNoFree();
	return BearStreamPtr<BearInputStream>(strem);
}
