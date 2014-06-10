#include "ProtossDescriptor.h"
#include "Base.h"
#include "Logger.h"
#include "Strategy.h"
#include "ProductionGoal.h"
#include "ConstructionGoal.h"

using namespace Lizurd;

ProtossDescriptor::ProtossDescriptor(void)
{
}


ProtossDescriptor::~ProtossDescriptor(void)
{
}


void ProtossDescriptor::CreateBaseFromCommandCentre(BWAPI::Unit unit, Base *base) 
{
	Logger::GetInstance().Log("ProtossDescriptor", "CreateBaseFromCommandCentre");
}

Strategy* ProtossDescriptor::GetDefaultStrategy() const
{
	Logger::GetInstance().Log("ProtossDescriptor", "GetDefaultStrategy");
	return nullptr;
}

Goal* ProtossDescriptor::GetSupplyGoal() const 
{
	return nullptr;
}
