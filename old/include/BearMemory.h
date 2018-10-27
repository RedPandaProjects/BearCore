#pragma once
namespace BearCore
{
	class BEARTOOL_API BearMemory
	{
	public:
		static void* Malloc(bsize size
#ifdef DEBUG
			,const char*name
#endif
		);
		static void* Realloc(void*old, bsize new_size
#ifdef DEBUG
			,const char*name
#endif
		);

		static void  Free(void*ptr);
		static void Swap(void*a, void*b, bsize size);
		BEAR_FUNCTION_DEBUG(static void, DebugCheak,);
		BEAR_FUNCTION_DEBUG(static void, DebugOn, );
		BEAR_FUNCTION_DEBUG(static void, DebugOff, );
	};
	template<typename C>
	inline void bear_copy(C*dst, const C*source, bsize count)
	{
		memcpy(reinterpret_cast<void*>(dst), reinterpret_cast<const void*>(source), count*sizeof(C));
	}
	
	inline void bear_copy(void*dst, const void*source, bsize size)
	{
		memcpy(dst, source, size);
	}

	template<typename C>
	inline void bear_move(C*dst, bint move, bsize count)
	{
		memmove(dst + move,dst , sizeof(C)*count);
	}
	inline void bear_move(void*dst, bint move, bsize size)
	{
		memmove(reinterpret_cast<char*>(dst) + move,dst, size);
	}

	template<typename C>
	inline void bear_fill(C*c, bsize count, uint8 byte = 0)
	{
		memset(dst, byte, sizeof(C)*size);
	}
	inline void bear_fill(void*dst, bsize size, uint8 byte=0)
	{
		memset(dst, byte, size);
	}
	template<typename C>
	inline void bear_fill(C&c)
	{
		bear_fill(&c, 1);
	}

	template<typename C>
	inline void bear_swap(C*a,C*b, bsize count)
	{
		C*end = a + count;
		while (a != end)
		{
			std::swap(*a, *b);
			a++; b++;
		}
	}
	inline void bear_swap(void*a, void*b, bsize size)
	{
		bear_swap<char>(reinterpret_cast<char*>(a), reinterpret_cast<char*>(b), size);
	}
	template<typename C>
	inline void bear_swap(C&a, C&b)
	{
		if  (sizeof(C) == sizeof(uint64))
		{
			uint64 c = *reinterpret_cast<uint64*>(&a);
			*reinterpret_cast<uint64*>(&a) = *reinterpret_cast<uint64*>(&b);
			*reinterpret_cast<uint64*>(&b) = c;
		}
		else if  (sizeof(C) == sizeof(uint32))
		{
			uint32 c = *reinterpret_cast<uint32*>(&a);
			*reinterpret_cast<uint32*>(&a) = *reinterpret_cast<uint32*>(&b);
			*reinterpret_cast<uint32*>(&b) = c;
		}
		else if  (sizeof(C) == sizeof(uint16))
		{
			uint16 c = *reinterpret_cast<uint16*>(&a);
			*reinterpret_cast<uint16*>(&a) = *reinterpret_cast<uint16*>(&b);
			*reinterpret_cast<uint16*>(&b) = c;
		}
		else if  (sizeof(C) == sizeof(uint8))
		{
			uint8 c = *reinterpret_cast<uint8*>(&a);
			*reinterpret_cast<uint8*>(&a) = *reinterpret_cast<uint8*>(&b);
			*reinterpret_cast<uint8*>(&b) = c;
		}
		else 
		{ 
			BearMemory::Swap(&a, &b, sizeof(C));
		}
	}

	template<typename C>
	inline bint bear_compare(const C*a, const C*b, bsize count)
	{
		return static_cast<bint>(memcmp(reinterpret_cast<const void*>(a), reinterpret_cast<const void*>(b), sizeof(C)*count));
	}
	inline bint bear_compare(const void*a, const void*b, bsize size)
	{
		return static_cast<bint>(memcmp(a,b, size));
	}

	template<typename C>
	C*bear_alloc(bsize count)
	{
		return reinterpret_cast<C*>(BearMemory::Malloc(sizeof(C)*count,typeid(C).name()));
	}

	template<typename C>
	C*bear_new()
	{
		C*c = reinterpret_cast<C*>(BearMemory::Malloc(sizeof(C), typeid(C).name()));
		new(c)C();
		return c;
	}
	template<typename C, class...D>
	C*bear_new(D...d)
	{
		C*c=reinterpret_cast<C*>(BearMemory::Malloc(sizeof(C), typeid(C).name()));
		new(c)C(d...);
		return c;
	}

	template<typename C>
	C*bear_realloc(C*old,bsize new_count)
	{
		return reinterpret_cast<C*>(BearMemory::Realloc(reinterpret_cast<void*>(old),sizeof(C)*new_count, typeid(C).name()));
	}

	template<typename C>
	void bear_free(C*old)
	{
		if(old)
		BearMemory::Free(reinterpret_cast<void*>(old));
	}
	template<typename C>
	void bear_delete(C*old)
	{
		if (old)
		old->~C();
		BearMemory::Free(reinterpret_cast<void*>(old));
	}
	inline bsize bear_recommended_size(bsize size)
	{
		bsize out = 1;
		while (out <= size)
		{
			out <<= 1;
		}
		return out;
	}
	template<class P>
	struct BearPtr
	{
	public:
		BearPtr(P*p, bool auto_free = true) :m_p(p), m_free(auto_free)
		{}
		BearPtr() :m_p(0), m_free(false) {};
		BearPtr(const BearPtr&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };
		BearPtr( BearPtr&&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };

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

		~BearPtr() { clear(); }
		P*operator->() { return m_p; }
		const P*operator->()const { return m_p; }
		P*operator*() { return m_p; }
		const P*operator*()const { return m_p; }


		BearPtr&operator=( BearPtr&&ptr) { clear(); swap(ptr);    return*this; };
		BearPtr&operator=(const BearPtr&ptr) { clear(); swap(ptr);    return*this; };
		void copy(const BearPtr&ptr)  { clear(); m_p = ptr.m_p; ptr.m_p = 0; m_free = ptr.m_free; ptr.m_free = false; }
		void swap(BearPtr&ptr) { bear_swap(ptr.m_p, m_p);  bear_swap(ptr.m_free, m_free); }


		P&operator[](bsize id) { return m_p[id]; }
		const P&operator[](bsize id) const { return m_p[id]; }
	private:
		mutable	P*m_p;
		mutable bool m_free;
	};

	template<>
	struct BearPtr<void*>
	{
	public:
		BearPtr(void*p, bool auto_free = true) :m_p(p), m_free(auto_free)
		{}
		BearPtr() :m_p(0), m_free(false) {};
		BearPtr(const BearPtr&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };
		BearPtr(BearPtr&&ptr) :m_p(ptr.m_p), m_free(ptr.m_free) { ptr.m_p = 0; ptr.m_free = false; };

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

		~BearPtr() { clear(); }
		
		void*operator*() { return m_p; }
		const void*operator*()const { return m_p; }


		BearPtr&operator=(BearPtr&&ptr) { clear(); swap(ptr);    return*this; };
		BearPtr&operator=(const BearPtr&ptr) { clear(); swap(ptr);    return*this; };
		void copy(const BearPtr&ptr)  { clear(); m_p = ptr.m_p; ptr.m_p = 0; m_free = ptr.m_free; ptr.m_free = false; }
		void swap(const BearPtr&ptr) { bear_swap(ptr.m_p, m_p);  bear_swap(ptr.m_free, m_free); }

	private:
		mutable	void*m_p;
		mutable bool m_free;
	};


	template<class P>
	struct BearMultiPtr
	{
	private:
		struct data
		{
			bsize m_count;
			P m_data;
		};
		data*m_data;
	public:
		BearMultiPtr():m_data(0)
		{
		}
		~BearMultiPtr()
		{
			clear();
		}
		BearMultiPtr(const BearMultiPtr&ptr) :m_data(0)
		{
			copy(ptr);
		}
		BearMultiPtr( BearMultiPtr&&ptr) :m_data(0)
		{
			swap(ptr);
		}
		bool inline empty()const
		{
			return !m_data;
		}
		inline void create()
		{
			clear();
			m_data = bear_new<data>();
			m_data->m_count = 1;
		}
		inline void clear()
		{
			if (!m_data ) { return; }
			m_data->m_count--;
			if (!m_data->m_count)
			{
				bear_free(m_data);
				return;
			}
			m_data = 0;

		}
		inline P*get()
		{
			if (!m_data ) {  create(); }
			return &m_data->m_data;
		}
		inline P*get() const
		{
			if (!m_data ) { return 0; }
			return &m_data->m_data;
		}
		BearMultiPtr&operator=(const BearMultiPtr&ptr) { copy(ptr); return*this; };
		BearMultiPtr&operator=( BearMultiPtr&&ptr) { swap(ptr); return*this; };
		void swap(BearMultiPtr&ptr)
		{
			bear_swap(ptr.m_data, m_data);
		}
		void copy(const BearMultiPtr&ptr)
		{
			if (ptr.m_data != m_data)
			{
				clear();
				m_data = ptr.m_data;
				if (!m_data ) { return; }
				m_data->m_count++;
			}
		}


	};


	template<class P>
	struct BearStreamPtr
	{
	public:
		BearStreamPtr(P*p) :m_p(p)
		{}
		BearStreamPtr() :m_p(0) {};
		BearStreamPtr(const BearStreamPtr&ptr) :m_p(ptr.m_p) { ptr.m_p = 0; };
		void clear()
		{
			if (!m_p)return;
			m_p->destory();
			m_p = 0;
			//	bear_free<P>(m_p, false);
		}
		void clearNoFree() { m_p = 0; }
		~BearStreamPtr() { clear(); }
		P*operator->() { return m_p; }
		const P*operator->()const { return m_p; }
		P*operator*() { return m_p; }
		const P*operator*()const { return m_p; }

		BearStreamPtr&operator=(const BearStreamPtr&ptr) { clear(); swap(ptr);    return*this; };
		
		void copy(const BearStreamPtr&ptr) const { clear(); m_p = ptr.m_p; ptr.m_p = 0; }
		void swap(const BearStreamPtr&ptr) { bear_swap(ptr.m_p, m_p); }
		P&operator[](bsize id) { return m_p[id]; }
		const P&operator[](bsize id) const { return m_p[id]; }
	private:
		mutable P*m_p;
	};
	template <class T>
	class bear_allocator
	{
	public:
		typedef bsize size_type;
		typedef bint difference_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T value_type;

	public:
		template<class _Other>
		struct rebind { typedef bear_allocator<_Other> other; };
	public:
		pointer address(reference _Val) const { return (&_Val); }
		const_pointer address(const_reference _Val) const { return (&_Val); }
		bear_allocator() { }
		bear_allocator(const bear_allocator<T>&) { }
		template<class _Other> bear_allocator(const bear_allocator<_Other>&) { }
		template<class _Other> bear_allocator<T>& operator= (const bear_allocator<_Other>&) { return (*this); }
		bool operator== (const bear_allocator&) { return true; }
		bool operator!= (const bear_allocator&) { return false; }
		template<class _Other>
		bool operator== (const bear_allocator<_Other>&) { return false; }
		template<class _Other>
		bool operator!= (const bear_allocator<_Other>&) { return true; }
		pointer allocate(size_type n, const void* p = 0) const { return bear_alloc<T>(n); }
		char* _charalloc(size_type n) { return (char*)allocate(n); }
		void deallocate(pointer p, size_type n) const { bear_free(p); }
		void deallocate(void* p, size_type n) const { bear_free(p); }
		template<class C, class T>
		void construct(C* p, const T& _Val) { ::new ((void*)p) C(_Val); }
		template<class C>
		void destroy(C* p) { p->~C(); }
		size_type max_size() const { size_type _Count = (size_type)(-1) / sizeof(T); return (0 < _Count ? _Count : 1); }


	};

}