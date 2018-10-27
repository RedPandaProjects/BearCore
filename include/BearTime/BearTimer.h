#pragma once
namespace BearCore
{
	class BEARTOOL_API  BearTimer
	{
	public:
		BearTimer()
		{
			m_factor = 1.f;
			m_pause = false;
			m_timer= getCurrentTime();
		}
		inline void restart()
		{
			if (!m_pause)
			m_timer = getCurrentTime();
		}
		inline BearTime getElapsedTime() const
		{
			if (m_pause)return m_pause_time;
			return  (getCurrentTime() - m_timer)*m_factor;
		}
		inline void pause(bool paused) 
		{
			if (paused)pause(); else play();
		}
		inline void pause() 
		{
			m_pause = true;
			m_pause_time = (getCurrentTime() - m_timer);
		}
		inline void play() 
		{
			if (!m_pause)return;
			m_timer = getCurrentTime() - m_pause_time;
			m_pause = false;

		}
		inline bool paused()const { return m_pause; }
		inline void setTimeFactor(double factor) { m_factor = factor; }
		inline double getTimeFactor()const { return m_factor; }
	private:
		BearTime getCurrentTime() const ;
		BearTime m_timer;
		bool m_pause;
		BearTime m_pause_time;
		double m_factor;
	};
}