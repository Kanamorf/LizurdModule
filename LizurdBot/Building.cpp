#include "Building.h"
#include "Base.h"
#include "BuildingPlacer.h"

using namespace Lizurd;

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
/// <returns>Distance to the unit or -1</returns>
int Building::GetDistance( BWAPI::Unit unit ) const
{
	int distance = -1;
	if(_building)
		distance = _building->getDistance(unit);
	return distance;
}

/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
BWAPI::Position Building::GetPosition() const
{
	BWAPI::Position position;
	if(_building)
		position = _building->getPosition();
	return position;
}

/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
BWAPI::TilePosition Building::GetTilePosition() const
{
	BWAPI::TilePosition position;
	if(_building)
		position = _building->getTilePosition();
	return position;
}


/// <summary>
/// Determines whether this building is idle.
/// </summary>
/// <returns>True if the building can produce and is not</returns>
bool Building::IsIdle() const
{
	bool idle = false;
	if(_building)
		idle = _building->isIdle();
	return idle;
}

BWAPI::Player Building::GetPlayer() const
{
	BWAPI::Player player = nullptr;
	if(_building)
		player = _building->getPlayer();
	return player;
}


