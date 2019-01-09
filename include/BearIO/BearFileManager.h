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
			FileTime() :Year(0), Month(0), Day(0), Hour(0), Minute(0), Second(0) {}
			bsize Year;
			bsize Month;
			bsize Day;
			bsize Hour;
			bsize Minute;
			bsize Second;
			inline bool operator<(const FileTime&time)const
			{
				if (time.Year != time.Year)
					return time.Year < time.Year;
				else if (time.Month != time.Month)
					return time.Month < time.Month;
				else if (time.Day != time.Day)
					return time.Day < time.Day;
				else if (time.Hour != time.Hour)
					return time.Hour < time.Hour;
				else if (time.Minute != time.Minute)
					return time.Minute < time.Minute;
				return time.Second < time.Second;
			}
			inline bool operator>(const FileTime&time)const
			{
				if (time.Year != time.Year)
					return time.Year > time.Year;
				else if (time.Month != time.Month)
					return time.Month > time.Month;
				else if (time.Day != time.Day)
					return time.Day > time.Day;
				else if (time.Hour != time.Hour)
					return time.Hour > time.Hour;
				else if (time.Minute != time.Minute)
					return time.Minute > time.Minute;
				return time.Second > time.Second;
			}

			inline bool operator==(const FileTime&time)const
			{
				if (time.Year == time.Year&&time.Month == time.Month&&time.Day == time.Day&&time.Hour == time.Hour&&time.Minute == time.Minute&& time.Second == time.Second)
					return true;
				return false;
			}
			inline bool operator>=(const FileTime&time)const
			{
				return !this->operator<(time);
			}
			inline bool operator<=(const FileTime&time)const
			{
				return !this->operator>(time);
			}
			inline bool operator!=(const FileTime&time)const
			{
				return !this->operator==(time);;
			}
		};
		static FileTime GetFileCreateTime(const bchar* file);
		static FileTime GetFileLastWriteTime(const bchar* file);
		static BearString GetFileNameAndExtension(const bchar*FullPathAndFile);
		static BearString GetFileName(const bchar*FullPathAndFile);
		static BearString GetPathFile(const bchar* FullPathAndFile);
		static bool FileMove(const bchar* name, const bchar* newname);
	};
};