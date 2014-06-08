#pragma once
#include "RaceDescriptor.h"

namespace Lizurd
{

	class ZergDescriptor :
		public RaceDescriptor
	{
	public:
		ZergDescriptor(void);
		~ZergDescriptor(void);
		virtual BWAPI::UnitType GetCommandCenterType() const override { return BWAPI::UnitTypes::Zerg_Hatchery; }
		virtual BWAPI::UnitType GetWorkerType() const override  { return BWAPI::UnitTypes::Zerg_Drone; }
		virtual Base* CreateBaseFromCommandCentre(BWAPI::Unit unit) override;
		virtual Strategy* GetDefaultStrategy() const override;
		virtual Goal* GetSupplyGoal() const override;
		virtual Building* GetBuildingByType(const BWAPI::UnitType &type) const override;
	};

}