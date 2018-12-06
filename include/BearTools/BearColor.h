#pragma once 
namespace BearCore
{
	class BEARTOOL_API BearColor
	{
	public:
		BearColor();
		~BearColor();

		BearColor(uint8 R, uint8 G, uint8 B, uint8 A = 255);
		BearColor(uint32 color);
		BearColor(float R, float G, float B, float A = 1);

		BearColor(const BearColor&color);
		void Copy(const BearColor&color);
		void Swap(BearColor&color);
		BearColor&operator=(const BearColor&color);

		void Set(uint32 color);
		void Set(uint8 R, uint8 G, uint8 B, uint8 A = 255);
		void Set(float R, float G, float B, float A = 1.f);
		BearCore::BearVector4<float> GetFloat() const;
		BearCore::BearVector4<uint8> GetUint8() const;
		uint32 GetUint32()const;
		static const BearColor Black;
		static const BearColor White;
		static const BearColor Red;
		static const BearColor Green;
		static const BearColor Blue;
		static const BearColor Yellow;
		static const BearColor Magenta;
		static const BearColor Cyan;
		static const BearColor Transparent;
		static const BearColor Brown;
	private:
		float m_r, m_g, m_b, m_a;

	};
}