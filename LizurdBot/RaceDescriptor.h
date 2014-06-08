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
		virtual Base* CreateBaseFromCommandCentre(BWAPI::Unit unit) = 0;
		virtual BWAPI::UnitType GetWorkerType() const = 0;
		virtual Strategy* GetDefaultStrategy() const = 0;
		virtual Goal* GetSupplyGoal() const =0;
		virtual Building* GetBuildingByType(const BWAPI::UnitType &type) const =0;
		void AddOrUpdate(GoalQueue& goalMap, const Goal *add) const;
		
	};

}