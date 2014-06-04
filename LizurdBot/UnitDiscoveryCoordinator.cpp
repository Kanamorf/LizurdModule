#include "UnitDiscoveryCoordinator.h"
#include "RaceDescriptor.h"


UnitDiscoveryCoordinator::UnitDiscoveryCoordinator(Gateway &gateway) :
	Coordinator(gateway, "UnitDiscoveryCoordinator")
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

bool UnitDiscoveryCoordinator::ProcessNotification(const Notification &notification)
{
	bool retVal = false;
	if(notification.size() == 1)
	{
		RegisterUnit(notification.back());
		retVal = true;
	}
	
	return retVal;
}

/// <summary>
/// Registers the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
void UnitDiscoveryCoordinator::RegisterUnit(BWAPI::Unit unit)
{
	if(unit->getType() == _gateway.GetRaceDescriptor().GetCommandCenterType())
	{
		_commandCentres.push_back(unit);
	}
	else if(unit->getType().isBuilding() == false)
	{
		_localUnits.push_back(unit);
	}
	else
	{
		_localBuildings.push_back(unit);
	}
}