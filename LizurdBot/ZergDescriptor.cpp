#include "ZergDescriptor.h"
#include "ZergHatchery.h"
#include "ZergSpawningPool.h"
#include "ZergExtractor.h"
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
		base->SetCommandCentre(pHhatchery);
		base->Initialise();
	}
}

Strategy* Lizurd::ZergDescriptor::GetDefaultStrategy() const
{
	Logger::GetInstance().Log("ZergDescriptor", "GetDefaultStrategy");
	Strategy* strategy = new Strategy();
	strategy->SetName(DefaultStrategy);
	strategy->AddOrUpdate(StrategyType::BuildingStrategy, new ConstructionGoal(BWAPI::UnitTypes::Zerg_Drone, BWAPI::UnitTypes::Zerg_Spawning_Pool, GoalState::Replace, ResourceValue(200,0,0)));
	strategy->AddOrUpdate(StrategyType::BuildingStrategy, new ConstructionGoal(BWAPI::UnitTypes::Zerg_Drone, BWAPI::UnitTypes::Zerg_Extractor, GoalState::Extend, ResourceValue(50,0,0)));
	strategy->AddOrUpdate(StrategyType::BuildingStrategy, new ConstructionGoal(BWAPI::UnitTypes::Zerg_Drone, BWAPI::UnitTypes::Zerg_Hatchery, GoalState::Extend, ResourceValue(300,0,0)));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Drone, GoalState::Replace, ResourceValue(50, 0, 2), 1.0, 3));
	strategy->AddOrUpdate(StrategyType::UnitStrategy, new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Drone, GoalState::Extend, ResourceValue(50, 0, 2), 1.0, 5));
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
		case BWAPI::UnitTypes::Enum::Zerg_Extractor:
		building = new ZergExtractor(unit);
		break;
	default:
		//nothing to do
		break;
	}
	return building;
}

Goal* ZergDescriptor::GetGoal(const BWAPI::UnitType &type)
{
	Goal *goal = nullptr;
	switch(type)
	{
	case BWAPI::UnitTypes::Enum::Zerg_Drone:
		goal = new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Drone, GoalState::Extend, ResourceValue(50, 0, 2), 1.0);
		break;
	case BWAPI::UnitTypes::Enum::Zerg_Overlord:
		goal = new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Overlord, GoalState::Extend, ResourceValue(100, 0, 0));
		break;
	case BWAPI::UnitTypes::Enum::Zerg_Zergling:
		goal = new ProductionGoal(BWAPI::UnitTypes::Zerg_Larva, BWAPI::UnitTypes::Zerg_Zergling, GoalState::Extend, ResourceValue(50, 0, 2));
		break;
	}
	return goal;
}

/// <summary>
/// Given a set of buildings what units can be built , the float is a weighting for how often that type should be built.
/// This is very much finger in the air guessing at the moment.
///
float ZergDescriptor::GetBuildableUnits(const std::map<BWAPI::UnitType, int> &buildings, std::map<BWAPI::UnitType, float> &units) const 
{
	float total = 0.0f;
	for(std::map<BWAPI::UnitType, int>::const_iterator it = buildings.begin(); it != buildings.end(); ++it)
	{
		switch(it->first)
		{
		case BWAPI::UnitTypes::Enum::Zerg_Hatchery:
			units[BWAPI::UnitTypes::Zerg_Drone] = 1.0f;
			total += 1.0f;
			break;
		case BWAPI::UnitTypes::Enum::Zerg_Spawning_Pool:
			units[BWAPI::UnitTypes::Zerg_Zergling] = 2.6f;
			total += 2.6f;
			break;
		}
	}
	return total;
}

BWAPI::UnitType ZergDescriptor::GetPreMorphType(BWAPI::UnitType type) const
{
	BWAPI::UnitType morphType = BWAPI::UnitTypes::None;
	if(type.isBuilding())
	{
		morphType = BWAPI::UnitTypes::Zerg_Drone;
	}
	else if(type == BWAPI::UnitTypes::Zerg_Egg)
	{
		morphType = BWAPI::UnitTypes::Zerg_Larva;
	}
	else
	{
		morphType = BWAPI::UnitTypes::Zerg_Egg;
	}
	return morphType;
}