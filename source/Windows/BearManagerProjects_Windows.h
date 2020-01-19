
struct lib
{
	HMODULE Module;
	BearMap<BearStringConteniar, FARPROC> Procs;
};
BearMap<BearStringConteniar, lib> Libs;
bool BearManagerProjects::CheckProject(BearStringConteniar  name_)
{
	auto Item = Libs.find(name_);
	const bchar* name = *name_;
	if (Item == Libs.end())
	{
		const bchar*name_project = name;
		BearStringPath fullname,main_project,name_data;
		BearString::Copy(main_project, TEXT(BEAR_TO_STRING(MAIN_PROJECT_NAME)));
		if (BearString::ToChar(main_project, TEXT('_')))
			BearString::ToChar(main_project, TEXT('_'))[0] = 0;

		BearString::Copy(fullname,
#ifdef GCC
	TEXT("lib")
#endif
		 TEXT(BEAR_TO_STRING(MAIN_PROJECT_NAME))
		 );
		BearString::Contact(fullname, TEXT("_"));

		BearString::Copy(name_data, name);
		name = name_data;
		if (BearString::ExistPossition(name, 0, main_project))
		{
			name += BearString::GetSize(main_project);
		}
		if (name[0] == TEXT('_'))
			name++;

		BearString::Contact(fullname, name);
#ifdef _DEBUG
		BearString::Contact(fullname, TEXT("_debug"));
#elif MIXED
		BearString::Contact(fullname, TEXT("_mixed"));
#endif
		BearString::Contact(fullname, TEXT(".dll"));
		lib obj;
		obj.Module = LoadLibrary(fullname);
		if(obj.Module) Libs.insert(name_project, obj);
		return obj.Module;
	}
	return false;
}
inline void BearManagerProjects::Destory()
{
	auto begin = Libs.begin();
	auto end = Libs.end();
	while (begin != end)
	{
		if(begin->second.Module)
		FreeLibrary(begin->second.Module);
		begin++;
	}
	Libs.clear();
}
inline void BearManagerProjects::UnLoad(BearStringConteniar name)
{
	auto Item = Libs.find(name);
	if (Item != Libs.end())
	{
		FreeLibrary(Item->second.Module);
		Libs.erase(Item);
	}
}
void * BearManagerProjects::GetFunctionInProjectImpl(BearStringConteniar name_, BearStringConteniar function)
{
	auto Item= Libs.find(name_);
	const bchar* name=*name_;
	if (Item == Libs.end())
	{
		const bchar*name_project = name;
		BearStringPath fullname, main_project, name_data;
		BearString::Copy(main_project, TEXT(BEAR_TO_STRING(MAIN_PROJECT_NAME)));
		if (BearString::ToChar(main_project, TEXT('_')))
			BearString::ToChar(main_project, TEXT('_'))[0] = 0;

		BearString::Copy(fullname,
#ifdef GCC
	TEXT("lib")
#endif
		 TEXT(BEAR_TO_STRING(MAIN_PROJECT_NAME)));
		BearString::Contact(fullname, TEXT("_"));

		BearString::Copy(name_data, name);
		name = name_data;
		if (BearString::ExistPossition(name, 0, main_project))
		{
			name += BearString::GetSize(main_project);
		}
		if (name[0] == TEXT('_'))
			name++;

		BearString::Contact(fullname, name);
#ifdef DEBUG
		BearString::Contact(fullname, TEXT("_debug"));
#elif MIXED
		BearString::Contact(fullname, TEXT("_mixed"));
#endif
		BearString::Contact(fullname, TEXT(".dll"));
		lib obj;
		obj.Module = LoadLibrary(fullname);
		BEAR_FATALERROR(obj.Module, TEXT("Бибилиотека " BEAR_PRINT_STR_CURRENT " не существует или повреждена. Ошибка:0x%x"), fullname, GetLastError());
		Libs.insert(name_project, obj);
		Item = Libs.find(name_project);
	}
	auto ItemProc = Item->second.Procs.find(function);
	if (ItemProc == Item->second.Procs.end())
	{
#ifdef UNICODE
		FARPROC proc = GetProcAddress(Item->second.Module, *BearEncoding::FastToAnsi(*function));
#else
		FARPROC proc = GetProcAddress(Item->second.Module, *function);
#endif
		BEAR_FATALERROR(proc, TEXT("Функция " BEAR_PRINT_STR_CURRENT " не существует в библиотеке " BEAR_PRINT_STR_CURRENT ""), *function, name);
		Item->second.Procs.insert(function, proc);
		return reinterpret_cast<void*>( proc);
	}
	return reinterpret_cast<void*>( ItemProc->second);
}
