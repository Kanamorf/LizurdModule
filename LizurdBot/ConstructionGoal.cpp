#include "ConstructionGoal.h"
#include "Logger.h"

using namespace Lizurd;

ConstructionGoal::ConstructionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost) :
	Goal(unit, type, state, cost)
{
}
ConstructionGoal::ConstructionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio):
	Goal(unit, type, state, cost, ratio)
{
}
ConstructionGoal::ConstructionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio, int total):
	Goal(unit, type, state, cost, ratio, total)
{
}


ConstructionGoal::~ConstructionGoal(void)
{
}

Order * ConstructionGoal::CreateOrder(const BWAPI::Unit executingUnit) const 
{
	Order *order = nullptr;
	Logger::GetInstance().Log("ConstructionGoal", "CreateOrder. Code not implemented yet.");
	return order;
}