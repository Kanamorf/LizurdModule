#include <sstream>
#include "GatherOrder.h"
#include "Logger.h"

GatherOrder::GatherOrder(BWAPI::Unit unit):
Order(GATHERORDER, unit, TaskPriority::Gather)
{
}

GatherOrder::~GatherOrder(void)
{
}


bool GatherOrder::IsReady() const
{
	bool result = false;
	if(_executor != nullptr)
	{
		result = true;
	}
	return result;
}

bool GatherOrder::Execute()
{
	std::stringstream ss;
	ss << "Executing GatherOrder {" << GetID() << "}";
	Logger::GetInstance().Log(GetName(),  ss.str());
	bool success = false;

	success = _executor->gather(_executor->getClosestUnit( BWAPI::Filter::IsMineralField ));
	if(success)
	{
		SetIsUnderway(true);
	}

	return success;
}
