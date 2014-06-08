#include "Goal.h"

using namespace Lizurd;

Goal::Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost):
	_unitType(unit),
	_goalState(state), 
	_goalType(type), 
	_cost(cost),
	_ratio(1),
	_total(1)
{
}

Goal::Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio):
	_unitType(unit),
	_goalState(state), 
	_goalType(type), 
	_cost(cost),
	_ratio(ratio),
	_total(1)
{

}

Goal::Goal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio, int total):
	_unitType(unit),
	_goalState(state), 
	_goalType(type), 
	_ratio(ratio),
	_cost(cost),
	_total(total)
{
}

Goal::~Goal(void)
{
}

BWAPI::UnitType Goal::GetGoalType() const
{
	return _goalType;
}

GoalState Goal::GetState() const
{
	return _goalState;
}



