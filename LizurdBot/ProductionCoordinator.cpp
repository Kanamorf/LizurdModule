// The production coordinator is in charge of producing units.
// It will be guided by the current strategy
// Buildings are built by the ConstructionCoordinator.

#include "ProductionCoordinator.h"

using namespace Lizurd;

ProductionCoordinator::ProductionCoordinator(Gateway &gateway) :
	Coordinator(gateway, ProductionCoord)
{

}


ProductionCoordinator::~ProductionCoordinator(void)
{
}

Result ProductionCoordinator::ProcessNotificationInternal(Notification &notification)
{
	return Result::Failure;
}

Result ProductionCoordinator::UpdateInternal()
{
	return Result::Failure;
}

Result ProductionCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}
