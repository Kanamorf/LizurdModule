// The Gateway is the entry and Exit point from our AI.
// All communication with StarCraft must take place on the 
// same thread as the game is running on. As Coordinators will
// be running on separate threads it is imperative we have a point
// where all Orders can be marshaled and issued.


#include "Gateway.h"
#include "Coordinator.h"
#include "UnitDiscoveryCoordinator.h"
#include "WorkerCoordinator.h"
#include "RaceDescriptor.h"
#include "ZergDescriptor.h"

Gateway::Gateway(void)
{
}


Gateway::~Gateway(void)
{
	if(_raceDescriptor)
	{
		delete _raceDescriptor;
	}
}

void Gateway::Initialise(BWAPI::Game *game, BWAPI::Race race)
{
	_coordinators.insert(std::pair<std::string, Coordinator*>(UnitDiscoveryCoord, new UnitDiscoveryCoordinator(*this)));
	_coordinators.insert(std::pair<std::string, Coordinator*>(WorkerCoord, new WorkerCoordinator(*this)));
	if( race == BWAPI::Races::Zerg)
	{
		_raceDescriptor = new ZergDescriptor();
	}
}

bool Gateway::Update()
{
	bool retVal = false;
	for(std::map<std::string, Coordinator*>::iterator it = _coordinators.begin(); it != _coordinators.end(); ++it)
	{
		it->second->Update();
	}
	std::vector<Order*> completeOrders;
	for(std::vector<Order*>::iterator it = _orders.begin(); it != _orders.end(); ++it)
	{
		retVal = (*it)->Execute();
		if(retVal)
		{
			completeOrders.push_back(*it);
		}
	}
	for(std::vector<Order*>::iterator it = completeOrders.begin(); it != completeOrders.end(); ++it)
	{
		std::vector<Order*>::iterator found = std::find(_orders.begin(), _orders.end(), *it);
		if(found != _orders.end())
			_orders.erase(found);
		delete *it;
	}

	ResourceValue(GetGame().self()->minerals(), GetGame().self()->gas(), GetGame().self()->supplyUsed(), GetGame().self()->supplyTotal());

	return retVal;
}

bool Gateway::RegisterNotification(Notification &notification) const
{
	bool retVal = false;
	std::string target = notification.GetTarget();
	std::map<std::string, Coordinator*>::const_iterator found = _coordinators.find(target);
	if(found != _coordinators.end())
	{
		found->second->ProcessNotificationInternal(notification);
		retVal = true;
	}
	return retVal;
}

void Gateway::AddOrder(Order *order)
{
	_orders.push_back(order);
}
