#include "UnitDiscoveryCoordinator.h"
#include "RaceDescriptor.h"


UnitDiscoveryCoordinator::UnitDiscoveryCoordinator(Gateway &gateway) :
	Coordinator(gateway, UnitDiscoveryCoord)
{
}


UnitDiscoveryCoordinator::~UnitDiscoveryCoordinator(void)
{
}

bool UnitDiscoveryCoordinator::UpdateInternal()
{ 
	return false;
}

bool UnitDiscoveryCoordinator::AfterUpdateInternal()
{
	return false;
}

bool UnitDiscoveryCoordinator::ProcessNotification(Notification &notification)
{
	bool retVal = false;
	if(notification.size() == 1)
	{
		if(notification.GetAction() == Notification::Action::RegisterUnit)
		{
			RegisterUnit(notification);
			retVal = true;
		}
		else if(notification.GetAction() == Notification::Action::DeRegisterUnit)
		{
			DeRegisterUnit(notification);
			retVal = true;
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
		_commandCentres.push_back(unit);
	}
	else if(unit->getType().isBuilding() == false)
	{
		if(unit->getType().isWorker())
		{
			Logger::GetInstance().Log(GetName(), "Registering unit: " + unit->getType().getName());
			notification.SetTarget(WorkerCoord);
			_gateway.RegisterNotification(notification);
		}
		else
		{
			_localUnits.push_back(unit);
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
		VectorRemove(_commandCentres, unit);
	}
	else if(unit->getType().isBuilding() == false)
	{
		if(unit->getType().isWorker())
		{
			notification.SetTarget("WorkerCoordinator");
			_gateway.RegisterNotification(notification);
		}
		else
		{
			VectorRemove(_localUnits, unit);
		}
	}
	else
	{
		VectorRemove(_localBuildings, unit);
	}
}


