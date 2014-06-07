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
		virtual Result UpdateInternal() override;
		virtual Result AfterUpdateInternal() override;

	private:
		void LoadDefaultStrategy();
		Strategy *_strategy;
	};

}