#include "UnitDiscoveryCoordinator.h"
#include "RaceDescriptor.h"


UnitDiscoveryCoordinator::UnitDiscoveryCoordinator(void)
{
}


UnitDiscoveryCoordinator::~UnitDiscoveryCoordinator(void)
{
}



/// <summary>
/// Registers the unit in preperation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
void UnitDiscoveryCoordinator::RegisterUnit(BWAPI::Unit unit)
{
	if(unit->getType() == RaceDescriptor::GetInstance().GetCommandCenterType())
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