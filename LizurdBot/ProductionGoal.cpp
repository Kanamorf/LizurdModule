#include "ProductionGoal.h"
#include "ProductionOrder.h"

using namespace Lizurd;

ProductionGoal::ProductionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost) :
	Goal(unit, type, state, cost)
{
}
ProductionGoal::ProductionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio):
	Goal(unit, type, state, cost, ratio)
{
}
ProductionGoal::ProductionGoal(BWAPI::UnitType unit, BWAPI::UnitType type, GoalState state, ResourceValue cost, float ratio, int total):
	Goal(unit, type, state, cost, ratio, total)
{
}


ProductionGoal::~ProductionGoal(void)
{
}

Order * ProductionGoal::CreateOrder(const BWAPI::Unit executingUnit) const 
{
	ProductionOrder *order = new ProductionOrder("ProductionOrder", executingUnit, TaskPriority::Medium );
	order->SetResultUnit(_goalType);
	order->SetCost(_cost);
	return order;
}
