#include "Building.h"
#include "Base.h"
#include "BuildingPlacer.h"


Building::Building(BWAPI::Unit building, Base &base, ResourceValue cost, std::string name):
	_building(building),
	_parentBase(base),
	_cost(cost),
	_name(name)
{
}

Building::~Building(void)
{
}

/// <summary>
/// Gets the distance to the specified unit.
/// </summary>
/// <param name="unit">The unit.</param>
/// <returns></returns>
int Building::GetDistance( BWAPI::Unit unit ) const
{
	return _building->getDistance(unit);
}

/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
BWAPI::Position Building::GetPosition() const
{
	return _building->getPosition();
}

/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
BWAPI::TilePosition Building::GetTilePosition() const
{
	return _building->getTilePosition();
}


/// <summary>
/// Determines whether this building is idle.
/// </summary>
/// <returns>True if the building can produce and is not</returns>
bool Building::IsIdle() const
{
	return _building->isIdle();
}


