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

Result Lizurd::StrategyCoordinator::UpdateInternal()
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
	return retVal;
}

void StrategyCoordinator::LoadDefaultStrategy()
{
	_strategy  = _gateway.GetRaceDescriptor().GetDefaultStrategy();
}
