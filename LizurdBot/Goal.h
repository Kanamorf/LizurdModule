#pragma once
#include "Base.h"
#include "Defines.h"
#include <BWAPI.h>

namespace Lizurd
{
	class Order;
	class Goal
	{
	public:
		Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost);
		Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio);
		Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio, int total);
		virtual ~Goal(void);
		virtual Order *CreateOrder(const BWAPI::Unit executingUnit) const =0;
		BWAPI::UnitType GetExecutingUnitType() const { return _unitType; }
		BWAPI::UnitType GetGoalType() const;
		GoalState GetState() const;
		float GetRatio() const { return _ratio; }
		ResourceValue GetCost() const { return _cost; }
		void DecrementTotal() { --_total; }
		bool IsComplete() const { return _total == 0; }
		protected:
		BWAPI::UnitType _goalType;
		GoalState _goalState;
		float _ratio;
		int _total;
		BWAPI::UnitType _unitType;
		ResourceValue _cost;
	};
}