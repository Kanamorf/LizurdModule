#include "Notification.h"

using Lizurd::Notification;

Notification::Notification(std::string target) :
	_target(target)
{
}


Notification::~Notification(void)
{
}


void Notification::push_back(BWAPI::Unit unit)
{
	_units.push_back(unit);
}

BWAPI::Unit Notification::back() const
{
	return _units.back();
}

size_t Notification::size() const
{
	return _units.size();
}

