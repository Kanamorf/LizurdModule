#include "ZergHydraliskDen.h"

using namespace Lizurd;

ZergHydraliskDen::ZergHydraliskDen(BWAPI::Unit building):
	Building(building, nullptr, ResourceValue(100, 50, 0), ZergSpawningPoolName, 600)
{

}


ZergHydraliskDen::ZergHydraliskDen(BWAPI::Unit building, Base *base):
	Building(building, base, ResourceValue(100, 50, 0), ZergSpawningPoolName, 600)
{
}


ZergHydraliskDen::~ZergHydraliskDen(void)
{
}

Order* ZergHydraliskDen::ProduceUnit(BWAPI::UnitType type)
{
	return nullptr;
}

bool ZergHydraliskDen::IsOkToBuild() const 
{
	return true;
}

bool ZergHydraliskDen::CanBuild(BWAPI::UnitType type)
{
	return true;
}

Order* ZergHydraliskDen::CreateBuildOrder(BWAPI::TilePosition position)
{
	return nullptr;
}

BWAPI::UnitType ZergHydraliskDen::GetType() const 
{
	return BWAPI::UnitTypes::Zerg_Hydralisk_Den;
}
