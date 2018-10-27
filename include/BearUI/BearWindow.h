#pragma once
namespace BearCore
{
	class BEARTOOL_API BearWindow
	{
	public:
		BearWindow();

		~BearWindow();

		void create(const bchar* Title, uint32 width, uint32 height, bool fullscrean);

		bool draw(bool onclosed);

		void setTitle(const bchar*Title);

		void setSize(uint32 width, uint32 height);

		void setFullScreen(bool fs);

		inline const BearString& getTitle() const
		{
			return m_title;
		}

		inline BearVector2<uint32> getSize() const
		{
			return m_size;
		}

		inline bool getFullScreen() const
		{
			return m_bfullscreen;
		}

		bool isActive() const;

		inline void* getRef() const
		{
			return m_ref;
		}

		void close();
	private:
		void*m_ref;
		BearString m_title;
		BearVector2<uint32> m_size;
		bool m_bfullscreen;

	};
}