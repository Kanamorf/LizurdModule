#include "ConstructionOrder.h"
#include "Logger.h"

using namespace Lizurd;

ConstructionOrder::ConstructionOrder(std::string name, TaskPriority priority):
	Order(name, priority)
{

}
ConstructionOrder::ConstructionOrder(std::string name, BWAPI::Unit executor, TaskPriority priority):
	Order(name, executor, priority)
{
}


ConstructionOrder::~ConstructionOrder(void)
{
}



bool ConstructionOrder::IsReady() const
{
	bool result = false;
	if(_executor != NULL && _result != BWAPI::UnitTypes::None)
	{
		result = true;
	}
	return result;
}

bool ConstructionOrder::Execute()
{
	Logger::GetInstance().Log("ProductionOrder", "Executing ProductionOrderbuilding : " + _result.getName());
	return _executor->build(_result, _position);
}