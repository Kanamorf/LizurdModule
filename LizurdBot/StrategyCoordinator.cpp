#include "StrategyCoordinator.h"
#include "RaceDescriptor.h"
#include "Strategy.h"

using namespace Lizurd;

StrategyCoordinator::StrategyCoordinator(Gateway &gateway) :
	Coordinator(gateway, StrategyCoord)
{
	LoadDefaultStrategy();
}


StrategyCoordinator::~StrategyCoordinator(void)
{
}

Result Lizurd::StrategyCoordinator::UpdateInternal(int frameNo)
{
	return Result::Failure;
}

Result Lizurd::StrategyCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}

Result Lizurd::StrategyCoordinator::ProcessNotificationInternal(Notification &notification)
{
	Result retVal = Result::Failure;
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
		_strategy->RegisterNewUnit(notification.GetUnitType());
		retVal = Result::Success;
		
	}
	return retVal;
}

void StrategyCoordinator::LoadDefaultStrategy()
{
	_strategy  = _gateway.GetRaceDescriptor().GetDefaultStrategy();
}
