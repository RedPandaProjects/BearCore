
struct lib
{
	HMODULE Module;
	BearCore::BearMap<BearCore::BearStringConteniar, FARPROC> Procs;
};
BearCore::BearMap<BearCore::BearStringConteniar, lib> Libs;
bool BearCore::BearProjectTool::CheckProject(const bchar * name)
{
	auto Item = Libs.find(BearStringConteniar(name, false));
	if (Item == Libs.end())
	{
		const bchar*name_project = name;
		BearStringPath fullname,main_project,name_data;
		BearString::Copy(main_project, TEXT(BEAR_TO_STRING(MAIN_PROJECT_NAME)));
		if (BearString::ToChar(main_project, TEXT('_')))
			BearString::ToChar(main_project, TEXT('_'))[0] = 0;

		BearString::Copy(fullname, TEXT(BEAR_TO_STRING(MAIN_PROJECT_NAME)));
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
inline void BearCore::BearProjectTool::Destory()
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
inline void BearCore::BearProjectTool::UnLoad(const bchar * name)
{
	auto Item = Libs.find(BearStringConteniar(name, false));
	if (Item != Libs.end())
	{
		FreeLibrary(Item->second.Module);
		Libs.erase(Item);
	}
}
void * BearCore::BearProjectTool::GetFunctionInProjectImpl(const bchar * name, const bchar * function)
{
	auto Item= Libs.find(BearStringConteniar( name,false));
	if (Item == Libs.end())
	{
		const bchar*name_project = name;
		BearStringPath fullname, main_project, name_data;
		BearString::Copy(main_project, TEXT(BEAR_TO_STRING(MAIN_PROJECT_NAME)));
		if (BearString::ToChar(main_project, TEXT('_')))
			BearString::ToChar(main_project, TEXT('_'))[0] = 0;

		BearString::Copy(fullname, TEXT(BEAR_TO_STRING(MAIN_PROJECT_NAME)));
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
		BEAR_FATALERROR(obj.Module, TEXT("Бибилиотека %s не существует или повреждена. Ошибка:0x%x"), fullname, GetLastError());
		Libs.insert(name_project, obj);
		Item = Libs.find(BearStringConteniar(name_project, false));
	}
	auto ItemProc = Item->second.Procs.find(BearStringConteniar(function,false));
	if (ItemProc == Item->second.Procs.end())
	{
		FARPROC proc = GetProcAddress(Item->second.Module, *BearEncoding::ToANSI(function));
		BEAR_FATALERROR(proc, TEXT("Функция %s не существует в библиотеке %s"), function, name);
		Item->second.Procs.insert(function, proc);
		return proc;
	}
	return ItemProc->second;
}
