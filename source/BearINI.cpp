#include "BearCore.hpp"

BearCore::BearINI::BearINI()
{
}

BearCore::BearINI::~BearINI()
{
	Clear();
}

bool BearCore::BearINI::LoadFromFile(const bchar * name_ini, BearEncoding::Encoding typetext, BearIncluder*icluder)
{
	BearCore::BearFileStream stream;
	if (!stream.Open(name_ini))
		return false;
	LoadFromStream(stream, typetext, icluder);
	return true;
}

void BearCore::BearINI::LoadFromStream(const BearInputStream & stream, BearEncoding::Encoding typetext, BearIncluder*icluder)
{
	BearMemoryStream memory(stream);
	LoadFromBuffer(memory, typetext, icluder);
}

void BearCore::BearINI::LoadFromBuffer(const BearBufferedReader & stream, BearEncoding::Encoding typetext, BearIncluder*icluder )
{
	decoder(stream, typetext, icluder);
}

bool BearCore::BearINI::SaveToFile(const bchar * name_ini, BearEncoding::Encoding typetext) const
{
	BearCore::BearFileStream stream;
	if (!stream.Open(name_ini,stream.M_Write))
		return false;
	coder(stream, typetext);
	return true;
}


BearCore::BearINI::BearINI(const BearINI & right)
{
	Copy(right);
}

BearCore::BearINI::BearINI(BearINI && right)
{
	Swap(right);
}

void BearCore::BearINI::Swap(BearINI & right)
{
	sections.swap(right.sections);
}

void BearCore::BearINI::Copy(const BearINI & right)
{
	sections.copy(right.sections);
}

BearCore::BearINI & BearCore::BearINI::operator=(const BearINI & right)
{
	Copy(right);
	return *this;
}

BearCore::BearINI & BearCore::BearINI::operator=(BearINI && right)
{
	Swap(right);
	return *this;
}

void BearCore::BearINI::Clear()
{
	sections.clear();
}

void BearCore::BearINI::decoder(const BearBufferedReader & base, BearEncoding::Encoding typetext, BearIncluder*includer)
{
	BearString str;
	auto current_section = sections.end();
	while (!base.Eof())
	{
		
		str.clear_no_free();
		base.ReadStringToLine(str, typetext);
		str.seek(0);
		str.sub_space_in_begin();
		if (str.to_char(TEXT(';')))
		{
			str--;
			if (**str != TEXT('\\'))
			{
				str++;
				**str = 0;
			}
		}
		str.seek(0);
		str.sub_space_in_begin();
		if (str.exist_possition(0, TEXT("#include")))
		{
			str.seek(str.tell() + 9);
			str.sub_space_in_begin();
			BEAR_FATALERROR(**str==TEXT('"'), TEXT("Некоретный импорт [%s]"), **str);
			str.sub_space_in_end();
			BEAR_FATALERROR((*str)[str.size()-1] == TEXT('"'), TEXT("Некоретный импорт [%s]"), **str);
			(*str)[str.size() - 1] = 0;
		
			decoder(**includer->OpenAsBuffer(*str), typetext, includer);

		}
		if (!**str)
			continue;
		if (str[0] == TEXT('['))
		{


			str++;
			bchar*data = *str;
			BEAR_FATALERROR(str.to_char(TEXT(']')), TEXT("Нет конца в [%s]"), data);
			str.sub_space_in_begin();
			bchar *sec_name_end = *str; str.to_char(TEXT(':'));
			str.sub_space_in_begin();
			str.sub_space_in_end();
			bchar *parent_name = *str;
			*sec_name_end = 0;

			auto parent = sections.end();
			if (parent_name[0])
			{
				parent_name++;
				section sec;
				sec.parent = parent_name;
				//BEAR_FATALERROR(parent != sections.end(), TEXT("Не найден родитель [%s]"), parent_name);
				sections.insert(data, sec);
			}
			else
			{
				sections.insert(data);
			}
			current_section = sections.find(BearStringConteniar(data, false));
			continue;

		}
		else
		{
			if (!*str)continue;
			BEAR_FATALERROR(current_section != sections.end(), TEXT("Некоректный ini файл"));
			bchar*data = *str;
			str.to_char(TEXT('='));
			bchar*key_data = TEXT("");
			if (**str) {
				**str = 0;
				str++;
				str.sub_space_in_begin();
				str.sub_space_in_end();
				if (**str)
					key_data = *str;

			}
			str.seek(0);
			str.sub_space_in_begin();
			str.sub_space_in_end();
			data = *str;
			auto item =	current_section->second.keys.find(BearStringConteniar(data, false));
			if (item == current_section->second.keys.end())
			{
				current_section->second.keys.insert(data);
				item = current_section->second.keys.find(BearStringConteniar(data, false));
			}
			item->second.push_back(key_data);
		}
	}
}

void BearCore::BearINI::coder(BearOutputStream & base, BearEncoding::Encoding typetext) const
{
	auto begins = sections.begin();
	auto ends = sections.end();
	BearString str;
	while (begins != ends)
	{
		str.clear_no_free();
		str.append_printf(TEXT("[%s]"), *begins->first);
		if(begins->second.parent.size())
			str.append_printf(TEXT(":%s"), *begins->second.parent);

		base.WriteStringAndNewLine(str, typetext);
		auto begink = begins->second.keys.begin();
		auto endk = begins->second.keys.end();
		while (begink != endk)
		{
			auto begind=begink->second.begin();
			auto endd = begink->second.end();
			while (begind != endd)
			{
				str.clear_no_free();
				if (begind->size())
				{
					str.append_printf(TEXT("%s=%s"), *begink->first, **begind);
					base.WriteStringAndNewLine(str, typetext);
				}
				else
				{
					str.append_printf(TEXT("%s"), *begink->first);
					base.WriteStringAndNewLine(str, typetext);
				}
				begind++;
			}
			begink++;
		}
		begins++;
	}

}

BearCore::BearVector<BearCore::BearString>& BearCore::BearINI::Key(const bchar * section, const bchar * key, BearString && default)
{
	auto sec = sections.find(BearStringConteniar(section, false));
	while (sec != sections.end())
	{
		auto k = sec->second.keys.find(BearStringConteniar(key, false));
		if (k == sec->second.keys.end())
		{
			if (sec->second.parent.size())
				sec = sections.find(BearStringConteniar(*sec->second.parent, false));
			else
				break;
		}
		else
		{
			return k->second;
		}
	}
	sec = sections.find(BearStringConteniar(section, false));
	if (sec == sections.end())
	{
		sections.insert(section);
		sec = sections.find(BearStringConteniar(section, false));
	}
	sec->second.keys.insert(key);
	auto k = sec->second.keys.find(BearStringConteniar(key, false));
	k->second.push_back(section);
	return 	k->second;
}

BearCore::BearVector<BearCore::BearString>& BearCore::BearINI::Key(const bchar * section, const bchar * key, const BearString & default)
{
	auto sec = sections.find(BearStringConteniar(section, false));
	while (sec == sections.end())
	{
		auto k = sec->second.keys.find(BearStringConteniar(key, false));
		if (k == sec->second.keys.end())
		{
			if (sec->second.parent.size())
				sec = sections.find(BearStringConteniar(*sec->second.parent, false));
			else
				break;
		}
		else
		{
			return k->second;
		}
	}
	sec = sections.find(BearStringConteniar(section, false));
	if (sec == sections.end())
	{
		sections.insert(section);
		sec = sections.find(BearStringConteniar(section, false));
	}
	sec->second.keys.insert(key);
	auto k = sec->second.keys.find(BearStringConteniar(key, false));
	k->second.push_back(section);
	return 	k->second;
}

const BearCore::BearVector<BearCore::BearString>& BearCore::BearINI::Key(const bchar * section, const bchar * key) const
{
	auto sec = sections.find(BearStringConteniar(section, false));
	BEAR_FATALERROR(sec != sections.end(), TEXT("Не найдена секция [%s]"), section);
	auto k = sec->second.keys.find(BearStringConteniar(key, false));
	BEAR_FATALERROR(k != sec->second.keys.end(), TEXT("Не найдена ключь [%s] в секции [%s]"), key, section);
	return 	k->second;
}

BearCore::BearVector< BearCore::BearString>& BearCore::BearINI::Key(const bchar * section, const bchar * key)
{
	auto sec = sections.find(BearStringConteniar(section, false));
	BEAR_FATALERROR(sec != sections.end(), TEXT("Не найдена секция [%s]"), section);
	auto k = sec->second.keys.find(BearStringConteniar(key, false));
	BEAR_FATALERROR(k != sec->second.keys.end(), TEXT("Не найдена ключь [%s] в секции [%s]"), key, section);
	return 	k->second;
}

BearCore::BearINI::section & BearCore::BearINI::Section(const bchar * section)
{
	auto sec = sections.find(BearStringConteniar(section, false));
	if (sec == sections.end())
	{
		sections.insert(section);
		sec = sections.find(BearStringConteniar(section, false));
	}
	return sec->second;
}

bool BearCore::BearINI::Exist(const bchar * section, const bchar * key) const
{
	auto sec = sections.find(BearStringConteniar(section, false));
	if (sec == sections.end())
		return false;
	auto k = sec->second.keys.find(BearStringConteniar(key, false));
	if (k == sec->second.keys.end())
		return false;
	return true;
}

bool BearCore::BearINI::Exist(const bchar * section) const
{
	auto sec = sections.find(BearStringConteniar(section, false));
	return (sec != sections.end());
}
