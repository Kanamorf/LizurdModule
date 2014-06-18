#include "StrategyCoordinator.h"
#include "RaceDescriptor.h"
#include "Strategy.h"
#include <stdlib.h>
#include <time.h>
#include "ProductionGoal.h"
#include <sstream>

using namespace Lizurd;

StrategyCoordinator::StrategyCoordinator(Gateway &gateway) :
	Coordinator(gateway, StrategyCoord)
{
	LoadDefaultStrategy();
	srand(static_cast<unsigned int>(time(NULL)));
}


StrategyCoordinator::~StrategyCoordinator(void)
{
}

Result Lizurd::StrategyCoordinator::UpdateInternal(int frameNo)
{
	if(_strategy->UnitGoalIsEmpty())
	{
		std::map<BWAPI::UnitType, float> units;
		float total = _gateway.GetRaceDescriptor().GetBuildableUnits(_buildings, units);
		float random = RandomFloat(0.0f, total);
		float inc = 0.0f;
		for(std::map<BWAPI::UnitType, float>::iterator it = units.begin(); it != units.end(); ++it)
		{
			// we want 3 times as many workers as we have mineral fields
			// this will need to be modified to count mineral fields we own, not just ones
			// we have found
			float modifier = 1.0f;
			if(it->first == _gateway.GetRaceDescriptor().GetWorkerType())
			{
				//float fields = _units[BWAPI::UnitTypes::Resource_Mineral_Field];
			}
			inc += it->second;
			if(random <= inc)
			{
				Goal* goal = _gateway.GetRaceDescriptor().GetGoal(it->first);
				if(goal != nullptr)
				{
					_strategy->AddOrUpdate(StrategyType::UnitStrategy, goal);
					break;
				}
			}
		}
		
	}
	return Result::Success;
}

Result Lizurd::StrategyCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}

Result Lizurd::StrategyCoordinator::ProcessNotificationInternal(Notification &notification)
{
	Result retVal = Result::Failure;
	if(notification.GetTarget() != Coordinators::StrategyCoordinator && notification.IsRegistered() == false)
	{
		notification.SetIsRegistered();
		BWAPI::UnitType type = notification.GetUnitType();
		// All notifications come via strategy coordinator so we can count stuff
		switch(notification.GetAction().Underlying())
		{
		case Action::RegisterOwnUnit:
			if(type.isBuilding())
				++_buildings[type];
			else
				++_units[type];
			break;
		case Action::DeRegisterUnit :
			if(type.isBuilding())
				--_buildings[type];
			else
				--_units[type];
			break;
		case Action::MorphUnit :
			BWAPI::UnitType preMorph = _gateway.GetRaceDescriptor().GetPreMorphType(type);
			if(preMorph != BWAPI::UnitTypes::None)
			{
				if(preMorph.isBuilding())
					--_buildings[preMorph];
				else
					--_units[preMorph];
				if(type.isBuilding() == false)
					// dont register building yet as it is useless until its built
					//++_buildings[type];
					++_units[type];
			}
			break;
		}
	}
	else
	{
		//This notification was actually for the strategy coordinator
		if(notification.GetAction() == Action::GetNextProductionGoal)
		{
			Goal* goal = _strategy->GetNextUnitGoal();
			if(goal != nullptr)
			{
				notification.SetGoal(goal);
				retVal = Result::Success;
			}
		}
		else if(notification.GetAction() == Action::GetNextConstructionGoal)
		{
			Goal* goal = _strategy->GetNextBuildingGoal();
			if(goal != nullptr)
			{
				notification.SetGoal(goal);
				retVal = Result::Success;
			}
		}
		else if(notification.GetAction() == Action::NewBuildingFinished)
		{
			BWAPI::UnitType type = notification.GetUnitType();
			RegisterNewUnit(type);
			if(type == _gateway.GetRaceDescriptor().GetGasCollectorType())
			{
				Notification newGas(Coordinators::WorkerCoordinator);
				newGas.SetAction(Action::NewGasCollector);
				// hacky fix this
				BWAPI::Unit u = notification.GetLastUnit();
				notification.AddUnit(u);
				newGas.AddUnit(u);
				newGas.SetIsRegistered();
				_gateway.RegisterNotification(newGas);
			}
			retVal = Result::Success;

		}
	}
	return retVal;
}

float Lizurd::StrategyCoordinator::RandomFloat(float a, float b)
{
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void StrategyCoordinator::LoadDefaultStrategy()
{
	_strategy  = _gateway.GetRaceDescriptor().GetDefaultStrategy();
}

void StrategyCoordinator::RegisterNewUnit(BWAPI::UnitType type)
{
	std::stringstream ss;
	ss << "Registering new unit: " << type.getName();
	Logger::GetInstance().CriticalLog("Strategy", ss.str());
	++_buildings[type];
}


void StrategyCoordinator::DrawDebugInfo()
{
	int x = 5;

	for(std::map<BWAPI::UnitType, int>::iterator it = _buildings.begin(); it != _buildings.end(); ++it)
	{
		std::stringstream ss;
		ss << it->first.getName() << " " << it->second;
		BWAPI::Broodwar->drawText(BWAPI::CoordinateType::Screen, 5, x, ss.str().c_str());
		x += 10;
	}
	for(std::map<BWAPI::UnitType, int>::iterator it = _units.begin(); it != _units.end(); ++it)
	{
		std::stringstream ss;
		ss << it->first.getName() << " " << it->second;
		BWAPI::Broodwar->drawText(BWAPI::CoordinateType::Screen, 5, x, ss.str().c_str());
		x += 10;
	}
}