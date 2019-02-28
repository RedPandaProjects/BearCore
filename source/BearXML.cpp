﻿#include "BearCore.hpp"
#include "tinyxml.h"
using namespace BearCore;
BearXML::BearXML():m_Doc(NULL)
{
}


BearCore::BearXML::~BearXML()
{
	Clear();
}

bool BearCore::BearXML::LoadFromFile(const bchar * file, BearString&value_error, BearString&out_error)
{
	Clear();
	m_Doc = bear_new< TiXmlDocument>();
	TiXmlDocument*m_doc = static_cast<TiXmlDocument*>(m_Doc);
	if (!m_doc->LoadFile(*BearEncoding::ToANSI(file)))
	{
		Clear();
		return false;
	}
	if (m_doc->Error())
	{
#ifdef UNICODE
		value_error.assign(*BearEncoding::ToUTF16(m_doc->Value()));
		out_error.assign(*BearEncoding::ToUTF16(m_doc->ErrorDesc()));
#elif UTF_8
			value_error.assign(*BearEncoding::ToUTF8(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF8(m_doc->ErrorDesc()));
#else
		value_error.assign(m_doc->Value());
		out_error.assign(m_doc->ErrorDesc());
#endif
		Clear();
		return false;
	}
	return true;
}

bool BearCore::BearXML::LoadFromStream(const BearInputStream & file, BearEncoding::Encoding tp, BearString&value_error, BearString&out_error)
{
	return LoadFromBuffrer(BearMemoryStream(file), tp, value_error, out_error);
}

bool BearCore::BearXML::LoadFromBuffrer(const BearBufferedReader & buffer, BearEncoding::Encoding tp, BearString&value_error, BearString&out_error)
{
	Clear();
	m_Doc = new TiXmlDocument;
	TiXmlDocument*m_doc = static_cast<TiXmlDocument*>(m_Doc);

	if (tp == BearEncoding::ANSI)
	{
		auto ptr = BearEncoding::ToUTF8((const bchar8*)buffer.Begin(), (const bchar8*)buffer.End());
		m_doc->Parse((char*)*ptr, 0, TIXML_ENCODING_UTF8);
		if (m_doc->Error())
		{
#ifdef UNICODE
			value_error.assign(*BearEncoding::ToUTF16(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF16(m_doc->ErrorDesc()));
#elif UTF_8
			value_error.assign(*BearEncoding::ToUTF8(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF8(m_doc->ErrorDesc()));
#else
			value_error.assign(m_doc->Value());
			out_error.assign(m_doc->ErrorDesc());
#endif
			Clear();
			return false;
		}
	}
	else if (tp == BearEncoding::UTF16)
	{
		auto ptr = BearEncoding::ToUTF8((const bchar16*)buffer.Begin(), (const bchar16*)buffer.End());
		m_doc->Parse((char*)*ptr, 0, TIXML_ENCODING_UTF8);
		if (m_doc->Error())
		{
#ifdef UNICODE
			value_error.assign(*BearEncoding::ToUTF16(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF16(m_doc->ErrorDesc()));
#elif UTF_8
			value_error.assign(*BearEncoding::ToUTF8(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF8(m_doc->ErrorDesc()));
#else
			value_error.assign(m_doc->Value());
			out_error.assign(m_doc->ErrorDesc());
#endif
			Clear();
			return false;
		}
	}
	else 
	{
		auto ptr = BearEncoding::ToUTF8((const bchar_utf8*)buffer.Begin(), (const bchar_utf8*)buffer.End());
		m_doc->Parse((char*)*ptr, 0, TIXML_ENCODING_UTF8);
		if (m_doc->Error())
		{
#ifdef UNICODE
			value_error.assign(*BearEncoding::ToUTF16(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF16(m_doc->ErrorDesc()));
#elif UTF_8
			value_error.assign(*BearEncoding::ToUTF8(m_doc->Value()));
			out_error.assign(*BearEncoding::ToUTF8(m_doc->ErrorDesc()));
#else
			value_error.assign(m_doc->Value());
			out_error.assign(m_doc->ErrorDesc());
#endif
			Clear();
			return false;
		}
	}
	return true;
}


void BearXML::Clear()
{
	TiXmlDocument*m_doc = static_cast<TiXmlDocument*>(m_Doc);
	if (m_doc)
	{
		m_doc->Clear();
		bear_delete(m_doc);
		m_Doc = 0;
	}
}

BearString BearXML::Get(BearXmlNode node, const  bchar* default_str_val)
{
	if (!m_Doc)
		return (default_str_val);
	if(((TiXmlElement*)node)->GetText()[0])
#ifdef UNICODE
		return *BearEncoding::ToUTF16(((TiXmlElement*)node)->GetText());
#elif UTF_8
			return *BearEncoding::ToUTF8(((TiXmlElement*)node)->GetText());
#else
	return ((TiXmlElement*)node)->GetText();
#endif
	else return (default_str_val);
}

BearString BearCore::BearXML::GetAtribute(BearXmlNode node, const  char* Atribute, const  bchar* default_str_val)
{
	if (!m_Doc)
		return (default_str_val);

	if  (((TiXmlElement*)node)->Attribute(Atribute)!=NULL)
		if (((TiXmlElement*)node)->Attribute(Atribute)[0])
#ifdef UNICODE
			return *BearEncoding::ToUTF16(((TiXmlElement*)node)->Attribute(Atribute));
#elif UTF_8
			return *BearEncoding::ToUTF8(((TiXmlElement*)node)->Attribute(Atribute));
#else
			return ((TiXmlElement*)node)->Attribute(Atribute);
#endif
		else return (default_str_val);
	else return (default_str_val);
}
BearXML::BearXmlNode BearXML::GetNode(const char * name)
{
	if (!m_Doc)
		return NULL;
	TiXmlDocument*m_doc = static_cast<TiXmlDocument*>(m_Doc);
	return m_doc->FirstChildElement(name);
}

BearXML::BearXmlNode BearXML::GetNode(BearXmlNode node, const char * name)
{
	if (!m_Doc)
		return NULL;
	return ((TiXmlElement*)node)->FirstChildElement(name);
}

BearXML::BearXmlNode BearCore::BearXML::NextNode(BearXmlNode node, const char * name)
{
	if (!m_Doc)
		return NULL;
	return ((TiXmlElement*)node)->NextSiblingElement(name);
}

