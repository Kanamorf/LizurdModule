#pragma once
#include <vector>
#include "BWAPI.h"
#include "Goal.h"

namespace
{
	const std::string DefaultStrategy = "DefaultStrategy";

}

namespace Lizurd
{
	class Base;
	class Strategy;

	class RaceDescriptor
	{
	public:

		RaceDescriptor();
		virtual ~RaceDescriptor(void);
		virtual BWAPI::UnitType GetCommandCenterType() const = 0;
		virtual BWAPI::UnitType GetSupplyType() const = 0;
		virtual void CreateBaseFromCommandCentre(BWAPI::Unit unit, Base *base) = 0;
		virtual BWAPI::UnitType GetWorkerType() const = 0;
		virtual Strategy* GetDefaultStrategy() const = 0;
		virtual Goal* GetSupplyGoal() const =0;
		virtual Building* ConvertUnitToBuilding(BWAPI::Unit unit) const =0;
		virtual float GetBuildableUnits(const std::map<BWAPI::UnitType, int> &buildings, std::map<BWAPI::UnitType, float> &units) const =0;
		virtual Goal* GetGoal(const BWAPI::UnitType &type) =0;

		void AddOrUpdate(GoalQueue& goalMap, const Goal *add) const;
		
		
	};

}