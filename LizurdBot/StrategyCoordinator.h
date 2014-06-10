#pragma once
#include "Coordinator.h"

namespace Lizurd
{
	class Strategy;

	class StrategyCoordinator :
		public Coordinator
	{
	public:
		StrategyCoordinator(Gateway &gateway);
		~StrategyCoordinator(void);

		virtual Result ProcessNotificationInternal(Notification &notification) override;
		virtual Result UpdateInternal(int frameNo) override;
		virtual Result AfterUpdateInternal() override;
		void RegisterNewUnit(BWAPI::UnitType type);

	private:
		void LoadDefaultStrategy();
		float RandomFloat(float a, float b);
		Strategy *_strategy;
		std::map<BWAPI::UnitType, int> _buildings;
	};

}