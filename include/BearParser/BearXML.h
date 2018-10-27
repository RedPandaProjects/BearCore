#pragma once
namespace BearCore
{
	class BEARTOOL_API BearXML
	{
	public:
		typedef void* BearXmlNode;
		BearXML();
	
		~BearXML();
		bool loadFromFile(const bchar* file, BearString&value_error, BearString&out_error);
		bool loadFromStream(const BearInputStream& file, BearEncoding::Encoding tp, BearString&value_error, BearString&out_error);
		bool loadFromBuffrer(const BearBufferedReader&buffer, BearEncoding::Encoding tp, BearString&value_error, BearString&out_error);
		void clear();
		BearString  get(BearXmlNode node,const bchar*text=TEXT(""));
		BearString  getAtribute(BearXmlNode node,const char* Atribute, const bchar*text = TEXT(""));
		BearXmlNode getNode(const char* name);
		BearXmlNode getNode(BearXmlNode node, const char* name);
		BearXmlNode nextNode(BearXmlNode node, const char* name);

		BearXML(const BearXML&) = delete;
		BearXML&operator =(const BearXML&) = delete;
	private:
		mutable void*	m_Doc;

	};
};