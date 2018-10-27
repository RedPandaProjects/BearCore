#pragma once
namespace  BearCore
{
	template<class P>
	struct BearStreamRef
	{
	public:
		BearStreamRef(P*p) :m_p(p)
		{}
		BearStreamRef() :m_p(0) {};
		BearStreamRef(const BearStreamRef&ptr) :m_p(ptr.m_p) { ptr.m_p = 0; };
		void clear()
		{
			if (!m_p)return;
			m_p->destory();
			m_p = 0;
			//	bear_free<P>(m_p, false);
		}
		void clearNoFree() { m_p = 0; }
		~BearStreamRef() { clear(); }
		P*operator->() { return m_p; }
		const P*operator->()const { return m_p; }
		P*operator*() { return m_p; }
		const P*operator*()const { return m_p; }

		BearStreamRef&operator=(const BearStreamRef&ptr) { clear(); swap(ptr);    return*this; };

		void copy(const BearStreamRef&ptr) const { clear(); m_p = ptr.m_p; ptr.m_p = 0; }
		void swap(const BearStreamRef&ptr) { bear_swap(ptr.m_p, m_p); }
		P&operator[](bsize id) { return m_p[id]; }
		const P&operator[](bsize id) const { return m_p[id]; }
	private:
		mutable P*m_p;
	};
}