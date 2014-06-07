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

Result UnitDiscoveryCoordinator::UpdateInternal()
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
	if(notification.size() == 1)
	{
		if(notification.GetAction() == Action::RegisterUnit)
		{
			RegisterUnit(notification);
			retVal = Result::Success;
		}
		else if(notification.GetAction() == Action::DeRegisterUnit)
		{
			DeRegisterUnit(notification);
			retVal = Result::Success;
		}
	}

	return retVal;
}

/// <summary>
/// Registers the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
void UnitDiscoveryCoordinator::RegisterUnit(Notification &notification)
{
	BWAPI::Unit unit = notification.back();
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
			_gateway.RegisterNotification(notification);
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
}

/// <summary>
/// DeRegisters the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
void UnitDiscoveryCoordinator::DeRegisterUnit(Notification &notification)
{
	BWAPI::Unit unit = notification.back();
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
void UnitDiscoveryCoordinator::CreateNewBase(BWAPI::Unit unit)
{
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
		}
	}
	LizurdModule::VectorRemove(_orphanedUnits, attachedUnit);
}

