#pragma once
#include "Coordinator.h"

namespace Lizurd
{
	class ConstructionCoordinator :
		public Coordinator
	{
	public:
		ConstructionCoordinator(Gateway &gateway);
		~ConstructionCoordinator(void);

		virtual Result ProcessNotificationInternal(Notification &notification) override;
		virtual Result UpdateInternal() override;
		virtual Result AfterUpdateInternal() override;

	private:
		Goal* _currentGoal;
	};

}