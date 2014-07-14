#include "SquadCoordinator.h"
#include "AttackOrder.h"
#include "RaceDescriptor.h"

using namespace Lizurd;

SquadCoordinator::SquadCoordinator(Gateway &gateway) :
	Coordinator(gateway, SquadCoord),
	_attackcount(10)
{
}


SquadCoordinator::~SquadCoordinator(void)
{
}

Result SquadCoordinator::ProcessNotificationInternal(Notification &notification)
{
	Result retVal = Result::Failure;
	if(notification.GetAction() == Action::RegisterOwnUnit)
	{
		RegisterUnit(notification);
		retVal = Result::Success;
	}
	return retVal;
}

Result SquadCoordinator::UpdateInternal(int frameNo)
{
	if(_units.size() >= _attackcount)
	{
		BWAPI::Position pos;
		BWAPI::Unit unit = _units.front();
		if(unit->getPosition().y > 1000)
		{
			pos.x = 675;
			pos.y = 497;
		}
		else
		{
			pos.x = 1341;
			pos.y = 5547;			
		}
		AttackOrder *pOrder = new AttackOrder(TaskPriority::High);
		pOrder->AddUnits(_units);
		pOrder->SetTarget(pos);
		_units.clear();
		_gateway.AddOrder(pOrder);
		_attackcount *= 2;
		if(_attackcount > 80)
		{
			_attackcount = 80;
		}
	}
	return Result::Success;
}

Result SquadCoordinator::AfterUpdateInternal()
{
	return Result::Success;
}

void SquadCoordinator::RegisterUnit(Notification &notification)
{
	BWAPI::Unit unit = notification.GetLastUnit();
	std::string type = unit->getType().getName();
	if(_gateway.GetRaceDescriptor().IsMilitaryUnit(unit))
		_units.push_back(unit);
}
