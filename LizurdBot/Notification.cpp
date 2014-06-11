#include "Notification.h"

using namespace Lizurd;

Notification::Notification(Coordinators target) :
	_target(target)
{
}


Notification::~Notification(void)
{
}


void Notification::AddUnit(BWAPI::Unit unit)
{
	_units.push_back(unit);
}

BWAPI::Unit Notification::GetLastUnit()
{
	BWAPI::Unit unit = nullptr;
	if(_units.size() > 0)
	{
		unit = _units.back();
		_units.pop_back();
	}	
	return unit;
}

size_t Notification::UnitSize() const
{
	return _units.size();
}

BWAPI::Unit Notification::PeekUnit() const
{
	BWAPI::Unit unit = nullptr;
	if(_units.size() > 0)
	{
		unit = _units.back();
	}	
	return unit;
}

