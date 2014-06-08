#include "ConstructionOrder.h"
#include "Logger.h"
#include <sstream>

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
	Logger::GetInstance().Log("ConstructionOrder", "Executing ConstructionOrder building : " + _result.getName());
	bool success = _executor->build(_result, _position);
	std::stringstream ss;
	ss << "Attempting to build using a drone that is at x:" << _executor->getTilePosition().x << " y:" << _executor->getTilePosition().y
		<< " building location x:" << _position.x << " y:" << _position.y;
	Logger::GetInstance().Log("ConstructionOrder", "Executing ConstructionOrder " + ss.str());
	return success;
}