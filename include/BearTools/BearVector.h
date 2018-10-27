#pragma once
namespace BearCore
{
	template<class C>
	class BearVector :public std::vector<C,BearMemoryAllocator<C>>
	{
	private:
		typedef	std::vector<C, BearMemoryAllocator<C>> vector;
	public:
		BearVector(BearVector&&vector) : vector(vector) {}
		BearVector(const BearVector&vector) : vector(vector) {}
		void copy(const BearVector&right) { *this = right; }
		inline 	BearVector&operator=(BearVector&&str) { swap(str); return*this; }
		inline 	BearVector&operator=(const BearVector&str) { copy(str); return*this; }
		BearVector() : vector() {}
		BearVector(bsize count, const C& value) : vector(count, value) {}
		explicit BearVector(bsize count) : vector(count) {}
	
		const_reference operator[] (size_type pos) const { BEAR_ASSERT(pos<size());  return (*(begin() + pos)); }
		reference operator[] (size_type pos) { BEAR_ASSERT(pos < size());  return (*(begin() + pos)); }
		void clear_not_free() { erase(begin(), end()); }
		BearMemoryRef<C> popData() { auto ptr = BearMemoryRef<C>(&at(0), true); this->_Myfirst() = vector::pointer(); this->_Mylast() = vector::pointer(); this->_Myend() = vector::pointer(); return ptr; }

	};
}