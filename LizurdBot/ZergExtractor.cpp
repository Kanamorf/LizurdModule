#include "ZergExtractor.h"

using namespace Lizurd;

ZergExtractor::ZergExtractor(BWAPI::Unit building):
	Building(building, nullptr, ResourceValue(50, 0, 0), ZergExtractorName, 1200)
{

}


ZergExtractor::ZergExtractor(BWAPI::Unit building, Base *base):
	Building(building, base, ResourceValue(50, 0, 0), ZergExtractorName, 1200)
{
}


ZergExtractor::~ZergExtractor(void)
{
}

Order* ZergExtractor::ProduceUnit(BWAPI::UnitType type)
{
	return nullptr;
}

bool ZergExtractor::IsOkToBuild() const 
{
	return true;
}

bool ZergExtractor::CanBuild(BWAPI::UnitType type)
{
	return true;
}

Order* ZergExtractor::CreateBuildOrder(BWAPI::TilePosition position)
{
	return nullptr;
}

BWAPI::UnitType ZergExtractor::GetType() const 
{
	return BWAPI::UnitTypes::Zerg_Extractor;
}
