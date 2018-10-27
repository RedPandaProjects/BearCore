#include "BearCore.hpp"
#ifdef DEBUG 
static bool LDebugMemory = false;
struct BearDebugMemoryBlock
{
	BearDebugMemoryBlock(const char*name, void*ptr) :name(name), ptr(ptr) {	}
	BearDebugMemoryBlock(void*ptr) :name(0), ptr(ptr) {	}
	const char*name;
	void*ptr;
	bool operator<(const BearDebugMemoryBlock&block) const
	{
		return ptr < block.ptr;
	}
};
static std::vector<BearDebugMemoryBlock> LMemoryBlocks;

static void AddBlock(BearDebugMemoryBlock&&memory)
{
	if (!LDebugMemory)return;
	LMemoryBlocks.push_back(memory);
	BearCore::bear_sort(LMemoryBlocks.begin(), LMemoryBlocks.end());
}
static void ReBlock(void*old, void*new_block)
{
	auto find = BearCore::bear_lower_bound(LMemoryBlocks.begin(), LMemoryBlocks.end(), BearDebugMemoryBlock(old));
	if (find == LMemoryBlocks.end() || find->ptr != old)return;
	find->ptr = new_block;;
	BearCore::bear_sort(LMemoryBlocks.begin(), LMemoryBlocks.end());
}
static void SubBlock(void*old)
{
	auto find = BearCore::bear_lower_bound(LMemoryBlocks.begin(), LMemoryBlocks.end(), BearDebugMemoryBlock(old));
	if (find == LMemoryBlocks.end() || find->ptr != old)return;
	LMemoryBlocks.erase(find);
}
#endif
void * BearCore::BearMemory::Malloc(bsize size
#ifdef DEBUG
	, const char*name
#endif
)
{

#ifdef DEBUG 
	void*ptr = malloc(size);
	AddBlock(BearDebugMemoryBlock(name, ptr));
	return ptr;
#else
	return malloc(size);
#endif
}

void * BearCore::BearMemory::Realloc(void * old, bsize new_size
#ifdef DEBUG
	, const char*name
#endif
)
{
#ifdef DEBUG 
	if (!old)return Malloc(new_size, name);
	void*ptr = realloc(old, new_size);
	ReBlock(old, ptr);
	return ptr;
#else
	return realloc(old, new_size);
#endif
}

void BearCore::BearMemory::Free(void * ptr)
{
#ifdef DEBUG 
	SubBlock(ptr);
#endif
	free(ptr);
}

void BearCore::BearMemory::Swap(void * a, void * b, bsize size)
{
	char*c = reinterpret_cast<char*>(a);
	char*d = reinterpret_cast<char*>(b);
	while (size--)
	{
		char m = *c;
		*c = *d;
		*d = m;
		c++;
		d++;
	}
}
#ifdef DEBUG
void BearCore::BearMemory::DebugCheak()
{
	if (!LMemoryBlocks.empty())
	{
		BearDebug::ErrorPrintf(TEXT("------------------------------MEMORY------------------------------\n"));
		auto begin = LMemoryBlocks.begin();
		auto end = LMemoryBlocks.end();
		while (begin != end)
		{
			BearDebug::ErrorPrintf(BEAR_PRINT_ANSI TEXT(":0x%p\n"), begin->name, begin->ptr);
			begin++;
		}
		BearDebug::ErrorPrintf(TEXT("------------------------------------------------------------------\n"));
	}

}
void BearCore::BearMemory::DebugOn()
{
	LDebugMemory = true;
}

void BearCore::BearMemory::DebugOff()
{
	LDebugMemory = false;
}
#endif
