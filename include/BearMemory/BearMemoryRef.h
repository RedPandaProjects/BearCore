#pragma once

template<typename P>
struct BearRef
{
public:
	template<typename C>
	BearRef(C* p, bool auto_free = true) :m_real_p(0), m_p(0), m_free(auto_free)
	{
		m_p = static_cast<P*>(p);
		m_real_p = reinterpret_cast<void*>(p);
	}
	explicit BearRef(P*p, bool auto_free = true) :m_real_p(0),m_p(p), m_free(auto_free)
	{}
	BearRef() :m_p(0), m_free(false), m_real_p(0){};
	BearRef(const BearRef& ptr) :m_real_p(ptr.m_real_p), m_p(ptr.m_p), m_free(ptr.m_free){ ptr.m_p = 0; ptr.m_free = false; ptr.m_real_p = 0; };
	BearRef(BearRef&&ptr) :m_real_p(ptr.m_real_p), m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; ptr.m_real_p = 0;};

	void clear()
	{
		if (!m_p)return;
		if (m_free) {
			
			if (m_real_p)
			{
				m_p->~P();
				bear_free(m_real_p);
			}
			else
			{
				bear_delete(m_p);
			}
		}
		m_free = false;
		m_p = 0;
		m_real_p = 0;
	}

	void clear_no_free() { m_free = false; m_p = 0; m_real_p = 0; }

	~BearRef() { clear(); }
	P*operator->() { return m_p; }
	const P*operator->()const { return m_p; }
	P*operator*() { return m_p; }
	const P*operator*()const { return m_p; }


	BearRef&operator=(BearRef&&ptr) { clear(); swap(ptr);    return*this; };
	BearRef&operator=(const BearRef&ptr) { clear(); copy(ptr);    return*this; };
	void copy(const BearRef& ptr) { clear(); m_real_p = ptr.m_real_p;    m_p = ptr.m_p; ptr.m_p = 0; m_free = ptr.m_free; ptr.m_free = false; }
	void swap(BearRef& ptr) { bear_swap(ptr.m_p, m_p);  bear_swap(ptr.m_free, m_free); bear_swap(ptr.m_real_p, m_real_p); }


	P&operator[](bsize id) { return m_p[id]; }
	const P&operator[](bsize id) const { return m_p[id]; }
private:
	mutable void* m_real_p;
	mutable	P*m_p;
	mutable bool m_free;
};

template<>
struct BearRef<void*>
{
public:
	BearRef(void*p, bool auto_free = true) :m_p(p), m_free(auto_free)
	{}
	BearRef() :m_p(0), m_free(false) {};
	BearRef(const BearRef&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };
	BearRef(BearRef&&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };

	void clear()
	{
		if (!m_p)return;
		if (m_free) {

			bear_free(m_p);
		}
		m_free = false;
		m_p = 0;
	}

	void clear_no_free() { m_free = false; m_p = 0; }

	~BearRef() { clear(); }

	void*operator*() { return m_p; }
	const void*operator*()const { return m_p; }


	BearRef&operator=(BearRef&&ptr) { clear(); swap(ptr);    return*this; };
	BearRef&operator=(const BearRef&ptr) { clear(); swap(ptr);    return*this; };
	void copy(const BearRef&ptr) { clear(); m_p = ptr.m_p; ptr.m_p = 0; m_free = ptr.m_free; ptr.m_free = false; }
	void swap(const BearRef&ptr) { bear_swap(ptr.m_p, m_p);  bear_swap(ptr.m_free, m_free); }

private:
	mutable	void*m_p;
	mutable bool m_free;
};
