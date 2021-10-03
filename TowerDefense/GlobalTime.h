#pragma once
#include <SFML/System/Clock.hpp>

namespace td
{
	class GlobalTime
	{
	public:
		static GlobalTime& Instance()
		{
			static GlobalTime m_instance; // Static here for instantiation on first use and well-defined destruction
			return m_instance;
		}

		static void OnFrameBegin()
		{
			Instance().m_timeAtBeginningOfFrame = Instance().m_systemClock.restart();
		}

		static float DeltaTime()
		{
			return Instance().m_timeAtBeginningOfFrame.asSeconds();
		}

		// Explicit deletion of special member functions to satisfy the singleton pattern - only one instance possible
		GlobalTime(const GlobalTime& globalTime) = delete;
		void operator=(const GlobalTime& globalTime) = delete;

		GlobalTime(GlobalTime&& globalTime) = delete;
		void operator=(GlobalTime&& globalTime) = delete;

		~GlobalTime() = default;
	private:

		sf::Clock m_systemClock;
		sf::Time m_timeAtBeginningOfFrame;

		GlobalTime() = default;
	};
}