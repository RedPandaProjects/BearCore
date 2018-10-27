#pragma once
namespace  BearCore
{
	class BEARTOOL_API BearFileManager 
	{
	public:
		static void FindFiles(BearVector<BearString> &list, const bchar*  path, const bchar* fileextension, bool allpath = true, bool subPath = true);
		static void FindDirectories(BearVector<BearString> &list, const bchar* path, const bchar* fileextension, bool allpath = true, bool subPath = true);
		static bool FileExists(const bchar* name);
		static bool FileDelete(const bchar* name);
		static bool DirectoryCreate(const bchar* path);
		static bool DirectoryExists(const bchar* name);
		static bool DirectoryDelete(const bchar* name, bool deleteall);
		static bool DirectoryRename(const bchar*path, const bchar* newpath);
		static bool DirectoryMove(const bchar*path, const bchar* newpath);
		static bool FileCopy(const bchar* file, const bchar*newfile);
		static int64 FileSize(const bchar*name);
		static void GetWorkPath(BearStringPath&path);
		static void GetApplicationPath(BearStringPath&path);
		struct FileTime
		{
			uint32 Year;
			uint32 Month;
			uint32 Day;
			uint32 Hour;
			uint32 Minute;
			uint32 Second;
		};
		static FileTime GetTime—reationFile(const bchar* file);
		static FileTime GetTime—hangeFile(const bchar* file);
		static BearString GetFileNameAndExtension(const bchar*FullPathAndFile);
		static BearString GetFileName(const bchar*FullPathAndFile);
		static BearString GetPathFile(const bchar* FullPathAndFile);
		static bool FileMove(const bchar* name, const bchar* newname);
	};
};