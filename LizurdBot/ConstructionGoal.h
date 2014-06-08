#pragma once
#include "Goal.h"

namespace Lizurd
{
	class ConstructionGoal :
		public Goal
	{
	public:
		ConstructionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost);
		ConstructionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio);
		ConstructionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio, int total);
		~ConstructionGoal(void);

		virtual Order *CreateOrder(const BWAPI::Unit executingUnit) const override;
	};
}