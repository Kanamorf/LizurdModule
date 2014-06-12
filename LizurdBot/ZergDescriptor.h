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
		virtual BWAPI::UnitType GetSupplyType() const override { return BWAPI::UnitTypes::Zerg_Overlord; }
		virtual BWAPI::UnitType GetWorkerType() const override  { return BWAPI::UnitTypes::Zerg_Drone; }
		virtual BWAPI::UnitType GetGasCollectorType() const override { return BWAPI::UnitTypes::Zerg_Extractor; }
		virtual void CreateBaseFromCommandCentre(BWAPI::Unit unit, Base *base) override;
		virtual Strategy* GetDefaultStrategy() const override;
		virtual Goal* GetSupplyGoal() const override;
		virtual Building* ConvertUnitToBuilding(BWAPI::Unit unit) const override;
		virtual float GetBuildableUnits(const std::map<BWAPI::UnitType, int> &buildings, std::map<BWAPI::UnitType, float> &units) const override;
		virtual Goal* GetGoal(const BWAPI::UnitType &type) override;
	};

}