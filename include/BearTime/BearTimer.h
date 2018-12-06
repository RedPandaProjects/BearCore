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
			m_timer= GetCurrentTime();
		}
		inline void restart()
		{
			if (!m_pause)
			m_timer = GetCurrentTime();
		}
		inline BearTime get_elapsed_time() const
		{
			if (m_pause)return m_pause_time;
			return  (GetCurrentTime() - m_timer)*m_factor;
		}
		inline void pause(bool paused) 
		{
			if (paused)pause(); else play();
		}
		inline void pause() 
		{
			m_pause = true;
			m_pause_time = (GetCurrentTime() - m_timer);
		}
		inline void play() 
		{
			if (!m_pause)return;
			m_timer = GetCurrentTime() - m_pause_time;
			m_pause = false;

		}
		inline bool paused()const { return m_pause; }
		inline void set_time_factor(double factor) { m_factor = factor; }
		inline double get_time_factor()const { return m_factor; }
	private:
		BearTime GetCurrentTime() const ;
		BearTime m_timer;
		bool m_pause;
		BearTime m_pause_time;
		double m_factor;
	};
}