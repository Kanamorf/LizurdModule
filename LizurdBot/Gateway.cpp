// The Gateway is the entry and Exit point from our AI.
// All communication with StarCraft must take place on the 
// same thread as the game is running on. As Coordinators will
// be running on separate threads it is imperative we have a point
// where all Orders can be marshaled and issued.


#include "Gateway.h"
#include "Coordinator.h"
#include "UnitDiscoveryCoordinator.h"
#include "WorkerCoordinator.h"
#include "StrategyCoordinator.h"
#include "ResourceCoordinator.h"
#include "ProductionCoordinator.h"
#include "RaceDescriptor.h"
#include "ZergDescriptor.h"
#include "TerranDescriptor.h"
#include "ProtossDescriptor.h"
#include "ConstructionCoordinator.h"

using namespace Lizurd;

Gateway::Gateway(void):
	_raceDescriptor(nullptr)
{
}


Gateway::~Gateway(void)
{
	if(_raceDescriptor)
	{
		delete _raceDescriptor;
	}
	for(std::map<std::string, Coordinator*>::iterator it = _coordinators.begin(); it != _coordinators.end(); ++it)
	{
		if(it->second != nullptr)
			delete it->second;
	}
}

Result Gateway::Initialise(BWAPI::Game *game, BWAPI::Race race)
{
	Result retVal = Result::Failure;
	
	if( race == BWAPI::Races::Zerg)
	{
		_raceDescriptor = new ZergDescriptor();
		retVal = Result::Success;
	}
	if(retVal == Result::Success)
	{
		_game = game;
		_coordinators.insert(std::pair<std::string, Coordinator*>(UnitDiscoveryCoord, new UnitDiscoveryCoordinator(*this)));
		_coordinators.insert(std::pair<std::string, Coordinator*>(WorkerCoord, new WorkerCoordinator(*this)));
		_coordinators.insert(std::pair<std::string, Coordinator*>(ResourceCoord, new ResourceCoordinator(*this)));
		_coordinators.insert(std::pair<std::string, Coordinator*>(ProductionCoord, new ProductionCoordinator(*this)));
		_coordinators.insert(std::pair<std::string, Coordinator*>(StrategyCoord, new StrategyCoordinator(*this)));
		_coordinators.insert(std::pair<std::string, Coordinator*>(ConstructionCoord, new ConstructionCoordinator(*this)));
	}
	return retVal;
}

Result Gateway::Update()
{
	Result retVal = Result::Failure;
	for(std::map<std::string, Coordinator*>::iterator it = _coordinators.begin(); it != _coordinators.end(); ++it)
	{
		it->second->Update();
	}
	std::vector<Order*> completeOrders;
	for(std::vector<Order*>::iterator it = _orders.begin(); it != _orders.end(); ++it)
	{
		bool success = (*it)->Execute();
		if(success)
		{
			completeOrders.push_back(*it);
			if((*it)->GetCost() > ResourceValue::Zero())
			{
				Notification notification(ResourceCoord);
				notification.SetAction(Action::ResourceRelease);
				notification.SetResourceValue((*it)->GetCost());
				RegisterNotification(notification);
			}
		}
	}
	for(std::vector<Order*>::iterator it = completeOrders.begin(); it != completeOrders.end(); ++it)
	{
		std::vector<Order*>::iterator found = std::find(_orders.begin(), _orders.end(), *it);
		if(found != _orders.end())
			_orders.erase(found);
		delete *it;
	}

	ResourceValue update(GetGame().self()->minerals(), GetGame().self()->gas(), GetGame().self()->supplyUsed(), GetGame().self()->supplyTotal());
	Notification notification(ResourceCoord);
	notification.SetAction(Action::ResourceUpdate);
	notification.SetResourceValue(update);
	RegisterNotification(notification);
	retVal = Result::Success;
	return retVal;
}

Result Gateway::RegisterNotification(Notification &notification) const
{
	Result retVal = Result::Failure;
	std::string target = notification.GetTarget();
	std::map<std::string, Coordinator*>::const_iterator found = _coordinators.find(target);
	if(found != _coordinators.end())
	{
		retVal = found->second->ProcessNotificationInternal(notification);
	}
	return retVal;
}

void Gateway::AddOrder(Order *order)
{
	_orders.push_back(order);
}

void Gateway::DrawDebugInfo()
{
	for(std::map<std::string, Coordinator*>::iterator it = _coordinators.begin(); it != _coordinators.end(); ++it)
	{
		it->second->DrawDebugInfo();
	}
}
