#include <sstream>
#include "GasOrder.h"
#include "Logger.h"

using namespace Lizurd;

GasOrder::GasOrder(BWAPI::Unit unit):
	Order(GASORDER, unit, TaskPriority::Gather),
	_extractor(nullptr)	
{
}

GasOrder::~GasOrder(void)
{
}


bool GasOrder::IsReady() const
{
	bool result = false;
	if(_executor != nullptr)
	{
		result = true;
	}
	return result;
}

bool GasOrder::Execute()
{
	std::stringstream ss;
	ss << "Executing GasOrder {" << GetID() << "}";
	Logger::GetInstance().Log(GetName(),  ss.str());
	bool success = false;
	if(_extractor != nullptr)
	{
		success = _executor->gather(_extractor);
		if(success)
		{
			SetIsUnderway(true);
		}
	}
	return success;
}
