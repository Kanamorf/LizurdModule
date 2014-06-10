#include "ZergSpawningPool.h"

using namespace Lizurd;

Lizurd::ZergSpawningPool::ZergSpawningPool(BWAPI::Unit building):
	Building(building, nullptr, ResourceValue(200, 0, 0), ZergSpawningPoolName, 1200)
{

}


ZergSpawningPool::ZergSpawningPool(BWAPI::Unit building, Base *base):
	Building(building, base, ResourceValue(200, 0, 0), ZergSpawningPoolName, 1200)
{
}


ZergSpawningPool::~ZergSpawningPool(void)
{
}

Order* ZergSpawningPool::ProduceUnit(BWAPI::UnitType type)
{
	return nullptr;
}

bool Lizurd::ZergSpawningPool::IsOkToBuild() const 
{
	return true;
}

bool ZergSpawningPool::CanBuild(BWAPI::UnitType type)
{
	return true;
}

Order* ZergSpawningPool::CreateBuildOrder(BWAPI::TilePosition position)
{
	return nullptr;
}

BWAPI::UnitType ZergSpawningPool::GetType() const 
{
	return BWAPI::UnitTypes::Zerg_Spawning_Pool;
}
