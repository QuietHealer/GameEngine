#pragma once
#include <cstdint>

namespace nu
{
	class Time
	{
	public:
		Time();

		void Reset();
		void Tick();

		float GetTime() { return TickToSeconds(m_currentTicks - m_startTicks); }
		float GetDeltaTime() { return TickToSeconds(m_deltaTicks); }

		float TickToSeconds(uint64_t ticks) {return (float)ticks / 1'000'000'000;}

	private:
		uint64_t m_startTicks = 0;
		uint64_t m_currentTicks = 0;
		uint64_t m_frameTicks = 0;
		uint64_t m_deltaTicks = 0;
	};
}
