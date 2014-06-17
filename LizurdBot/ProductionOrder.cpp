#include "ProductionOrder.h"
#include "Logger.h"

using namespace Lizurd;

ProductionOrder::ProductionOrder(std::string name, TaskPriority priority):
	Order(name, priority)
{
	isInstantSpend = true;
}
ProductionOrder::ProductionOrder(std::string name, BWAPI::Unit executor, TaskPriority priority):
	Order(name, executor, priority)
{
	isInstantSpend = true;
}


ProductionOrder::~ProductionOrder(void)
{
}



bool ProductionOrder::IsReady() const
{
	bool result = false;
	if(_executor != NULL && _result != BWAPI::UnitTypes::None)
	{
		result = true;
	}
	return result;
}

bool ProductionOrder::Execute()
{
	Logger::GetInstance().Log("ProductionOrder", "Executing ProductionOrderbuilding : " + _result.getName());
	return _executor->train(_result);
}