#include <sstream>
#include "Order.h"

int Order::_instanceCount = 0;
Order::Order(std::string name, TaskPriority priority):
_name(name), _priority(priority),  _isUnderway(false), _cost(ResourceValue(0,0,0)), _isUnique(false)
{
	_executor = nullptr;
	_instanceId = _instanceCount++;
}

Order::Order( std::string name, BWAPI::Unit executor, TaskPriority priority ):
_name(name), _priority(priority), _executor(executor), _isUnderway(false), _cost(ResourceValue(0,0,0)), _isUnique(false)
{
	_instanceId = _instanceCount++;
}

Order::~Order(void)
{
	_executor = nullptr;
}

bool Order::IsComplete() const
{
	return _isUnderway;
}


bool Order::ShouldRetry()
{
	bool retry = false;
	if(_executor != nullptr)
	{
		if(!_executor->exists())
		{
			_executor = nullptr;
		}
		else
		{
			retry = _executor->isIdle() && IsComplete() == false;
		}
	}
	return retry;
}
bool Order::ShouldStart() const
{
	return IsReady() && IsUnderway() == false;
}

std::string Order::GetNameWithID() const
{
	std::stringstream ss;
	ss << _name << "#" << _instanceId;
	return ss.str();
}
