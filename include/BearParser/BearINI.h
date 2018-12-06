#pragma once
namespace BearCore
{
	class BEARTOOL_API BearINI
	{
	public:
		BearINI();
		~BearINI();

		bool LoadFromFile(const bchar*name_ini, BearEncoding::Encoding typetext,BearIncluder*includer = &GIncluderDefault);
		void LoadFromStream(const BearInputStream&stream,  BearEncoding::Encoding typetext, BearIncluder*includer = &GIncluderDefault);
		void LoadFromBuffer(const BearBufferedReader&stream, BearEncoding::Encoding typetext, BearIncluder*includer = &GIncluderDefault);
		bool SaveToFile(const bchar*name_ini, BearEncoding::Encoding typetext)const;

		BearINI(const BearINI&right);
		BearINI(BearINI&&right);
		void Swap(BearINI&right);
		void Copy(const BearINI&right);
		BearINI&operator=(const BearINI&right);
		BearINI&operator=(BearINI&&right);
		void Clear();
		
		struct section
		{
			BearString parent;
			BearMap<BearStringConteniar, BearVector<BearString>> keys;
		};
		BearMap<BearStringConteniar, section> sections;

		BearVector<BearString>&Key(const bchar*section, const bchar*key, BearString&&default);
		BearVector<BearString>&Key(const bchar*section, const bchar*key, const BearString&default);
		const BearVector<BearString>&Key(const bchar*section, const bchar*key)const;
		BearVector<BearString>&Key(const bchar*section, const bchar*key);
		section&Section(const bchar*section);

		bool Exist(const bchar*section,const bchar*key)const;
		bool Exist(const bchar*section)const;
	private:
		void decoder(const BearBufferedReader& base,  BearEncoding::Encoding typetext, BearIncluder*includer);
		void coder(BearOutputStream& base, BearEncoding::Encoding typetext) const;

	};
}