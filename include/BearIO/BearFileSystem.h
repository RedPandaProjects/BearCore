#pragma once
namespace  BearCore
{
	class BEARTOOL_API BearFileSystem
	{
	public :
		BEAR_CLASS_NO_COPY(BearFileSystem);
		BearFileSystem();
		~BearFileSystem();

		void UpdatePath(const bchar*floder, bsize id,BearStringPath&path);


		void Update(const bchar*floder, const bchar*file, BearStringPath&path);
		void Update(const bchar*floder, const bchar*file, const bchar*e, BearStringPath&path);
		
		bool ExistFloder(const bchar*floder, bsize id);
		bool ExistFloderAndUpdate(const bchar*floder, bsize id, BearStringPath&path);
		bool ExistFileAndUpdate(const bchar*floder, const bchar*file, BearStringPath&path);
		bool ExistFile(const bchar*floder, const bchar*file);
		bool ExistFileAndUpdate(const bchar*floder, const bchar*file, const bchar*e, BearStringPath&path);
		bool ExistFile(const bchar*floder, const bchar*file, const bchar*e);

		void CreatePath(const bchar*floder, bsize id);

		bool LoadFromFile(const bchar*file,BearEncoding::Encoding type);
		void LoadFromStream(const BearInputStream&file, BearEncoding::Encoding type);
		void LoadFromBuffer(const BearBufferedReader&file, BearEncoding::Encoding type);

		void ReadConfig(const bchar*path, const bchar*file, const bchar*e, BearINI&ini, BearEncoding::Encoding coding,BearIncluder*includer=&GIncluderDefault);
		void ReadConfig(const bchar*path, const bchar*file, BearINI&ini, BearEncoding::Encoding coding, BearIncluder*includer = &GIncluderDefault);

		void WriteConfig(const bchar*path, const bchar*file, const bchar*e, bsize id, const BearINI&ini, BearEncoding::Encoding coding);
		void WriteConfig(const bchar*path, const bchar*file, bsize id,const BearINI&ini, BearEncoding::Encoding coding);

		BearStreamRef<BearInputStream> Read(const bchar*path, const bchar*file, const bchar*e);
		BearStreamRef<BearInputStream> Read(const bchar*path, const bchar*file);

		BearStreamRef<BearOutputStream> Write(const bchar*path, const bchar*file, bsize id);
		BearStreamRef<BearOutputStream> Write(const bchar*path, const bchar*file, const bchar*e, bsize id);

		bool Delete(const bchar*path, const bchar*file);
		bool Delete(const bchar*path, const bchar*file, const bchar*e);

		void GetFiles(BearVector<BearString>&files, const bchar*path, const bchar*e);

		void Clear();

		bsize CountPath(const bchar*Path);
		bool ExistPath(const bchar*path);
		void AppendPath(const bchar*name, const bchar*path, const bchar*parent_path, int32 priority);
		void SubPath(const bchar*name);
	private:
		void decoder(BearINI&ini);
		void update(const bchar*name);
		BearMap< BearStringConteniar, BearVector<BearString>> m_paths;
		struct SourcePath
		{
			BearStringPath parent;
			BearStringPath path;
			int32 priority;
			bool operator<(const SourcePath&right)const { return priority > right.priority; }
		};
		void decoderPath(SourcePath&path, BearString&string);
		BearMap< BearStringConteniar, BearVector<SourcePath>> m_source_paths;

	};
	BEARTOOL_API extern BearFileSystem*FS;
}