#pragma once
namespace BearCore
{
	template<class Key,class T,class C=BearLess>
	class BearMap :public std::map<Key,T,C, bear_allocator<std::pair<Key,T>>>
	{
	private:
		typedef	std::map<Key, T, C, bear_allocator<std::pair<Key, T>>> map;
	public:
		BearMap(BearMap&&right) : map(right) {}
		BearMap(const BearMap&right) : map(right) {}
		inline void copy(const BearMap&right) { *this = right; }

		BearMap() : map() {}
		inline void insert(const Key&k, const T&t)
		{
			map::insert(std::pair<Key, T>(k, t));
		}
	};
}