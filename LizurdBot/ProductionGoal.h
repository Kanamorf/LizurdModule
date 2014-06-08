#pragma once
#include "Goal.h"

namespace Lizurd
{
	class ProductionGoal :
		public Goal
	{
	public:
		ProductionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost);
		ProductionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio);
		ProductionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio, int total);
		~ProductionGoal(void);

		virtual Order *CreateOrder(const BWAPI::Unit executingUnit) const override;
	};

}