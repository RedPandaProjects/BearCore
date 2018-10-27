#include "BearCore.hpp"
#include <assert.h>
#ifdef UNICODE
#define stringLen wcslen
#define stringLower _wcslwr_s
#define stringUpper _wcsupr_s
#define stringFind wcsstr
#define stringToChar wcschr
#else
#define stringlen strlen
#define stringLower _strlwr_s
#define stringUpper _strupr_s
#define stringFind strstr
#define stringToChar strchr
#endif


/*

bsize BearCore::BearStringEditor::GetSize(const bchar8 * text)
{
	return strlen(text);;
}

bsize BearCore::BearStringEditor::GetSize(const bchar16 * text)
{
	return wcslen(text);;
}

void BearCore::BearStringEditor::Contact(BearStringBase & str, bchar text)
{
	Contact(str, &text,1);
}

void BearCore::BearStringEditor::Contact(BearStringBase & str, const bchar * text)
{
	Contact(str, text, GetSize(text));
}

void BearCore::BearStringEditor::Contact(BearStringBase & str, const bchar * text, bsize size)
{
	size++;

	auto&info = str.getInfo();

	bchar*begin = info.data + info.size + info.tell;

	if (size > info.sizeBuffer - info.size - info.tell)
		size = UpdateData(info, size + info.size + info.tell) - info.size - info.tell;
	bear_copy(begin, text, size-1);
	*(begin + size-1) = 0;
	Update(info);
}
void BearCore::BearStringEditor::Set(BearStringBase & str, bsize pos, bchar sim)
{
	Set(str, pos, &sim, 1);
}
void BearCore::BearStringEditor::Set(BearStringBase & str, bsize pos, const bchar * sim)
{
	Set(str, pos, sim, GetSize(sim));
}
void BearCore::BearStringEditor::Set(BearStringBase & str, bsize pos, const bchar * text, bsize size)
{
	auto&info = str.getInfo();
	int8 bSetNull = (int8)str.getInfo().size<pos+size;
	bchar*begin = info.data + info.tell+pos;

	if (info.tell + pos + size + bSetNull> info.sizeBuffer)
		size = UpdateData(info, size + info.tell + pos + bSetNull) - info.tell - pos - bSetNull;
	bear_copy(begin, text, size);
	if(bSetNull)
		*(begin + size) = 0;
	Update(info);
}

void BearCore::BearStringEditor::Append(BearStringBase & str, bsize pos, bchar sim)
{
	Append(str, pos, &sim, 1);
}

void BearCore::BearStringEditor::Append(BearStringBase & str, bsize pos, const bchar * sim)
{
	Append(str, pos,sim, GetSize(sim));
}

void BearCore::BearStringEditor::Append(BearStringBase & str, bsize pos, const bchar * sim, bsize size)
{
	Move(str.getInfo(), pos, size);
	Set(str,pos,sim,size);
}

void BearCore::BearStringEditor::DeleteSpaceInEnd(BearStringBase & str)
{
	auto&info = str.getInfo();
	bchar*begin = info.data+info.tell;
	bchar*end = begin+info.size;

	if (begin != end)
		end--;

	while (begin != end)
	{
		if (*end == TEXT(' ') || *end == TEXT('\t')|| *end == TEXT('\r')|| *end == TEXT('\n'))
		{
			*end = 0; end--;
		}
		else break;
	}
	Update(info);
}

void BearCore::BearStringEditor::DeleteSpaceInBegin(BearStringBase & str)
{
	auto&info = str.getInfo();
	bchar*begin = info.data + info.tell;
	bchar*end = begin + info.size;
	while (begin != end)
	{
		if (*begin == TEXT(' ') || *begin == TEXT('\t') || *begin == TEXT('\r') || *end == TEXT('\n'))
			begin++;
		else 
			break;

	}
	info.tell = begin - info.data;
	Update(info);
}

void BearCore::BearStringEditor::DeleteSpace(BearStringBase & str)
{
	DeleteSpaceInBegin(str);
	DeleteSpaceInEnd(str);
}

void BearCore::BearStringEditor::Substr(BearStringBase & str, bsize pos)
{
	auto&info = str.getInfo();
	Move(info, pos+1, -1);
	Update(info);
}

void BearCore::BearStringEditor::Substr(BearStringBase & str, bsize pos, bsize size)
{
	auto&info = str.getInfo();
	Move(info, pos+size, -static_cast<bint>(size));
	Update(info);
}

void BearCore::BearStringEditor::Substr(BearStringBase & str, const bchar * text)
{
	auto&info = str.getInfo();
	bsize sizeText = GetSize(text);
	bsize pos = Find(str, text, 0);
	while (pos != info.size)
	{
		Substr(str, pos, sizeText);
		pos = Find(str, text, 0);
	}
}

void BearCore::BearStringEditor::SubstrLast(BearStringBase & str)
{
	auto&info = str.getInfo();
	info.data[info.size - 1] = 0;
	Update(info);
}
void BearCore::BearStringEditor::ToLower(BearStringBase & str)
{
	auto&info = str.getInfo();
	stringLower(info.data + info.tell,info.size);
	Update(info);
}

void BearCore::BearStringEditor::ToUpper(BearStringBase & str)
{
	auto&info = str.getInfo();
	stringUpper(info.data + info.tell, info.size);
	Update(info);
}

bsize BearCore::BearStringEditor::Find(BearStringBase & str, const bchar * text, bsize pos)
{
	auto&info = str.getInfo();
	bchar*item=stringFind(str.getInfo().data + info.tell+pos, text);
	if (item == 0)return info.size;
	return item - info.data - pos- info.tell;
}

bsize BearCore::BearStringEditor::FindWithEnd(BearStringBase & str, const bchar * text, bsize pos)
{
	return bsize();
}

void BearCore::BearStringEditor::Replace(BearStringBase & str, bsize pos, bsize size, const bchar * text)
{
	auto&info = str.getInfo();
	bsize sizeText = GetSize(text);
	if (sizeText > size)
	{
		Move(info, pos,static_cast<bint>(sizeText-size));
		Set(str, pos, text);
	}
	else
	{
		Move(info, pos-(sizeText - size), static_cast<bint>(sizeText - size));
		Set(str, pos, text);
	}
	
}

void BearCore::BearStringEditor::Replace(BearStringBase & str, const bchar * old, const bchar * text)
{
	auto&info = str.getInfo();
	bsize sizeText = GetSize(old);
	bsize pos = Find(str, old, 0);
	while (pos != info.size)
	{
		Replace(str, pos, sizeText, text);
		pos = Find(str, old, 0);
	}
}
bool BearCore::BearStringEditor::ToChar(BearStringBase & str, bchar ch)
{
	auto&info = str.getInfo();
	bchar*begin=stringToChar(info.data + info.tell, ch);
	if (begin)
	{
		info.tell = begin - info.data - info.tell;
		Update(info);
		return true;
	}

	return false;
}


void BearCore::BearStringEditor::Move(BearStringBase::BearStringInfo & info, bsize possition, bint move)
{
	BEAR_ASSERT(possition<=info.size);
	bsize size = info.size + info.tell + move +1;
	bool bSetNull = false;
	if (size > info.sizeBuffer)
	{
		size = UpdateData(info, size);
		bSetNull = true;
	}

	bchar*begin = info.data + info.tell + possition;

	bsize sizeMove = size- possition-info.tell-move;
	if (sizeMove)info.size += move;
	bear_move(begin, move, sizeMove);
	if (bSetNull)*(info.data + info.sizeBuffer - 1) = 0;
	
}

bsize BearCore::BearStringEditor::UpdateData(BearStringBase::BearStringInfo & info, bsize new_size)
{
	BEAR_ASSERT(info.dynamic);
	BEAR_ASSERT(info.sizeBuffer<new_size);
	if (info.dynamic)
	{
		info.data = bear_realloc(info.data, new_size);
		info.sizeBuffer = new_size;
		return new_size;
	}
	return info.sizeBuffer;
}

*/