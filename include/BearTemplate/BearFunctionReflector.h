#pragma once
namespace  BearCore
{
	namespace Impl
	{
		template<class C>
		struct BearFunctionReturner
		{
			inline C&operator()(void*a) 
			{
				return *(C*)a;
			}
		}; 
		template<>
		struct BearFunctionReturner<void>
		{ 
			inline void operator()(void*a)
			{}
		};
		template<class C>
		struct BearFunctionRefCaller
		{
			template<typename  F,class M,class...A>
			inline void operator()(F f, M&c,A...a)
			{
				c = f(*a...);
			}
			template<typename  F, class M>
			inline void operator()(F f, M&c)
			{
				c = f();
			}
		};

		template<>
		struct BearFunctionRefCaller<void>
		{
			template<typename  F, class...A>
			inline void operator()(F f, int , A...a)
			{
				f(*a...);
			}
			template<typename  F>
			inline void operator()(F f, int)
			{
				 f();
			} 
		};
	};

	class BearArgumentContainer
	{
		
	public:
		virtual void Destroy() = 0;
		virtual void*Get()=0;
	private:
	};


	template<class C>
	class BearArgumentContainerMaker:public BearArgumentContainer
	{
	public:
		BearArgumentContainerMaker(const C&c):m_c(c){}
		~BearArgumentContainerMaker() {}
		virtual void Destroy()
		{
			bear_delete(this);
		}
		virtual void*Get()
		{
			return &m_c;
		}
	private:
		C m_c;
	};

	class BearArgumentsList :public BearVector<BearArgumentContainer*>
	{
	public:
		inline void clear()
		{
			auto b = begin();
			auto e = end();
			while (b != e)
			{
				(*b)->Destroy();
				b++;
			}
			BearVector<BearArgumentContainer*>::clear();
		}
		inline ~BearArgumentsList() { clear(); }
	};

	template<typename ...Args >
	void bear_make_arguments(BearArgumentsList&args_list, Args... args)
	{
		bear_make_arguments_impl(args_list, args...);
	}
	template<typename T, typename ...Args>
	void bear_make_arguments_impl(BearArgumentsList&args_list, const T&t, Args... args)
	{
		arg_list.push_back(bear_new<BearArgumentContainerMaker<T>>(t));
		bear_make_arguments_impl(args_list, args...);
	}
	template<typename T>
	void bear_make_arguments_impl(BearArgumentsList&args_list, const T&t)
	{
		args_list.push_back(bear_new<BearArgumentContainerMaker<T>>( t));
	}

	

	class BearFunctionRef
	{
	public:
		virtual void Destroy() = 0;
		template<class R>
		inline R CallWithArgumentsList(void**stack)
		{
			return Impl::BearFunctionReturner<bear_remove_reference<R>::type>()(Call(stack));
		}
		template<class R>
		inline R CallWithArgumentsList(const BearArgumentsList&args)
		{
			void*stack[256];
			auto begin = args.begin();
			auto end = args.end();
			bsize i = 0;
			while (begin != end)
			{
				stack[i++] = (*begin)->Get();
				begin++;
			}
			return Impl::BearFunctionReturner<bear_remove_reference<R>::type>()(Call(stack));
		}
#define CALL_IN_REF 
#define NAMEINCLUDE "BearFunctionReflectorMaker.h"
#include "BearMultiplicator.h"
#undef CALL_IN_MAKER
	protected:
		virtual void* Call(void**args) = 0;

	private:
	};	
	template<class C,typename F>
	class BearFunctionRefMaker:public BearFunctionRef
	{
	public:
		BearFunctionRefMaker(F f) :m_f(f) {}
		~BearFunctionRefMaker() {}
	private:
		virtual void Destroy()
		{
			bear_delete(this);
		}
	
#define CALL_IN_MAKER
#define NAMEINCLUDE "BearFunctionReflectorMaker.h"
#include "BearMultiplicator.h"
#undef CALL_IN_MAKER
		virtual void* Call(void**args)
		{
			call_impl(m_f, args);
			return &m_return;
		}

		F  m_f;
		C m_return;
	};
	template<typename P,class...A>
	inline  BearFunctionRef*bear_create_function_ref(P(*f)(A...))
	{
		return bear_new< BearFunctionRefMaker<bear_remove_reference<bear_remove_void<P>::type>::type, decltype(f)>>(f);
	}
	template<typename P>
	inline BearFunctionRef*bear_create_function_ref(P(*f)())
	{
		return bear_new< BearFunctionRefMaker<bear_remove_reference<bear_remove_void<P>::type>::type, decltype(f)>>(f);
	}
}