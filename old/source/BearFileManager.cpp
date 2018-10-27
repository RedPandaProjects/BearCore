#include "BearCore.hpp"
#ifdef WIN
#include "BearFileManager_Windows.h"
#else
#endif
#include <sys/stat.h>
#include <io.h>


bool BearCore::BearFileManager::FileExists(const bchar * name)
{
	struct stat buffer;
	int exist = stat(*BearString::ConvertToANSI(name), &buffer);
	if (exist == 0)
		return true;
	else // -1
		return false;
}

bool BearCore::BearFileManager::FileDelete(const bchar * name)
{

	return remove(*BearString::ConvertToANSI(name)) != -1;
}



bool BearCore::BearFileManager::DirectoryDelete(const bchar * name, bool deleteall)
{
	return false;
}

bool BearCore::BearFileManager::DirectoryRename(const bchar * path, const bchar * newpath)
{
	return false;
}

bool BearCore::BearFileManager::DirectoryMove(const bchar * path, const bchar * newpath)
{
	return false;
}


int64 BearCore::BearFileManager::FileSize(const bchar * name)
{

	FILE*file = 0;
	fopen_s(&file, *BearString::ConvertToANSI(name), "rb");
	if (!file)
		return -1;
	fseek(file, 0, SEEK_END);
	int64 size = ftell(file);
	fclose(file);
	return size;
}



BearCore::BearFileManager::FileTime BearCore::BearFileManager::GetTime—reationFile(const bchar * file)
{
	return FileTime();
}

BearCore::BearFileManager::FileTime BearCore::BearFileManager::GetTime—hangeFile(const bchar * file)
{
	return FileTime();
}

BearCore::BearString BearCore::BearFileManager::GetFileNameAndExtension(const bchar * FullPathAndFile)
{
	return BearString();
}

BearCore::BearString BearCore::BearFileManager::GetFileName(const bchar * FullPathAndFile)
{
	return BearString();
}

BearCore::BearString BearCore::BearFileManager::GetPathFile(const bchar * FullPathAndFile)
{
	return BearString();
}

bool BearCore::BearFileManager::FileMove(const bchar * name, const bchar * newname)
{
	return rename(*BearString::ConvertToANSI(name), *BearString::ConvertToANSI(newname)) != -1;
}
