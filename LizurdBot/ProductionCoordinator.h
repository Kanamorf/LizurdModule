#pragma once
#include "coordinator.h"

namespace Lizurd
{
	class ProductionCoordinator :
		public Coordinator
	{
	public:
		ProductionCoordinator(Gateway &gateway);
		~ProductionCoordinator(void);

		virtual Result ProcessNotificationInternal(Notification &notification) override;
		virtual Result UpdateInternal(int frameNo) override;
		virtual Result AfterUpdateInternal() override;

	private:
		Goal* _currentGoal;
		Goal* _savedGoal;
		bool _buildingSupply;
	};

}