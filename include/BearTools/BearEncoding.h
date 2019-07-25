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
		static BearMemoryRef<bchar8> ToANSI(const bchar_utf8*text, const bchar_utf8*end);
		static inline  BearMemoryRef<bchar8> ToANSI(const bchar_utf8*text)
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
		static BearMemoryRef<bchar16> ToUTF16(const bchar_utf8*text, const bchar_utf8*end);
		static inline  BearMemoryRef<bchar16> ToUTF16(const bchar_utf8*text)
		{
			return ToUTF16(text, text+ BearString::GetSize(reinterpret_cast<const bchar8*>(text)));
		}

		static BearMemoryRef<bchar_utf8> ToUTF8(const bchar8*text, const bchar8*end);
		static inline  BearMemoryRef<bchar_utf8> ToUTF8(const bchar8*text)
		{
			return ToUTF8(text, text+ BearString::GetSize(text));
		}
		static BearMemoryRef<bchar_utf8> ToUTF8(const bchar16*text, const bchar16*end);
		static inline  BearMemoryRef<bchar_utf8> ToUTF8(const bchar16*text)
		{
			return ToUTF8(text, text+ BearString::GetSize(text));
		}
		static BearMemoryRef<bchar_utf8> ToUTF8(const bchar_utf8*text, const bchar_utf8*end);
		static inline  BearMemoryRef<bchar_utf8> ToUTF8(const bchar_utf8*text)
		{
			return 	 BearMemoryRef<bchar_utf8>(const_cast<bchar_utf8*>(text), false);
		}

		static bchar8 ToANSI(bchar16 c);
		static bchar8 ToANSI(bchar8 c);
		static bchar8 ToANSI(bchar_utf8 c);

		static bchar16 ToUTF16(bchar16 c);
		static bchar16 ToUTF16(bchar8 c);
		static bchar16 ToUTF16(bchar_utf8 c);

		static bchar_utf8 ToUTF8(bchar16 c);
		static bchar_utf8 ToUTF8(bchar8 c);
		static bchar_utf8 ToUTF8(bchar_utf8 c);

		template<typename C>
		static BearMemoryRef<bchar> ToCurrent(const C*text, const C*end)
		{
#ifdef UNICODE
			return ToUTF16(text, end);
#elif UTF_8
			return ToUTF8(text, end);
#else
			return ToANSI(text, end);
#endif
		}
		template<typename C>
		static inline  BearMemoryRef<bchar> ToCurrent(const C*text)
		{
#ifdef UNICODE
			return ToUTF16(text);
#elif UTF_8
			return ToUTF8(text);
#else
			return ToANSI(text);
#endif
		}
		template<typename C>
		static inline  BearMemoryRef<bchar> ToCurrent(C*text)
		{
#ifdef UNICODE
			return ToUTF16(text);
#elif UTF_8
			return ToUTF8(text);
#else
			return ToANSI(text);
#endif
		}
		template<typename C>
		static inline  bchar ToCurrent( C text)
		{
#ifdef UNICODE
			return ToUTF16(text);
#elif UTF_8
			return ToUTF8(text);
#else
			return ToANSI(text);
#endif
		}

		enum Lang
		{
			E_RUS,
			E_ENG,
		};
		static void SetLang(Lang lang);

	};
}