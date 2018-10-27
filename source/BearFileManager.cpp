#include "BearCore.hpp"
#ifdef WINDOWS
#include "Windows/BearFileManager_Windows.h"
#elif LINUX
#endif
#include <sys/stat.h>
#include <io.h>


bool BearCore::BearFileManager::FileExists(const bchar * name)
{
	struct _stat buffer;
#ifdef UNICODE
	int exist = _wstat(name, &buffer);
#else
	int exist = _stat(name, &buffer);
#endif
	if (exist == 0)
		return true;
	else // -1
		return false;
}

bool BearCore::BearFileManager::FileDelete(const bchar * name)
{
#ifdef UNICODE
	return _wremove(name) != -1;
#else
	return remove(name) != -1;
#endif
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
#ifdef UNICODE
	_wfopen_s(&file, name, TEXT("rb"));
#else
	fopen_s(&file, name, "rb");
#endif
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
#ifdef UNICODE
	return _wrename(name, newname) != -1;
#else
	return rename(name, newname) != -1;
#endif
}
