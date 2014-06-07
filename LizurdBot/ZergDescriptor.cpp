#include "ZergDescriptor.h"
#include "ZergHatchery.h"
#include "Base.h"
#include "Logger.h"
#include "Strategy.h"

using namespace Lizurd;

ZergDescriptor::ZergDescriptor(void)
{
}


ZergDescriptor::~ZergDescriptor(void)
{
}

Base* ZergDescriptor::CreateBaseFromCommandCentre(BWAPI::Unit unit) 
{
	Logger::GetInstance().Log("ZergDescriptor", "CreateBaseFromCommandCentre");
	Base *pBase = new Base();
	ZergHatchery *pHhatchery = new ZergHatchery(unit, *pBase);
	pBase->SetCommandCentre(pHhatchery);
	return pBase;
}

Strategy* Lizurd::ZergDescriptor::GetDefaultStrategy() const
{
	Logger::GetInstance().Log("ZergDescriptor", "GetDefaultStrategy");
	Strategy* strategy = new Strategy();
	strategy->SetName(DefaultStrategy);
	strategy->AddOrUpdate(StrategyType::BuildingStrategy, new Goal(BWAPI::UnitTypes::Zerg_Drone, BWAPI::UnitTypes::Zerg_Spawning_Pool, GoalState::Replace, ResourceValue(200,0,0)));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, new Goal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Drone, GoalState::Replace, ResourceValue(50, 0, 2), 1.0, 20));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, new Goal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Zergling, GoalState::Extend, ResourceValue(50, 0, 2), 1.0));
	return strategy;
}

Goal* Lizurd::ZergDescriptor::GetSupplyGoal() const 
{
	return new Goal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Overlord, GoalState::Extend, ResourceValue(100, 0, 0));
}
