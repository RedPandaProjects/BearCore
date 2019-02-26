#include "BearCore.hpp"
BEARTOOL_API BearCore::BearIncluder BearCore::GIncluderDefault;
BearCore::BearIncluder::BearIncluder()
{
}

BearCore::BearStreamRef< BearCore::BearInputStream> BearCore::BearIncluder::OpenAsStream(const bchar * name)
{
	BearFileStream *File = bear_new<BearFileStream>();
	BEAR_FATALERROR(File->Open(name), TEXT("Неудалось открыть [" BEAR_PRINT_CURRENT "]"), name);
	return BearStreamRef<BearInputStream>(File);
}

BearCore::BearStreamRef< BearCore::BearBufferedReader> BearCore::BearIncluder::OpenAsBuffer(const bchar * name)
{
	BearFileStream File;
	BEAR_FATALERROR(File.Open(name), TEXT("Неудалось открыть [" BEAR_PRINT_CURRENT "]"), name);
	return BearStreamRef<BearBufferedReader>(bear_new<BearMemoryStream>(File));
}

BearCore::BearIncluder::~BearIncluder()
{
}
