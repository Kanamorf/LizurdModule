#include "ConstructionGoal.h"
#include "ConstructionOrder.h"
#include "Logger.h"
#include "BuildingPlacer.h"
#include "Gateway.h"
#include "RaceDescriptor.h"

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
	BWAPI::TilePosition position = BWAPI::TilePositions::None;
	if(_goalType == Gateway::GetInstance().GetRaceDescriptor().GetGasCollectorType())
	{
		BWAPI::Unit unit = executingUnit->getClosestUnit(BWAPI::Filter::IsRefinery);
		position = unit->getTilePosition();
	}
	else
		position = BuildingPlacer::GetInstance().getBuildLocationNear(executingUnit->getTilePosition(), _goalType);
	ConstructionOrder *order = new ConstructionOrder("ConstructionOrder", executingUnit, TaskPriority::Medium );
	order->SetResultUnit(_goalType);
	order->SetCost(_cost);
	order->SetTilePosition(position);
	return order;
}