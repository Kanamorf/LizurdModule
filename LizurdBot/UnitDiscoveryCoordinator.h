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
		virtual Result UpdateInternal(int frameNo) override;
		virtual Result AfterUpdateInternal() override;
		virtual void DrawDebugInfo() override;

	private:
		Result RegisterOwnUnit(Notification &notification);
		Result RegisterEnemyUnit(Notification &notification);
		Result RegisterVespeneGeyser(Notification &notification);
		Result MorphUnit(Notification &notification);
		Result CreateNewBase(BWAPI::Unit unit);
		Result DeRegisterUnit(Notification &notification);
		Base* FindClosestFriendlyBase(const BWAPI::Unit unit) const;
		BWAPI::Unit FindIdleUnit(Notification &notification);

	private:
		BaseVector _bases;
		std::vector<BWAPI::Unit> _orphanedUnits;
		std::vector<BWAPI::Unit> _localBuildings;
		BWAPI::Unitset _enemyUnits;
		std::vector<BWAPI::Unit> _vespeneGas;
	};

}