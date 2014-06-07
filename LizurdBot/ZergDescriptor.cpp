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
	Strategy* strategy = new Strategy();
	strategy->SetName(DefaultStrategy);
	strategy->AddOrUpdate(StrategyType::BuildingStrategy, GoalMapPair(BWAPI::UnitTypes::Zerg_Drone, 
		new Goal(GoalType::BuildSpawningPool, GoalState::Replace)));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, GoalMapPair(BWAPI::UnitTypes::Zerg_Larva, 
		new Goal(GoalType::TrainWorker, GoalState::Replace, 1.0, 20)));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, GoalMapPair(BWAPI::UnitTypes::Zerg_Larva, 
		new Goal(GoalType::TrainZergling, GoalState::Extend, 1)));
	return strategy;
}

GoalMapPair Lizurd::ZergDescriptor::GetSupplyGoal() const 
{
	return GoalMapPair(BWAPI::UnitTypes::Zerg_Larva, new Goal(GoalType::TrainOverlord, GoalState::Extend));
}
