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


bsize BearCore::BearFileManager::GetFileSize(const bchar * name)
{

	FILE*file = 0;
#ifdef UNICODE
	_wfopen_s(&file, name, TEXT("rb"));
#else
	fopen_s(&file, name, "rb");
#endif
	if (!file)
		return 0;
	fseek(file, 0, SEEK_END);
	int64 size = ftell(file);
	fclose(file);
	return static_cast<bsize>(size);
}



BearCore::BearFileManager::FileTime BearCore::BearFileManager::GetFileCreateTime(const bchar * file)
{
	BearCore::BearFileManager::FileTime ft;
	HANDLE fH;
	FILETIME creationTime;
	SYSTEMTIME sysTime;
	fH = CreateFile(file, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (fH != INVALID_HANDLE_VALUE)
	{
		GetFileTime(fH, &creationTime, 0, 0);
		FileTimeToSystemTime(&creationTime, &sysTime);
		ft.Year = sysTime.wYear;
		ft.Month = sysTime.wMonth;
		ft.Day = sysTime.wDay;
		ft.Hour = sysTime.wHour;
		ft.Minute = sysTime.wMinute;
		ft.Second = sysTime.wSecond;
		CloseHandle(fH);
	}
	return ft;
}

BearCore::BearFileManager::FileTime BearCore::BearFileManager::GetFileLastWriteTime(const bchar * file)
{
	BearCore::BearFileManager::FileTime ft;
	HANDLE fH;
	FILETIME creationTime;
	SYSTEMTIME sysTime;
	fH = CreateFile(file, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (fH != INVALID_HANDLE_VALUE)
	{
		GetFileTime(fH, 0, 0, &creationTime);
		FileTimeToSystemTime(&creationTime, &sysTime);
		ft.Year = sysTime.wYear;
		ft.Month = sysTime.wMonth ;
		ft.Day = sysTime.wDay;
		ft.Hour = sysTime.wHour;
		ft.Minute = sysTime.wMinute;
		ft.Second = sysTime.wSecond;
		CloseHandle(fH);
	}
	return ft;
}

BearCore::BearString BearCore::BearFileManager::GetFileNameAndExtension(const bchar * FullPathAndFile)
{
	BearString temp(FullPathAndFile);
	temp.seek(0);
	if (temp.to_char_with_end(BEAR_PATH[0]))
		temp++;
	return temp;
}

BearCore::BearString BearCore::BearFileManager::GetFileName(const bchar * FullPathAndFile)
{
	BearString temp(FullPathAndFile);
	if (temp.to_char_with_end(TEXT('.')))
		**temp = 0;
	temp.seek(0);
	if (temp.to_char_with_end(BEAR_PATH[0]))
		temp++;
	else
		temp.seek(0);
	return temp;
}

BearCore::BearString BearCore::BearFileManager::GetPathFile(const bchar * FullPathAndFile)
{
	BearString temp(FullPathAndFile);
	if (temp.to_char_with_end(TEXT('\\')))
		**temp = 0;
	temp.seek(0);
	return temp;
}

bool BearCore::BearFileManager::FileMove(const bchar * name, const bchar * newname)
{
#ifdef UNICODE
	return _wrename(name, newname) != -1;
#else
	return rename(name, newname) != -1;
#endif
}

void BearCore::BearFileManager::PathOptimization(bchar * in)
{
	bchar*path = in;
	bchar*path_lost = in;
	bchar* b = in;
	bchar* e = in+BearString::GetSize(in);
	{
		const bchar*shift = b;
		while (*shift == BEAR_PATH[0])
		{
			shift++;
		}
		if (shift - b )
		{
			bear_move(b , shift, BearString::GetSize(shift) + 1);
		}
	}
	while (b != e)
	{
	

		if (*b == BEAR_PATH[0])
		{
			
			const bchar*shift = b;
			while (*shift == BEAR_PATH[0])
			{
				shift++;
			}
			if (shift - b > 1)
			{
				bear_move(b + 1, shift, BearString::GetSize(shift) + 1);
				path = in;
				b = in;
				e = in + BearString::GetSize(in);
				continue;
			}
	
			path_lost = path;
			path = b;
		
		}
		if (b[0] == TEXT('.') && b[1] == TEXT('.') && b[2]!= TEXT('.') && path != in)
		{
			if (path_lost[0] == BEAR_PATH[0])
			{
				if (bear_compare(&path_lost[1], TEXT(".."), 2) == 0 && path_lost[3] != TEXT('.')) {

					b++;
					continue;
				}
			}
			else
			{
				if (bear_compare(&path_lost[0], TEXT(".."), 2) == 0 && path_lost[2] != TEXT('.')) {

					b++;
					continue;
				}
			}
			
			b += 2;
			bear_move(path_lost, b, BearString::GetSize(b) + 1);
			path = in;
			path_lost = in;
			b = in;
			e = in + BearString::GetSize(in);
			continue;
		}
		b++;
	}

	{
		e = in + BearString::GetSize(in) - 1;
		while (b != e && *e == BEAR_PATH[0])
		{
			e[0] = 0;
			e--;
		}
	}
}


