#pragma once
#include <functional>
namespace Impl
{
	template<typename Return, typename...Args>
	class BearFunctionImpl 
	{
	public:
		BearFunctionImpl():m_function(0)
		{
		}	
		explicit  BearFunctionImpl(const BearFunctionImpl& right) :m_function(right.m_function)
		{
		}
		template <typename F>
		BearFunctionImpl(F function) :m_function(function)
		{
		}
		inline Return call(Args...args) const
		{
			return m_function(args...);
		}
		inline bool empty()
		{
			return m_function == 0;
		}
		inline void copy(const BearFunctionImpl&right)
		{
			m_function = right.m_function;
		}
		inline void swap(BearFunctionImpl& right)
		{
			bear_swap(m_function,right.m_function);
		}
		inline bool equal (const BearFunctionImpl& right) const
		{
			return m_function== right.m_function;
		}
	private:
		Return(*m_function)(Args...) ;
	};
	template<typename Return, typename Class, typename...Args>
	class BearFunctionImplOfClass
	{
	public:
		BearFunctionImplOfClass() :m_function(0), m_function_const(0)
		{
		}
		explicit  BearFunctionImplOfClass(const BearFunctionImplOfClass&right) :m_function(right.m_function), m_function_const(right.m_function_const)
		{
		}
		template <typename F>
		BearFunctionImplOfClass(F function)
		{
			set(function);
		}
		inline Return call(const Class* c, Args...args) const
		{
			if(m_function)
				return (const_cast<Class*>(c)->*m_function)(args...);
			return (c->*m_function_const)(args...);
		}
		inline bool empty()
		{
			return m_function == 0;
		}
		inline void copy(const BearFunctionImplOfClass& right)
		{
			m_function = right.m_function;
			m_function_const = right.m_function_const;
		}
		inline void swap(BearFunctionImplOfClass& right)
		{
			bear_swap(m_function, right.m_function);
			bear_swap(m_function_const, right.m_function_const);
		}
		inline bool equal (const BearFunctionImplOfClass& right) const
		{
			return m_function== right.m_function&& m_function_const == right.m_function_const;
		}
	protected:
		void set(Return(Class::* function)(Args...))
		{
			m_function = function;
			m_function_const = 0;
		}
		void set(Return(Class::* function)(Args...)const)
		{
			m_function = 0;
			m_function_const = function;
		}
		Return(Class::*m_function)(Args...);
		Return(Class::* m_function_const)(Args...)const;
	};
#ifdef MSVC
	template <class F>
	struct BearGetFunctionImpl {};
	template<class Return, class...Args>
	struct BearGetFunctionImpl<Return (Args...)>
	{
		using Type = BearFunctionImpl<Return, Args...>;
	};
	template<class Return, class Class, class...Args>
	struct BearGetFunctionImpl<Return (Class:: *)(Args...)>
	{
		using Type = BearFunctionImplOfClass<Return, Class, Args...>;
	};

#endif
};

#ifdef MSVC
template<typename F>
class BearFunction:public Impl::BearGetFunctionImpl<F>::Type
{
	using base =typename Impl::BearGetFunctionImpl<F>::Type;
#else
template<typename none>
class BearFunction;
template<typename Return, typename...Args>
class BearFunction<Return(Args...)> :public Impl::BearFunctionImpl<Return,Args...>
{
	using base = typename Impl::BearFunctionImpl<Return,Args...>;
#endif
public:

	BearFunction(std::nullptr_t){}
	BearFunction() {}
	template <class FO>
	BearFunction(FO f):base(f)
	{
	}

	BearFunction(const BearFunction& right)
	{
		base::copy(right);
	}
	BearFunction(BearFunction&& right) 
	{
		base::swap(right);
	}
	inline BearFunction& operator=(const BearFunction& right)
	{
		base::copy(right);
		return *this;
	}
	inline BearFunction& operator=( BearFunction&& right)
	{
		base::swap(right);
		return *this;
	}
	inline bool operator==(const BearFunction& right)const
	{
		return base::equal(right);
	}
};
#ifndef MSVC

template<typename Return,typename Class, typename...Args>
class BearFunction<Return(Class::*)(Args...)> :public Impl::BearFunctionImplOfClass<Return,Class,Args...>
{
	using base = typename Impl::BearFunctionImplOfClass<Return,Class,Args...>;
public:
	BearFunction(std::nullptr_t){}
	BearFunction() {}
	template <class FO>
	BearFunction(FO f):base(f)
	{
	}

	BearFunction(const BearFunction& right)
	{
		base::copy(right);
	}
	BearFunction(BearFunction&& right) 
	{
		base::swap(right);
	}
	inline BearFunction& operator=(const BearFunction& right)
	{
		base::copy(right);
		return *this;
	}
	inline BearFunction& operator=( BearFunction&& right)
	{
		base::swap(right);
		return *this;
	}
	inline bool operator==(const BearFunction& right)const
	{
		return base::equal(right);
	}
};
#endif