
bool BearCore::BearFileManager::FileCopy(const bchar * in, const bchar * out)
{
	return CopyFile(in, out, false);
}


bool BearCore::BearFileManager::DirectoryCreate(const bchar * path)
{
#ifdef UNICODE
	return CreateDirectoryW(path, NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
#else
	return CreateDirectoryA(path, NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
#endif
}

bool BearCore::BearFileManager::DirectoryExists(const bchar * name)
{

	DWORD dwAttrs = GetFileAttributes(name);

	if (dwAttrs == 16 || dwAttrs == 48 || dwAttrs == 22)
		return true;
	return false;
}
void BearCore::BearFileManager::GetWorkPath(BearStringPath & path)
{
	GetCurrentDirectory(MAX_PATH , path);
	PathOptimization(path);
}

void BearCore::BearFileManager::GetApplicationPath(BearStringPath & path)
{

	GetModuleFileName(GetModuleHandle(NULL), path, MAX_PATH);
	BearString::ToCharWithEnd(path, BEAR_PATH[0])[0] = 0;
	PathOptimization(path);
}


static void Find(BearCore::BearVector<BearCore::BearString>& list, const bchar* path, const bchar* ext, bool full_path, bool findFile = true)
{
	WIN32_FIND_DATA file;
	BearCore::BearStringPath full;
	BearCore::BearString::Copy(full, path);
	BearCore::BearString::Contact(full, BEAR_PATH);
	BearCore::BearString::Contact(full, ext);
	HANDLE search_handle = FindFirstFile(full, &file);
	if (reinterpret_cast<bint>(search_handle) != -1)
	{
		do
		{
			if (file.dwFileAttributes & 32)
			{
				if (!findFile)
					continue;
			}
			else
			{
				if (findFile)
					continue;
			}
			if (file.cFileName[0] == TEXT('.'))
			{
				if (file.cFileName[1] == 0 || ((file.cFileName[1] == TEXT('.') && file.cFileName[2] == 0)))
				{
						continue;
				}
			}
			if (full_path)
			{
				BearCore::BearStringPath item;
				BearCore::BearString::Copy(item, path);
				BearCore::BearString::Contact(item, BEAR_PATH);
				BearCore::BearString::Contact(item, file.cFileName);
				list.push_back(item);
			}
			else
			{
				BearCore::BearStringPath item;
				BearCore::BearString::Copy(item, file.cFileName);
				list.push_back(item);
			}
		} while (FindNextFile(search_handle, &file));

	}
	FindClose(search_handle);
}

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
bool BearCore::BearFileManager::FileMove(const bchar * name, const bchar * newname)
{
#ifdef UNICODE
	return _wrename(name, newname) != -1;
#else
	return rename(name, newname) != -1;
#endif
}