// The production coordinator is in charge of producing units.
// It will be guided by the current strategy
// Buildings are built by the ConstructionCoordinator.

#include "ProductionCoordinator.h"
#include "ProductionOrder.h"
#include "Goal.h"
#include "Logger.h"
#include <string>

using namespace Lizurd;

ProductionCoordinator::ProductionCoordinator(Gateway &gateway) :
	Coordinator(gateway, ProductionCoord),
	_currentGoal(nullptr)
{
}


ProductionCoordinator::~ProductionCoordinator(void)
{
}

Result ProductionCoordinator::ProcessNotificationInternal(Notification &notification)
{
	return Result::Failure;
}

Result ProductionCoordinator::UpdateInternal(int frameNo)
{
	Result retVal = Result::Failure;
	// first we need to check we have a goal;
	if(_currentGoal == nullptr || _currentGoal->GetExecutingUnitType() == BWAPI::UnitTypes::Enum::None)
	{

		Logger::GetInstance().Log(ProductionCoord, "Looking for a goal.");
		Notification notification(StrategyCoord);
		notification.SetAction(Action::GetNextProductionGoal);
		if(_gateway.RegisterNotification(notification) == Result::Success)
		{
			Logger::GetInstance().Log(ProductionCoord, "Found a goal.");
			_currentGoal = notification.GetGoal();
		}
	}
	if(_currentGoal != nullptr)
	{
		Logger::GetInstance().Log(ProductionCoord, "We have a goal. " + _currentGoal->GetGoalType());
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
				Logger::GetInstance().Log(ProductionCoord, "Found a unit to execute the goal.");
				BWAPI::Unit executingUnit = notification.GetLastUnit();
				if(executingUnit != nullptr)
				{
					// we have all the bits we need....
					Order *order = _currentGoal->CreateOrder(executingUnit);
					_gateway.AddOrder(order);
					_currentGoal->DecrementTotal();
					if(_currentGoal->IsComplete())
					{
						Logger::GetInstance().Log(ProductionCoord, _currentGoal->GetGoalType() + " is complete, removing.");
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
					Logger::GetInstance().Log(ProductionCoord, "Failed to release a resource reservation.");
				}
			}
		}


	}
	return retVal;
}

Result ProductionCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}
