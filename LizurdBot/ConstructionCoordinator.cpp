#include "ConstructionCoordinator.h"
#include "Goal.h"

using namespace Lizurd;

ConstructionCoordinator::ConstructionCoordinator(Gateway &gateway) :
	Coordinator(gateway, ConstructionCoord),
	_currentGoal(nullptr)
{
}


ConstructionCoordinator::~ConstructionCoordinator(void)
{
}

Result ConstructionCoordinator::ProcessNotificationInternal(Notification &notification)
{
	return Result::Failure;
}

Result ConstructionCoordinator::UpdateInternal()
{
	Result retVal = Result::Failure;
	// first we need to check we have a goal;
	if(_currentGoal == nullptr || _currentGoal->GetExecutingUnitType() == BWAPI::UnitTypes::Enum::None)
	{

		Logger::GetInstance().Log(ConstructionCoord, "Looking for a goal.");
		Notification notification(StrategyCoord);
		notification.SetAction(Action::GetNextConstructionGoal);
		if(_gateway.RegisterNotification(notification) == Result::Success)
		{
			Logger::GetInstance().Log(ConstructionCoord, "Found a goal.");
			_currentGoal = notification.GetGoal();
		}
	}
	if(_currentGoal != nullptr)
	{
		Logger::GetInstance().Log(ConstructionCoord, "We have a goal. " + _currentGoal->GetExecutingUnitType().getName());
		// now we have a goal attempt to reserve some resources.
		Notification notification(ResourceCoord);
		notification.SetAction(Action::ResourceRequest);
		notification.SetResourceValue(_currentGoal->GetCost());
		if(_gateway.RegisterNotification(notification) == Result::Success)
		{
			// next we need to get a unit to execute the order
			notification.SetTarget(UnitDiscoveryCoord);
			notification.SetAction(Action::RequestIdleUnit);
			notification.SetUnitType(_currentGoal->GetExecutingUnitType());
			if(_gateway.RegisterNotification(notification) == Result::Success)
			{
				Logger::GetInstance().Log(ConstructionCoord, "Found a unit to execute the goal.");
				BWAPI::Unit executingUnit = notification.GetLastUnit();
				if(executingUnit != nullptr)
				{
					// we have all the bits we need....
					Order *order = _currentGoal->CreateOrder(executingUnit);
					_gateway.AddOrder(order);
					_currentGoal->DecrementTotal();
					if(_currentGoal->IsComplete())
					{
						//current goal is complete so remove it
						delete _currentGoal;
						_currentGoal = nullptr;
					}
				}
			}
			else
			{
				// we failed to find a unit to build so release the reservation.
				notification.SetTarget(ResourceCoord);
				notification.SetAction(Action::ResourceRelease);
				notification.SetResourceValue(_currentGoal->GetCost());
				if(_gateway.RegisterNotification(notification) != Result::Success)
				{
					Logger::GetInstance().Log(ConstructionCoord, "Failed to release a resource reservation.");
				}
			}
		}


	}
	return retVal;
}

Result ConstructionCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}
