// The resource coordinator will keep track of all resources in the game.
// It will know how many resources the game has, it will be the place all coordinators
// request resources for building etc.  It will hold 2 values, the total resources and the
// reserved resources... Resources get reserved at the point an Order is created, this is 
// because Orders are not always instantly executed, for example a Build Order is created 
// it takes time for the worker to move to the position where the building is to be placed.
// Once the building is placed the resources are removed by the game. Reserving this cost means
// we can keep track of these and still know how much we have for other Orders.


#include "ResourceCoordinator.h"

using namespace Lizurd;

ResourceCoordinator::ResourceCoordinator(Gateway &gateway) :
	Coordinator(gateway, ResourceCoord),
	_totalResources(ResourceValue::Zero())
{
}


ResourceCoordinator::~ResourceCoordinator(void)
{
}

Result ResourceCoordinator::ProcessNotificationInternal(Notification &notification)
{
	Result retVal = Result::Failure;
	if(notification.GetAction() == Action::ResourceUpdate)
	{
		_totalResources = notification.GetResourceValue();
		retVal = Result::Success;
	}
	if(notification.GetAction() == Action::ResourceRequest)
	{
		retVal = RequestResources(notification.GetResourceValue());
	}
	if(notification.GetAction() == Action::ResourceRelease)
	{
		retVal = ReleaseResources(notification.GetResourceValue());
	}
	if(notification.GetAction() == Action::CurrentResources)
	{
		notification.SetResourceValue(GetCurrentResources());
		retVal = Result::Success;
	}
	return retVal;
}

Result ResourceCoordinator::UpdateInternal()
{
	return Result::Failure;
}

Result ResourceCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}

ResourceValue ResourceCoordinator::GetCurrentResources() const
{
	ResourceValue perceivedResources = _totalResources - _reservedResources;
	return perceivedResources;
}

Result ResourceCoordinator::RequestResources(ResourceValue value)
{
	Result retVal = Result::Failure;
	Logger::GetInstance().Log(ResourceCoord, "RequestResources");
	if(GetCurrentResources() >= value)
	{
		Logger::GetInstance().Log(ResourceCoord, "RequestResources found enough");
		_reservedResources += value;
		retVal = Result::Success;
	}
	else
	{
		retVal = Result::InsufficientResources;
	}
	return retVal;
}

Result ResourceCoordinator::ReleaseResources(ResourceValue value)
{
	Result retVal = Result::Failure;
	if(_reservedResources >= value)
	{
		_reservedResources -= value;
		retVal = Result::Success;
	}
	else
	{
		retVal = Result::InsufficientReservedResources;
	}
	return retVal;
}
