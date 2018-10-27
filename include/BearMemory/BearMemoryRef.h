#pragma once
namespace BearCore
{
	template<class P>
	struct BearMemoryRef
	{
	public:
		BearMemoryRef(P*p, bool auto_free = true) :m_p(p), m_free(auto_free)
		{}
		BearMemoryRef() :m_p(0), m_free(false) {};
		BearMemoryRef(const BearMemoryRef&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };
		BearMemoryRef(BearMemoryRef&&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };

		void clear()
		{
			if (!m_p)return;
			if (m_free) {

				bear_delete(m_p);
			}
			m_free = false;
			m_p = 0;
		}

		void clear_no_free() { m_free = false; m_p = 0; }

		~BearMemoryRef() { clear(); }
		P*operator->() { return m_p; }
		const P*operator->()const { return m_p; }
		P*operator*() { return m_p; }
		const P*operator*()const { return m_p; }


		BearMemoryRef&operator=(BearMemoryRef&&ptr) { clear(); swap(ptr);    return*this; };
		BearMemoryRef&operator=(const BearMemoryRef&ptr) { clear(); swap(ptr);    return*this; };
		void copy(const BearMemoryRef&ptr) { clear(); m_p = ptr.m_p; ptr.m_p = 0; m_free = ptr.m_free; ptr.m_free = false; }
		void swap(BearMemoryRef&ptr) { bear_swap(ptr.m_p, m_p);  bear_swap(ptr.m_free, m_free); }


		P&operator[](bsize id) { return m_p[id]; }
		const P&operator[](bsize id) const { return m_p[id]; }
	private:
		mutable	P*m_p;
		mutable bool m_free;
	};

	template<>
	struct BearMemoryRef<void*>
	{
	public:
		BearMemoryRef(void*p, bool auto_free = true) :m_p(p), m_free(auto_free)
		{}
		BearMemoryRef() :m_p(0), m_free(false) {};
		BearMemoryRef(const BearMemoryRef&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };
		BearMemoryRef(BearMemoryRef&&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };

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

		~BearMemoryRef() { clear(); }

		void*operator*() { return m_p; }
		const void*operator*()const { return m_p; }


		BearMemoryRef&operator=(BearMemoryRef&&ptr) { clear(); swap(ptr);    return*this; };
		BearMemoryRef&operator=(const BearMemoryRef&ptr) { clear(); swap(ptr);    return*this; };
		void copy(const BearMemoryRef&ptr) { clear(); m_p = ptr.m_p; ptr.m_p = 0; m_free = ptr.m_free; ptr.m_free = false; }
		void swap(const BearMemoryRef&ptr) { bear_swap(ptr.m_p, m_p);  bear_swap(ptr.m_free, m_free); }

	private:
		mutable	void*m_p;
		mutable bool m_free;
	};

}