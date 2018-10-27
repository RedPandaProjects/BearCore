#include "BearCore.hpp"
BearCore::BearFraction::BearFraction():m_c(0),m_d(0)
{
}

BearCore::BearFraction::BearFraction(BearFraction && right) : m_c(0), m_d(0)
{
	swap(right);
}

BearCore::BearFraction::BearFraction(const BearFraction & right) : m_c(0), m_d(0)
{
	copy(right);
}

void BearCore::BearFraction::copy(const BearFraction & right)
{
	m_c = right.m_c;
	m_d = right.m_d;
}

void BearCore::BearFraction::swap(BearFraction & right)
{
	bear_swap(m_c, right.m_c);
	bear_swap(m_d, right.m_d);
}

BearCore::BearFraction::BearFraction(uint64 c, uint64 b):m_c(c),m_d(b)
{
}

uint64 BearCore::BearFraction::div()
{
	if (m_d == 0)return 0;
	uint64 a = m_c / m_d;
    return a;
}

bool BearCore::BearFraction::isRest()
{
	return m_c%m_d;
}

BearCore::BearFraction & BearCore::BearFraction::operator=(const BearFraction & right)
{
	copy(right);
	return*this;
}

BearCore::BearFraction & BearCore::BearFraction::operator=(BearFraction && right)
{
	swap(right);
	return*this;
}

BearCore::BearFraction& BearCore::BearFraction::operator*=(const BearFraction& a)
{
	if (!m_d || !a.m_d || !m_c || !a.m_c) return*this;
	m_c *= a.m_c;
	m_d *= a.m_d;
	return *this;
}

BearCore::BearFraction& BearCore::BearFraction::operator/=(const BearFraction& a)
{
	if (!m_d||!a.m_d||!m_c||!a.m_c) return*this;
	m_c *= a.m_d;
	m_d *= a.m_c;
	return *this;
}

BearCore::BearFraction& BearCore::BearFraction::operator+=(const BearFraction& a)
{
	if (m_d == 0 && a.m_d == 0)
		return*this;
	if (m_d == 0)
		m_d = a.m_d;
	if (m_d != a.m_d) {
		m_c *= a.m_d;
		a.m_c *= m_d;
		m_d *= a.m_d;
		a.m_d = m_d;

	}
	m_c += a.m_c;
	return *this;
}

BearCore::BearFraction &BearCore::BearFraction::operator-=(const BearFraction& a)
{
	if (m_d == 0 && a.m_d == 0)
		return*this;
	if (m_d == 0)
		m_d = a.m_d;
	if (m_d != a.m_d) {
		m_c *= a.m_d;
		a.m_c *= m_d;
		m_d *= a.m_d;
		a.m_d = m_d;

	}
	m_c -= a.m_c;
	return *this;
}

BearCore::BearFraction& BearCore::BearFraction::operator+=(uint64 a)
{
	m_c += a;
	return*this;
}

BearCore::BearFraction BearCore::BearFraction::operator*(uint64 a)
{
	BearFraction b(*this);
	b.m_c *= a;
	return b;
}

BEARTOOL_API BearCore::BearFraction BearCore::operator*(const BearFraction & c, const BearFraction & a)
{
	BearFraction b(c);
	b *= a;
	return b;
}

BEARTOOL_API BearCore::BearFraction BearCore::operator/(const BearFraction & c, const BearFraction & a)
{
	BearFraction b(c);
	b /= a;
	return b;
}

BEARTOOL_API BearCore::BearFraction BearCore::operator+(const BearFraction & c, const BearFraction & a)
{
	BearFraction b(c);
	b += a;
	return b;
}

BEARTOOL_API BearCore::BearFraction BearCore::operator-(const BearFraction & c, const BearFraction & a)
{
	BearFraction b(c);
	b -= a;
	return b;
}
