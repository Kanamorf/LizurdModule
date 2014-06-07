#include "ZergDescriptor.h"
#include "ZergHatchery.h"
#include "Base.h"
#include "Logger.h"

ZergDescriptor::ZergDescriptor(void)
{
}


ZergDescriptor::~ZergDescriptor(void)
{
}

Base* ZergDescriptor::CreateBaseFromCommandCentre(BWAPI::Unit unit) 
{
	Logger::GetInstance().Log("ZergDescriptor", "CreateBaseFromCommandCentre");
	Base *pBase = new Base();
	ZergHatchery *pHhatchery = new ZergHatchery(unit, *pBase);
	pBase->SetCommandCentre(pHhatchery);
	return pBase;
}
