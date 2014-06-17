#include "StrategyCoordinator.h"
#include "RaceDescriptor.h"
#include "Strategy.h"
#include <stdlib.h>
#include <time.h>
#include "ProductionGoal.h"

using namespace Lizurd;

StrategyCoordinator::StrategyCoordinator(Gateway &gateway) :
	Coordinator(gateway, StrategyCoord)
{
	LoadDefaultStrategy();
	srand(static_cast<unsigned int>(time(NULL)));
	// We start the game with a command centre
	++_buildings[_gateway.GetRaceDescriptor().GetCommandCenterType()];
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
	if(notification.GetTarget() != Coordinators::StrategyCoordinator)
	{
		if(notification.GetUnitType() == BWAPI::UnitTypes::Resource_Mineral_Field)
		{
			int i = 0;
		}

		// All notifications come via strategy coordinator so we can count stuff
		switch(notification.GetAction().Underlying())
		{
		case Action::RegisterOwnUnit:
			
			++_units[notification.GetUnitType()];
			break;
		case Action::DeRegisterUnit :
			--_units[notification.GetUnitType()];
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
			RegisterNewUnit(notification.GetUnitType());
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
