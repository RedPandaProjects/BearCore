#pragma once
namespace BearCore
{
	class BEARTOOL_API BearThread
	{
	public:
		BEAR_CLASS_NO_COPY(BearThread);
		// регистрацы€ потока (функцы€ и еЄ аргументы);
		template<class F,class ...args>
		BearThread(F function,args&&...args):m_id(0),m_thread(0)
		{
			bear_make_arguments(m_arg, args...);
			m_fun = bear_create_function_ref(function);
			
		}
		template<class F>
		BearThread(F function) :m_id(0), m_thread(0)
		{
			m_fun = bear_create_function_ref(function);

		}
		//запустить
		void Join(const char*name);
		//ожидать пока закончитс€ поток. нельз€ в самом потоки исполнить функцыю
		void Wait();
		//быстрое проекрашение работы потока
		void Terminate();

		void Swap(BearThread&Thread);

		~BearThread();
	private:  
		void RunThread(const char*name, void * fun, void * arg);
		
		mutable void* m_id;
		mutable	uint32 m_thread;
		mutable	BearFunctionRef* m_fun;
		mutable	BearArgumentsList m_arg;
	};
}
