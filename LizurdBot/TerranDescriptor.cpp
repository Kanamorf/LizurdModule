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

Base* TerranDescriptor::CreateBaseFromCommandCentre(BWAPI::Unit unit) 
{
	return nullptr;
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

