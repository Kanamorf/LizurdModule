#pragma once
#include "coordinator.h"

namespace Lizurd
{
	class SquadCoordinator :
		public Coordinator
	{
	public:
		SquadCoordinator(Gateway &gateway);
		~SquadCoordinator(void);

		virtual Result ProcessNotificationInternal(Notification &notification) override;
		virtual Result UpdateInternal(int frameNo) override;
		virtual Result AfterUpdateInternal() override;

		void RegisterUnit(Notification &notification);

	private:
		BWAPI::Unitset _units;
		int _attackcount;
	};

}