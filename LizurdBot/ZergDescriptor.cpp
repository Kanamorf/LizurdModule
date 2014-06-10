#include "ZergDescriptor.h"
#include "ZergHatchery.h"
#include "ZergSpawningPool.h"
#include "Base.h"
#include "Logger.h"
#include "Strategy.h"
#include "ProductionGoal.h"
#include "ConstructionGoal.h"

using namespace Lizurd;

ZergDescriptor::ZergDescriptor(void)
{
}


ZergDescriptor::~ZergDescriptor(void)
{
}

void ZergDescriptor::CreateBaseFromCommandCentre(BWAPI::Unit unit, Base *base) 
{
	if(base != nullptr)
	{
		Logger::GetInstance().Log("ZergDescriptor", "CreateBaseFromCommandCentre");
		ZergHatchery *pHhatchery = new ZergHatchery(unit, base);
		Logger::GetInstance().Log("ZergDescriptor", "CreateBaseFromCommandCentre 1");
		base->SetCommandCentre(pHhatchery);
		Logger::GetInstance().Log("ZergDescriptor", "CreateBaseFromCommandCentre 2");
		base->Initialise();
		Logger::GetInstance().Log("ZergDescriptor", "CreateBaseFromCommandCentre 3");
	}
}

Strategy* Lizurd::ZergDescriptor::GetDefaultStrategy() const
{
	Logger::GetInstance().Log("ZergDescriptor", "GetDefaultStrategy");
	Strategy* strategy = new Strategy();
	strategy->SetName(DefaultStrategy);
	strategy->AddOrUpdate(StrategyType::BuildingStrategy, new ConstructionGoal(BWAPI::UnitTypes::Zerg_Drone, BWAPI::UnitTypes::Zerg_Spawning_Pool, GoalState::Replace, ResourceValue(200,0,0)));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Drone, GoalState::Replace, ResourceValue(50, 0, 2), 1.0, 3));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Overlord, GoalState::Extend, ResourceValue(100, 0, 0)));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Drone, GoalState::Extend, ResourceValue(50, 0, 2), 1.0, 3));
	return strategy;
}

Goal* Lizurd::ZergDescriptor::GetSupplyGoal() const 
{
	return new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Overlord, GoalState::Extend, ResourceValue(100, 0, 0));
}

Building* Lizurd::ZergDescriptor::ConvertUnitToBuilding(BWAPI::Unit unit) const 
{
	Building* building = nullptr;
	switch(unit->getType())
	{
	case BWAPI::UnitTypes::Enum::Zerg_Hatchery:
		building = new ZergHatchery(unit);
		break;
	case BWAPI::UnitTypes::Enum::Zerg_Spawning_Pool:
		building = new ZergSpawningPool(unit);
		break;
	default:
		//nothing to do
		break;
	}
	return building;
}

