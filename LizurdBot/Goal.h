#pragma once
#include "Base.h"
#include "Defines.h"
#include <BWAPI.h>

namespace Lizurd
{
	class Goal
	{
	public:
		Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost);
		Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio);
		Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio, int total);
		virtual ~Goal(void);
		BWAPI::UnitType GetExecutingUnitType() const { return _unitType; }
		BWAPI::UnitType GetGoalType() const;
		GoalState GetState() const;
		float GetRatio() const { return _ratio; }
		ResourceValue GetCost() const { return _cost; }
	private:
		BWAPI::UnitType _goalType;
		GoalState _goalState;
		float _ratio;
		int _total;
		BWAPI::UnitType _unitType;
		ResourceValue _cost;
	};
}