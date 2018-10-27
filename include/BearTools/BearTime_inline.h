#pragma once

inline BearCore::BearTime::BearTime(const BearTime & right)
{
	assign(right);
}
inline BearCore::BearTime::BearTime( BearTime && right) :m_microseconds(0)
{
	swap(right);
}
inline BearCore::BearTime::BearTime() :m_microseconds(0)
{
}

inline BearCore::BearTime::BearTime(int64 microseconds)
{
	assign(microseconds);
}

inline BearCore::BearTime::BearTime(int32 miliseconds)
{
	assign(miliseconds);
}

inline BearCore::BearTime::BearTime(float seconds)
{
	assign(seconds);
}

inline void BearCore::BearTime::swap(BearTime & right)
{
	bear_swap(m_microseconds, right.m_microseconds);
}
inline void BearCore::BearTime::copy(const BearTime & right)
{
	assign(right);
}

inline void  BearCore::BearTime::assign(int64 microseconds)
{
	m_microseconds = microseconds;
}

inline void  BearCore::BearTime::assign(int32 miliseconds)
{
	m_microseconds = int64(miliseconds * 1000);
}

inline void  BearCore::BearTime::assign(float seconds)
{
	m_microseconds = int64(seconds * 1000000);
}

inline void BearCore::BearTime::assign(const BearTime &time)
{
	m_microseconds = time.m_microseconds;
}

inline void  BearCore::BearTime::append(int64 microseconds)
{
	m_microseconds += microseconds;
}

inline void  BearCore::BearTime::append(int32 miliseconds)
{
	append(int64(miliseconds * 1000));
}

inline void  BearCore::BearTime::append(float seconds)
{
	append(int64(seconds * 1000000));
}

inline void BearCore::BearTime::append(const BearTime& time)
{
	append(time.m_microseconds);
}

inline int64  BearCore::BearTime::asmicroseconds() const
{
	return m_microseconds;
}

inline int32  BearCore::BearTime::asmiliseconds() const
{
	return static_cast<int32>(m_microseconds / 1000ll);
}

inline float  BearCore::BearTime::asseconds() const
{
	return m_microseconds / 1000000.f;
}
inline BearCore::BearTime & BearCore::BearTime::operator-=(const BearTime & right)
{
	m_microseconds -= right.m_microseconds;
	return *this;
}
inline BearCore::BearTime & BearCore::BearTime::operator+=(const BearTime & right)
{
	m_microseconds += right.m_microseconds;
	return *this;
}
inline BearCore::BearTime & BearCore::BearTime::operator-=(BearTime && right)
{
	m_microseconds -= right.m_microseconds;
	return *this;
}
inline BearCore::BearTime & BearCore::BearTime::operator+=(BearTime && right)
{
	m_microseconds += right.m_microseconds;
	return *this;
}

inline BearCore::BearTime & BearCore::BearTime::operator*=(const BearTime & right)
{
	m_microseconds *= right.m_microseconds;
	return *this;
}

inline BearCore::BearTime & BearCore::BearTime::operator/=(const BearTime & right)
{
	m_microseconds /= right.m_microseconds;
	return *this;
}

inline BearCore::BearTime & BearCore::BearTime::operator*=(BearTime && right)
{
	m_microseconds *= right.m_microseconds;
	return *this;
}

inline BearCore::BearTime & BearCore::BearTime::operator*(double right)
{
	 m_microseconds=int64(double(m_microseconds)*right);
	 return *this;
}

inline BearCore::BearTime & BearCore::BearTime::operator/=(BearTime && right)
{
	m_microseconds /= right.m_microseconds;
	return *this;
}

inline BearCore::BearTime  & BearCore::BearTime::operator=(const BearTime& right)
{
	m_microseconds = right.m_microseconds;
	return*this;
}
inline BearCore::BearTime  & BearCore::BearTime::operator=( BearTime&& right)
{
	m_microseconds = right.m_microseconds;
	return*this;
}
inline BearCore::BearTime BearCore::operator-(const BearTime & left, const BearTime & right)
{
	return BearTime(left) -= right;
}

inline BearCore::BearTime BearCore::operator+(const BearTime & left, const BearTime & right)
{
	return BearTime(left) += right;
}

inline BearCore::BearTime BearCore::operator-(const BearTime & left, BearTime && right)
{
	return BearTime(left) -= right;
}

inline BearCore::BearTime BearCore::operator+(const BearTime & left, BearTime && right)
{
	return BearTime(left) += right;
}

inline  BearCore::BearTime BearCore::operator*(const BearTime & left, const BearTime & right)
{
	return BearTime(left) *= right;
}

inline  BearCore::BearTime BearCore::operator/(const BearTime & left, const BearTime & right)
{
	return BearTime(left) /= right;
}

inline  BearCore::BearTime BearCore::operator*(const BearTime & left, BearTime && right)
{
	return BearTime(left) *= right;
}

inline BearCore::BearTime BearCore::operator/(const BearTime & left, BearTime && right)
{
	return BearTime(left) /= right;
}
