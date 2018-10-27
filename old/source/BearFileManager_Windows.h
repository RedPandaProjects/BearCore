bool BearCore::BearFileManager::FileCopy(const bchar * in, const bchar * out)
{
	return CopyFile(in, out, false);
}
bool BearCore::BearFileManager::DirectoryCreate(const bchar * path)
{
	return CreateDirectory(path, NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
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
	GetCurrentDirectory(MAX_PATH * 2, path);
}

void BearCore::BearFileManager::GetApplicationPath(BearStringPath & path)
{

	GetModuleFileName(GetModuleHandle(NULL), path, MAX_PATH * 2);

#ifdef WIN
	BearString::ToCharWithEnd(path, TEXT('\\'))[0] = 0;
#else
	BearString::ToCharWithEnd(path, TEXT('/'))[0] = 0;
#endif
}


static void WinFind(BearCore::BearVector<BearCore::BearString>& list, const bchar* path, const bchar* ext, bool full_path, bool findFile = true)
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
				if (file.cFileName[1] == 0 || (file.cFileName[1] == TEXT('.') || file.cFileName[2] == 0))
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
static void WinFindDirectory(BearCore::BearVector<BearCore::BearString>& list, const bchar * path, const bchar * curent_path, const bchar* fileextension)
{
	BearCore::BearVector<BearCore::BearString> temp;
	BearCore::BearStringPath path_temp;
	BearCore::BearString::Copy(path_temp, path);
	if (curent_path&&*curent_path)
	{
		BearCore::BearString::Contact(path_temp, BEAR_PATH);
		BearCore::BearString::Contact(path_temp, curent_path);
	}



	WinFind(temp, path_temp, fileextension, false, false);

	auto begin = temp.begin();
	auto end = temp.end();
	while (begin != end)
	{
		path_temp[0] = 0;
		if (curent_path&&*curent_path)
		{
			BearCore::BearString::Copy(path_temp, curent_path);
			BearCore::BearString::Contact(path_temp, BEAR_PATH);
		}

		BearCore::BearString::Contact(path_temp, **begin);
		begin->assign(path_temp);

		WinFindDirectory(list, path, path_temp, fileextension);
		begin++;
	}
	list.insert(list.end(), temp.begin(), temp.end());
}
void WinFindDirectory(BearCore::BearVector<BearCore::BearString>& list, const bchar * path, const bchar* fileextension)
{
	BearCore::BearVector<BearCore::BearString> temp;
	BearCore::BearStringPath path_temp;
	BearCore::BearString::Copy(path_temp, path);
	 
	WinFind(temp, path, fileextension, true, false);
	auto begin = temp.begin();
	auto end = temp.end();
	while (begin != end)
	{
		WinFindDirectory(list, **begin, fileextension);

		begin++;
	}

	if(temp.size())
	
	list.insert(list.end(), temp.begin(), temp.end());
}

void BearCore::BearFileManager::FindFiles(BearVector<BearString>& list, const bchar * path, const bchar * fileextension, bool allpath, bool all)
{
	WinFind(list, path, fileextension, allpath);
	if (all)
	{
		if (allpath)
		{
			BearCore::BearVector<BearCore::BearString> path_list;
			FindDirectories(path_list, path, TEXT("*"), true, true);
			auto begin = path_list.begin(), end = path_list.end();
			while (begin != end)
			{
				WinFind(list, **begin, fileextension, allpath);
				begin++;

			}
		}
		else
		{
			BearCore::BearVector<BearCore::BearString> path_list, file_list;
			FindDirectories(path_list, path, TEXT("*"), false, true);

			auto begin = path_list.begin(), end = path_list.end();
			while (begin != end)
			{
				BearStringPath path_temp;
				BearCore::BearString::Copy(path_temp, path);
				BearCore::BearString::Contact(path_temp, BEAR_PATH);
				BearCore::BearString::Contact(path_temp, **begin);

				WinFind(file_list, path_temp, fileextension, false);
				auto begin1 = file_list.begin(), end1 = file_list.end();
				while (begin1 != end1)
				{
					BearStringPath temp1;
					BearCore::BearString::Copy(temp1, **begin);
					BearCore::BearString::Contact(temp1, BEAR_PATH);
					BearCore::BearString::Contact(temp1, **begin1);
					list.push_back(temp1);
					begin1++;
				}
				file_list.clear();
				begin++;
			}

		}
	}
}

void BearCore::BearFileManager::FindDirectories(BearVector<BearString>& list, const bchar * path, const bchar * fileextension, bool allpath, bool all)
{
	if (!all)
		WinFind(list, path, fileextension, allpath, false);
	else if (allpath)
		WinFindDirectory(list, path, fileextension);
	else
		WinFindDirectory(list, path, TEXT(""), fileextension);
}





