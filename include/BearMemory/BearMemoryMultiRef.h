#pragma once

template<class P>
struct BearMemoryMultiRef
{
private:
	struct data
	{
		bsize m_count;
		P m_data;
	};
	data*m_data;
public:
	BearMemoryMultiRef():m_data(0)
	{
	}
	~BearMemoryMultiRef()
	{
		clear();
	}
	BearMemoryMultiRef(const BearMemoryMultiRef&ptr) :m_data(0)
	{
		copy(ptr);
	}
	BearMemoryMultiRef( BearMemoryMultiRef&&ptr) :m_data(0)
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
			m_data->m_data.~P();
			bear_free(m_data);
				
		}
		m_data = 0;
		return;
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
	const P*operator->()const { return get(); }
	P*operator->() { return get(); }
	bool is_one()const { if (m_data)return m_data->m_count == 1; return false; }
	BearMemoryMultiRef&operator=(const BearMemoryMultiRef&ptr) { copy(ptr); return*this; };
	BearMemoryMultiRef&operator=( BearMemoryMultiRef&&ptr) { swap(ptr); return*this; };
	void swap(BearMemoryMultiRef&ptr)
	{
		bear_swap(ptr.m_data, m_data);
	}
	void copy(const BearMemoryMultiRef&ptr)
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