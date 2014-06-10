// The production coordinator is in charge of producing units.
// It will be guided by the current strategy
// Buildings are built by the ConstructionCoordinator.

#include "ProductionCoordinator.h"
#include "RaceDescriptor.h"
#include "ProductionOrder.h"
#include "Goal.h"
#include "Logger.h"
#include <string>

using namespace Lizurd;

ProductionCoordinator::ProductionCoordinator(Gateway &gateway) :
	Coordinator(gateway, ProductionCoord),
	_currentGoal(nullptr),
	_savedGoal(nullptr),
	_buildingSupply(false)
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

	// check we have enough supply
	Notification notification(ResourceCoord);
	notification.SetAction(Action::CurrentResources);
	_gateway.RegisterNotification(notification);
	ResourceValue value =notification.GetResourceValue();

	// If we are running at greater than 80% make more supply 
	if((float)value.Supply >= (float)((float)value.MaxSupply * 0.8))
	{
		// save the goal we have currently
		_savedGoal = _currentGoal;
		_currentGoal = _gateway.GetRaceDescriptor().GetSupplyGoal();
		_buildingSupply = true;
	}

	// if we have no goal grab the saved goal
	if(_currentGoal == nullptr)
	{
		_currentGoal = _savedGoal;
		_savedGoal = nullptr;
	}

	// if we still don't have a goal go get a new one
	if(_currentGoal == nullptr || _currentGoal->GetExecutingUnitType() == BWAPI::UnitTypes::Enum::None)
	{
		Notification notification(StrategyCoord);
		notification.SetAction(Action::GetNextProductionGoal);
		if(_gateway.RegisterNotification(notification) == Result::Success)
		{
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
				BWAPI::Unit executingUnit = notification.GetLastUnit();
				if(executingUnit != nullptr)
				{
					// we have all the bits we need....
					Order *order = _currentGoal->CreateOrder(executingUnit);
					_gateway.AddOrder(order);
					_currentGoal->DecrementTotal();
					if(_currentGoal->IsComplete())
					{
						if(_currentGoal->GetGoalType() == _gateway.GetRaceDescriptor().GetSupplyType())
							_buildingSupply = false;
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
