// The UnitDiscoveryCoordinator controls the flow of all new and destroyed units.
// It will pass control of each new unit to the correct Coordinator, i.e. new workers
// will be passed to the WorkerCoordinator. This also happens in reverse when units are
// destroyed.

#include "UnitDiscoveryCoordinator.h"
#include "RaceDescriptor.h"
#include "Base.h"
#include "Building.h"

using namespace Lizurd;

UnitDiscoveryCoordinator::UnitDiscoveryCoordinator(Gateway &gateway) :
	Coordinator(gateway, UnitDiscoveryCoord)
{
}


UnitDiscoveryCoordinator::~UnitDiscoveryCoordinator(void)
{
}

Result UnitDiscoveryCoordinator::UpdateInternal(int frameNo)
{ 
	return Result::Failure;
}

Result UnitDiscoveryCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}

Result UnitDiscoveryCoordinator::ProcessNotificationInternal(Notification &notification)
{
	Result retVal = Result::Failure;

	if(notification.GetAction() == Action::RegisterUnit)
	{
		retVal = RegisterUnit(notification);
	}
	else if(notification.GetAction() == Action::DeRegisterUnit)
	{
		retVal = DeRegisterUnit(notification);
	}
	else if(notification.GetAction() == Action::MorphUnit)
	{
		retVal = MorphUnit(notification);
	}
	else if(notification.GetAction() == Action::RequestIdleUnit)
	{
		Logger::GetInstance().Log(UnitDiscoveryCoord, "Running  Action::RequestIdleUnit");
		if(notification.GetUnitType() == _gateway.GetRaceDescriptor().GetWorkerType())
		{
			Logger::GetInstance().Log(UnitDiscoveryCoord, "Running  Action::RequestIdleUnit, the requested unit is a worker go look in worker coordinator.");
			notification.SetTarget(WorkerCoord);
			retVal = _gateway.RegisterNotification(notification);
		}
		else
		{
			BWAPI::Unit unit = FindIdleUnit(notification);
			if(unit != nullptr)
			{
				notification.AddUnit(unit);
				retVal = Result::Success;
			}
		}
	}

	return retVal;
}

/// <summary>
/// Registers the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
Result UnitDiscoveryCoordinator::RegisterUnit(Notification &notification)
{
	Result retVal = Result::Failure;
	if(notification.UnitSize() == 1)
	{
		BWAPI::Unit unit = notification.GetLastUnit();
		Logger::GetInstance().Log(GetName(), "Registering unit: " + unit->getType().getName());
		if(unit->getType() == _gateway.GetRaceDescriptor().GetCommandCenterType())
		{
			CreateNewBase(unit);
		}
		else if(unit->getType().isBuilding() == false)
		{
			if(unit->getType().isWorker())
			{	
				notification.SetTarget(WorkerCoord);
				notification.SetAction(Action::RegisterUnit);
				notification.AddUnit(unit);
				retVal = _gateway.RegisterNotification(notification);
			}
			Base* pBase = FindClosestFriendlyBase(unit);
			if(pBase == nullptr)
			{
				Logger::GetInstance().Log(GetName(), "Orphaned unit: " + unit->getType().getName());
				_orphanedUnits.push_back(unit);
			}
			else
			{
				pBase->AddUnit(unit);
			}

		}
		else
		{
			_localBuildings.push_back(unit);
		}
		retVal = Result::Success;
	}
	return retVal;
}

/// <summary>
/// DeRegisters the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
Result UnitDiscoveryCoordinator::DeRegisterUnit(Notification &notification)
{
	Result retVal = Result::Failure;
	if(notification.UnitSize() == 1)
	{
		BWAPI::Unit unit = notification.GetLastUnit();
		Logger::GetInstance().Log(GetName(), "DeRegistering unit: " + unit->getType().getName());
		if(unit->getType() == _gateway.GetRaceDescriptor().GetCommandCenterType())
		{
			//command centre is saved inside a base...work out how to find the correct base and remove the command centre
		}
		else if(unit->getType().isBuilding() == false)
		{
			if(unit->getType().isWorker())
			{
				notification.SetTarget(WorkerCoord);
				_gateway.RegisterNotification(notification);
			}
			else
			{
				VectorRemove(_orphanedUnits, unit);
			}
		}
		else
		{
			VectorRemove(_localBuildings, unit);
		}
		retVal = Result::Success;
	}
	return retVal;
}

void UnitDiscoveryCoordinator::DrawDebugInfo()
{
	for(std::vector<Base*>::const_iterator it = _bases.begin(); it != _bases.end(); ++it)
	{
		if(*it)
		{
			(*it)->DrawDebugInfo();
		}
	}
}

/// <summary>
/// Finds the closest base.
/// </summary>
/// <param name="unit">The unit.</param>
/// <returns>The closest base</returns>
Base* UnitDiscoveryCoordinator::FindClosestFriendlyBase(const BWAPI::Unit unit) const
{
	int smallestDistance = INT_MAX;
	Base* foundUnit = nullptr;
	if(unit->exists() == true)
	{

		for(BaseVector::const_iterator it = _bases.begin(); it != _bases.end(); ++it)
		{
			if(unit->getPlayer() != (*it)->GetCommandCentre().GetPlayer())
			{
				break;
			}
			int distance = (*it)->GetCommandCentre().GetDistance(unit);
			if(distance < smallestDistance)
			{
				smallestDistance = distance;
				foundUnit = (*it);
			}
		}
	}

	return foundUnit;
}

Result UnitDiscoveryCoordinator::CreateNewBase(BWAPI::Unit unit)
{
	Result retVal = Result::Failure;
	Base* pBase = _gateway.GetRaceDescriptor().CreateBaseFromCommandCentre(unit);
	pBase->SetRaceDescriptor(&_gateway.GetRaceDescriptor());
	_bases.push_back(pBase);

	UnitVector attachedUnit;
	for(UnitVector::iterator it = _orphanedUnits.begin(); it != _orphanedUnits.end(); ++it)
	{
		Base* pBase = FindClosestFriendlyBase(*it);
		if(pBase && (*it)->exists())
		{
			pBase->AddUnit(*it);
			attachedUnit.push_back(*it);
			retVal = Result::Success;
		}
	}
	LizurdModule::VectorRemove(_orphanedUnits, attachedUnit);
	return retVal;
}

BWAPI::Unit UnitDiscoveryCoordinator::FindIdleUnit(Notification &notification)
{
	BWAPI::Unit unit = nullptr;
	for(BaseVector::iterator it = _bases.begin(); it != _bases.end(); ++it)
	{
		unit = (*it)->FindIdleUnit(notification.GetUnitType());
		if(unit != nullptr)
			break;
	}
	return unit;
}

Result UnitDiscoveryCoordinator::MorphUnit(Notification &notification)
{
	Result retVal = Result::Failure;
	BWAPI::Unit unit = notification.GetLastUnit();
	if(unit != nullptr)
	{
		bool success = false;
		//Making an assumption here that a unit cannot morph unless it is already registered with a base.
		for(BaseVector::iterator it = _bases.begin(); it != _bases.end(); ++it)
		{
			if((*it) != nullptr)
			{
				success = (*it)->RemoveUnitByPointer(unit);
			}
			if(success == true)
				break;
		}
		if(success == true)
		{
			notification.AddUnit(unit);
			retVal = RegisterUnit(notification);
		}
	}
	return retVal;
}

