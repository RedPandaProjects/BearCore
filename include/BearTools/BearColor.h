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
		void copy(const BearColor&color);
		void swap(BearColor&color);
		BearColor&operator=(const BearColor&color);

		void set(uint32 color);
		void set(uint8 R, uint8 G, uint8 B, uint8 A = 255);
		void set(float R, float G, float B, float A = 1.f);
		BearCore::BearVector4<float> getFloat() const;
		BearCore::BearVector4<uint8> getUint8() const;
		uint32 getUint32()const;
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