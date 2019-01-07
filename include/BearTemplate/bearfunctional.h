#pragma once
namespace BearCore
{
	template <typename T> struct bear_remove_reference
	{
		typedef T type;
	};
	template <typename T> struct bear_remove_reference<T&> {
		typedef T type;
	};
	template <typename T> struct bear_remove_reference<T&&> {
		typedef T type;
	};
	template <typename T> struct bear_remove_pointer
	{
		typedef T type;
	};
	template <typename T> struct bear_remove_pointer<T*> {
		typedef T type;
	};
	template <typename T> struct bear_remove_const
	{
		typedef T type;
	};
	template <typename T> struct bear_remove_const<T const> {
		typedef T type;
	};


	template <typename T> struct bear_remove_void {
		typedef T type;
	};
	template <>
	struct bear_remove_void<void> {
		typedef int type;
	};
	template <typename T> struct bear_is_const {
		enum { value = false };
	};

	template <typename T> struct bear_is_const<T const> {
		enum { value = true };
	};

	template <typename T> struct bear_is_reference {
		enum { value = false };
	};

	template <typename T> struct bear_is_reference<T &> {
		enum { value = true };
	};
	template <typename T> struct bear_is_reference<T &&> {
		enum { value = true };
	};
	template <typename T> struct bear_is_void {
		enum { value = false };
	};

	template <> struct bear_is_void<void> {
		enum { value = true };
	};

	template <typename T> struct bear_is_pointer {
		enum { value = false };
	};

	template <typename T> struct bear_is_pointer<T *> {
		enum { value = true };
	};

	template<typename A>
	struct bear_is_void_function
	{
		struct yes { int8 a; };
		struct no { int16 a; };
		template<typename U, typename ...args>
		static no test(U(*a)(args...)) { return no() };
		template<typename ...args>
		static yes test(void(*a)(args...)) { return yes() };
		enum { ressult = sizeof(yes) == sizeof(test((A)0)) };
	};

	struct BearDefaultSwap
	{
		template < class P>
		void operator()(P&p1, P&p2)
		{
			bear_swap(p1, p2);
		}
	};

	struct BearClassSwap
	{
		template < class P>
		void operator()(P&p1, P&p2)
		{
			p1.swap(p2);
		}
	};

	template <typename C, typename M>
	struct BearComparator
	{
		BearMemoryRef<M> m;
		C c;
		BearComparator(BearComparator&compor)  { copy(compor); }
		BearComparator()  {}
		BearComparator(M&m_, C&c_) :m(&m_,false), c(c_) {}
		BearComparator(M&&m_, C&c_) :m(bear_new<M>(m_)), c(c_) {}
		~BearComparator() { clear(); }
		template<typename T>
		inline bool operator()(T&m2)
		{
			BEAR_ASSERT(*m);
			return c(m2, **m);
		}
		inline	void copy(const BearComparator& compor) { m = compor.m; c = compor.c; }
		inline void swap(BearComparator& compor) { m.swap(compor.m); bear_swap(c, compor.c); }
		inline BearComparator&operator=(const BearComparator&compor) { copy(compor); return *this; }
		inline void clear() { m.clear(); }
	};
	template <typename C, typename M>
	struct BearTwoCompare
	{
		C c;
		M m;
		BearTwoCompare(BearTwoCompare&compor) { copy(compor); }
		BearTwoCompare() {}
		BearTwoCompare( const C&c_, const M&m_) :m(m_), c(c_) {}
		template <typename L>
		inline bool operator()(L&m1, L&m2)
		{
			return c(m1, m2) | m(m1, m2);
		}
		inline	void copy(const BearTwoCompare& compor) { m = compor.m; c = compor.c; }
		inline void swap(BearTwoCompare& compor) { bear_swap(m, compor.m); bear_swap(c, compor.c); }
		inline BearTwoCompare&operator=(const BearTwoCompare&compor) { copy(compor); return *this; }
	};
	template<typename C, typename M>
	inline BearComparator<C, M> bear_bind_compare(C&compare, M&item)
	{
		return BearComparator<C, M>(item, compare);
	}
	template<typename C, typename M>
	inline BearComparator<C, M> bear_bind_compare(C&&compare, M&item)
	{
		return BearComparator<C, M>(item, compare);
	}
	template<typename C, typename M>
	inline BearComparator<C, M> bear_bind_compare(C&compare, M&&item)
	{
		return BearComparator<C, M>(item, compare);
	}
	template<typename C, typename M>
	inline BearComparator<C, M> bear_bind_compare(C&&compare, M&&item)
	{
		return BearComparator<C, M>(item, compare);
	}


	template<typename C, typename M>
	inline BearTwoCompare<C, M> bear_append_compare(C&compare1, M&compare2)
	{
		return BearTwoCompare<C, M>(compare1, compare2);
	}
	template<typename C, typename M>
	inline BearTwoCompare<C, M> bear_append_compare(C&&compare1, M&compare2)
	{
		return BearTwoCompare<C, M>(compare1, compare2);
	}
	template<typename C, typename M>
	inline BearTwoCompare<C, M> bear_append_compare(C&compare1, M&&compare2)
	{
		return BearTwoCompare<C, M>(compare1, compare2);
	}
	template<typename C, typename M>
	inline BearTwoCompare<C, M> bear_append_compare(C&&compare1, M&&compare2)
	{
		return BearTwoCompare<C, M>(compare1, compare2);
	}

	struct BearLess
	{
		template<typename C,typename M>
		bool operator() (const C&c1, const M&c2)const
		{
			return c1 < c2;
		}
	};
	typedef BearLess BearDefaultCompare;
	struct BearGreater
	{
		template<typename C, typename M>
		bool operator() (const C&c1, const M&c2)const
		{
			return c1 > c2;
		}
	};
	struct BearEqual
	{
		template<typename C, typename M>
		bool operator()(const C&c1, const M&c2)const
		{
			return c1 == c2;
		}
	};

	template<typename C>
	struct BearNot
	{
		C c;
		BearNot(C&c_):c(c_) {};
		BearNot(BearNot&compor) { copy(compor); }
		BearNot() {}
		template<typename M>
		bool operator()(M&c1, M&c2)
		{
			return !c(c1,c2);
		}
	
		inline	void copy(const BearNot& compor) { c = compor.c; }
		inline void swap(BearNot& compor) {  bear_swap(c, compor.c); }
		inline BearNot&operator=(const BearNot&compor) { copy(compor); return *this; }

	};
	template<typename C>
	inline BearNot<C> bear_bind_not(C&compare)
	{

		return BearNot<C>( compare);
	}
	
	template<typename C>
	inline C bear_min(C &&a,C&& b)
	{
		if (a > b)
			return b;
		return a;
	}
	template<typename C>
	inline C bear_min(const C &a, C &&b)
	{
		if (a > b)
			return b;
		return a;
	}
	template<typename C>
	inline C bear_min(C &&a, const C& b)
	{
		if (a > b)
			return b;
		return a;
	}
	template<typename C>
	inline C bear_min(const C &a, const C& b)
	{
		if (a > b)
			return b;
		return a;
	}
	template<typename C>
	inline C bear_max(C&& a, C&& b)
	{
		if (a < b)
			return b;
		return a;
	}
	template<typename C>
	inline C bear_max(const C& a, C&& b)
	{
		if (a < b)
			return b;
		return a;
	}
	template<typename C>
	inline C bear_max(C&& a, const C& b)
	{
		if (a < b)
			return b;
		return a;
	}
	template<typename C>
	inline C bear_max(const C& a, const C& b)
	{
		if (a < b)
			return b;
		return a;
	}
	template <class T>
	inline static void bear_clamp(T& val, const T& _low, const T& _high) {
		if (val < _low) val = _low;
		else if (val > _high)
			val = _high;
	};
	template <class T>
	inline static T	bear_clampr(const T& val, const T& _low, const T& _high) {
		if (val < _low)	return _low;
		else if (val > _high)	return _high;
		else					return val;
	};

}