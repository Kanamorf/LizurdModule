#include "TerranDescriptor.h"
#include "Base.h"
#include "Logger.h"
#include "Strategy.h"

using namespace Lizurd;

TerranDescriptor::TerranDescriptor(void)
{
}


TerranDescriptor::~TerranDescriptor(void)
{
}

void TerranDescriptor::CreateBaseFromCommandCentre(BWAPI::Unit unit, Base *base) 
{
}

Strategy* TerranDescriptor::GetDefaultStrategy() const
{
	Logger::GetInstance().Log("ZergDescriptor", "GetDefaultStrategy");
	return nullptr;
}

Goal* Lizurd::TerranDescriptor::GetSupplyGoal() const 
{
	return nullptr;
}

