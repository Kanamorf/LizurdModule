#pragma once
#include "Coordinator.h"


namespace Lizurd
{
	class Base;
	typedef std::vector<Base *> BaseVector;

	class UnitDiscoveryCoordinator : public Coordinator
	{
	public:
		UnitDiscoveryCoordinator(Gateway &gateway);
		~UnitDiscoveryCoordinator(void);


		virtual Result ProcessNotificationInternal(Notification &notification) override;
		virtual Result UpdateInternal() override;
		virtual Result AfterUpdateInternal() override;
		virtual void DrawDebugInfo() override;

	private:
		void RegisterUnit(Notification &notification);
		void CreateNewBase(BWAPI::Unit unit);
		void DeRegisterUnit(Notification &notification);
		Base* FindClosestFriendlyBase(const BWAPI::Unit unit) const;
		BWAPI::Unit FindIdleUnit(Notification &notification);

	private:
		BaseVector _bases;
		std::vector<BWAPI::Unit> _orphanedUnits;
		std::vector<BWAPI::Unit> _localBuildings;
	};

}