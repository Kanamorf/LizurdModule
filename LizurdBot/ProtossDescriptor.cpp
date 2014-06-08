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


Base* ProtossDescriptor::CreateBaseFromCommandCentre(BWAPI::Unit unit) 
{
	Logger::GetInstance().Log("ProtossDescriptor", "CreateBaseFromCommandCentre");
	return nullptr;
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
