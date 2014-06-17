#include "ConstructionGoal.h"
#include "ConstructionOrder.h"
#include "Logger.h"
#include "BuildingPlacer.h"
#include "Gateway.h"
#include "RaceDescriptor.h"
#include "BWAPI.h"

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
		BWAPI::Unit found = nullptr;
		BWAPI::Unitset units = executingUnit->getUnitsInRadius(1024);
		for(BWAPI::Unitset::iterator it = units.begin(); it != units.end(); ++it)
		{
			if((*it)->getType() == BWAPI::UnitTypes::Resource_Vespene_Geyser)
			{
				found = *it;
				break;
			}
		}
		if(found != nullptr)
			position = found->getTilePosition();
	}
	else
		position = BuildingPlacer::GetInstance().getBuildLocationNear(executingUnit->getTilePosition(), _goalType);
	ConstructionOrder *order = new ConstructionOrder("ConstructionOrder", executingUnit, TaskPriority::Medium );
	order->SetResultUnit(_goalType);
	order->SetCost(_cost);
	order->SetTilePosition(position);
	return order;
}