#include "ZergHatchery.h"

using namespace Lizurd;

ZergHatchery::ZergHatchery(BWAPI::Unit building, Base &base) :
	Building(building, base, ResourceValue(300, 0, 0), ZergHatcheryName)
{
}


ZergHatchery::~ZergHatchery(void)
{
}

Order* ZergHatchery::ProduceUnit(BWAPI::UnitType type)
{
	return nullptr;
}

bool ZergHatchery::IsOkToBuild() const 
{
	return true;
}

BWAPI::UnitType ZergHatchery::GetType() const 
{
	return BWAPI::UnitTypes::Zerg_Hatchery;
}

Order* ZergHatchery::CreateBuildOrder(BWAPI::TilePosition position)
{
	return nullptr;
}

bool ZergHatchery::CanBuild(BWAPI::UnitType type)
{
	return true;
}
