#include "BearCore.hpp"

BearCore::BearColor::BearColor():m_r(0),m_g(0),m_b(0),m_a(0)
{
}

BearCore::BearColor::~BearColor()
{
}

BearCore::BearColor::BearColor(uint8 R, uint8 G, uint8 B, uint8 A)
{
	set(R, G, B, A);
}

BearCore::BearColor::BearColor(uint32 color)
{
	set(color);
}

BearCore::BearColor::BearColor(float R, float G, float B, float A)
{
	set(R, G, B, A);
}

BearCore::BearColor::BearColor(const BearColor & color)
{
	copy(color);
}

void BearCore::BearColor::copy(const BearColor & color)
{
	m_r = color.m_r;
	m_g = color.m_g;
	m_b= color.m_b;
	m_a = color.m_a;
}

void BearCore::BearColor::swap(BearColor & color)
{
	BearCore::bear_swap(m_r  ,color.m_r);
	BearCore::bear_swap(m_g , color.m_g);
	BearCore::bear_swap(m_b , color.m_b);
	BearCore::bear_swap(m_a , color.m_a);
}

BearCore::BearColor & BearCore::BearColor::operator=(const BearColor & color)
{
	copy(color);
	return*this;
}

void BearCore::BearColor::set(uint32 color)
{
	uint8*col = (uint8*)&color;
	set(col[0], col[1], col[2], col[3]);
}

void BearCore::BearColor::set(uint8 R, uint8 G, uint8 B, uint8 A)
{
	set(R / 255.f, G / 255.f, B / 255.f, A / 255.f);
}

void BearCore::BearColor::set(float R, float G, float B, float A)
{
	m_r = R; m_g = G; m_b = B; m_a = A;
}

BearCore::BearVector4<float> BearCore::BearColor::getFloat() const
{
	return BearCore::BearVector4<float>(m_r,m_g,m_b,m_a);
}

BearCore::BearVector4<uint8> BearCore::BearColor::getUint8() const
{
	return BearCore::BearVector4<uint8>(static_cast<uint8>(m_r * 255.f), static_cast<uint8>(m_g * 255.f), static_cast<uint8>(m_b * 255.f), static_cast<uint8>(m_a * 255.f));
}

uint32 BearCore::BearColor::getUint32() const
{
	uint8 temp[4];
	temp[0] =static_cast<uint8>( m_r * 255.f);
	temp[1] = static_cast<uint8>(m_g * 255.f);
	temp[2] = static_cast<uint8>(m_b * 255.f);
	temp[3] = static_cast<uint8>(m_a* 255.f);
	return *reinterpret_cast<uint32*>(temp);
}

const  BearCore::BearColor  BearCore::BearColor::Black((uint8)0, 0, 0);
const  BearCore::BearColor  BearCore::BearColor::White((uint8)255, (uint8)255, (uint8)255);
const  BearCore::BearColor  BearCore::BearColor::Red((uint8)255, 0, 0);
const  BearCore::BearColor BearCore::BearColor::Green((uint8)0, 255, 0);
const  BearCore::BearColor  BearCore::BearColor::Blue((uint8)0, 0, 255);
const  BearCore::BearColor  BearCore::BearColor::Yellow((uint8)255, 255, 0);
const  BearCore::BearColor  BearCore::BearColor::Magenta((uint8)255, 0, 255);
const  BearCore::BearColor  BearCore::BearColor::Cyan((uint8)0, 255, 255);
const  BearCore::BearColor  BearCore::BearColor::Transparent((uint8)0, 0, 0, 0);
const  BearCore::BearColor  BearCore::BearColor::Brown((uint8)69, (uint8)22, (uint8)28);