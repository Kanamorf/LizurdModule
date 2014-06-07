#include "ZergDescriptor.h"
#include "ZergHatchery.h"
#include "Base.h"

ZergDescriptor::ZergDescriptor(void)
{
}


ZergDescriptor::~ZergDescriptor(void)
{
}

Building& ZergDescriptor::GetNewCommandCenter(BWAPI::Unit unit) 
{
	Base *base = new Base();
	ZergHatchery *hatchery = new ZergHatchery(unit, *base);
	_buildings.push_back(hatchery);
	return *hatchery;
}
