#pragma once
namespace BearCore
{
	
	class BEARTOOL_API  BearEncoding
	{
		BEAR_CLASS_STATIC(BearEncoding);
	public:
		enum Encoding
		{
			ANSI,
			UTF8,
			UTF16
		};

		static BearMemoryRef<bchar8> ToANSI(const bchar8*begin, const bchar8*end);
		static inline  BearMemoryRef<bchar8> ToANSI(const bchar8*text)
		{
			return BearMemoryRef<bchar8>(const_cast<bchar8*>(text), false);
		}
		static BearMemoryRef<bchar8> ToANSI(const bchar16*text, const bchar16*end);
		static inline  BearMemoryRef<bchar8> ToANSI(const bchar16*text)
		{
			return ToANSI(text, text+BearString::GetSize(text));
		}
		static BearMemoryRef<bchar8> ToANSI(const bcharu8*text, const bcharu8*end);
		static inline  BearMemoryRef<bchar8> ToANSI(const bcharu8*text)
		{
			return ToANSI(text, text + BearString::GetSize(reinterpret_cast<const bchar8*>(text)));
		}
	

		static BearMemoryRef<bchar16> ToUTF16(const bchar8*text, const bchar8*end);
		static inline  BearMemoryRef<bchar16> ToUTF16(const bchar8*text)
		{
			return ToUTF16(text, text + BearString::GetSize(text));
		}
		static BearMemoryRef<bchar16> ToUTF16(const bchar16*text, const bchar16*end);
		static inline  BearMemoryRef<bchar16> ToUTF16(const bchar16*text)
		{
			return 	 BearMemoryRef<bchar16>(const_cast<bchar16*>(text), false);
		}
		static BearMemoryRef<bchar16> ToUTF16(const bcharu8*text, const bcharu8*end);
		static inline  BearMemoryRef<bchar16> ToUTF16(const bcharu8*text)
		{
			return ToUTF16(text, text+ BearString::GetSize(reinterpret_cast<const bchar8*>(text)));
		}

		static BearMemoryRef<bcharu8> ToUTF8(const bchar8*text, const bchar8*end);
		static inline  BearMemoryRef<bcharu8> ToUTF8(const bchar8*text)
		{
			return ToUTF8(text, text+ BearString::GetSize(text));
		}
		static BearMemoryRef<bcharu8> ToUTF8(const bchar16*text, const bchar16*end);
		static inline  BearMemoryRef<bcharu8> ToUTF8(const bchar16*text)
		{
			return ToUTF8(text, text+ BearString::GetSize(text));
		}
		static BearMemoryRef<bcharu8> ToUTF8(const bcharu8*text, const bcharu8*end);
		static inline  BearMemoryRef<bcharu8> ToUTF8(const bcharu8*text)
		{
			return 	 BearMemoryRef<bcharu8>(const_cast<bcharu8*>(text), false);
		}


	};
}