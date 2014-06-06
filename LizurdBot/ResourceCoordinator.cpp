// The resource coordinator will keep track of all resources in the game.
// It will know how many resources the game has, it will be the place all coordinators
// request resources for building etc.  It will hold 2 values, the total resources and the
// reserved resources... Resources get reserved at the point an Order is created, this is 
// because Orders are not always instantly executed, for example a Build Order is created 
// it takes time for the worker to move to the position where the building is to be placed.
// Once the building is placed the resources are removed by the game. Reserving this cost means
// we can keep track of these and still know how much we have for other Orders.


#include "ResourceCoordinator.h"


ResourceCoordinator::ResourceCoordinator(Gateway &gateway) :
	Coordinator(gateway, ResoueceCoord),
	_resources(ResourceValue::Zero())
{
}


ResourceCoordinator::~ResourceCoordinator(void)
{
}

Result ResourceCoordinator::ProcessNotificationInternal(Notification &notification)
{
	return Result::Failure;
}

Result ResourceCoordinator::UpdateInternal()
{
	return Result::Failure;
}

Result ResourceCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}
