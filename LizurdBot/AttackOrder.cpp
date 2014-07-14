#include "AttackOrder.h"

using namespace Lizurd;

AttackOrder::AttackOrder(TaskPriority priority):
	Order(ATTACKORDER, priority)
{
}


AttackOrder::~AttackOrder(void)
{
}

void AttackOrder::AddUnits(const BWAPI::Unitset &units)
{
	_units = units;
}

bool Lizurd::AttackOrder::Execute()
{
	_units.attack(_target);
	return true;
}
