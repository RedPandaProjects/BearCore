#pragma once
namespace BearCore
{
	template < class P> class BearFlags
	{
	public:
		BearFlags() :m_flags(0) {}
		BearFlags(P f) :m_flags(f) {}
		inline BearFlags&clear() { m_flags = 0; return*this; }
		inline BearFlags&fill() { m_flags = P(-1); return*this;}
		inline BearFlags&invert() { flags = ~flags; return*this; }
		inline BearFlags&invert(const BearFlags& right) { flags = ~right.flags;  return*this;}
		inline BearFlags&invert(P right) { flags ^= right;  return*this;}
		inline void copy(const BearFlags&right) { m_flags = right.m_flags; }
		inline BearFlags&assign(P p) { m_flags = p; return*this;}
		inline BearFlags&set(bool bit, P mask) {if (bit) m_flags |= mask; else m_flags = m_flags & ~mask; return*this;}
		inline bool is(P p)const { return p==m_flags & p; }
		inline bool test(P p)const { return m_flags & p; }
		inline BearFlags&and(P p) { m_flags &=p; return*this; }
		inline BearFlags&or(P p) { m_flags |= p; return*this; }
		inline BearFlags&and(const BearFlags& right) { m_flags &= right.m_flags; return*this; }
		inline BearFlags& or (const BearFlags& right) { m_flags |= right.m_flags; return*this; }
		inline void swap( BearFlags&right) { m_flags = right.m_flags; }
		BearFlags(const BearFlags& right) :m_flags(0) { copy(right); }
		BearFlags(BearFlags&& right) :m_flags(0) { swap(right); }
		inline BearFlags&operator=(const BearFlags&right){ copy(right); return*this;}
		inline BearFlags&operator=( BearFlags&&right) { swap(right); return*this; }
		inline BearFlags&operator=(P right) { m_flags=right; return*this; }
		inline bool operator==(const BearFlags&right) { return m_flags == right.m_flags; }
		inline P operator*()const { return m_flags; }

	private:
		P m_flags;
	};
}