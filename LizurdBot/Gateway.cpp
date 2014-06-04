#include "Gateway.h"
#include "Coordinator.h"
#include "UnitDiscoveryCoordinator.h"
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

void Gateway::Initialise(BWAPI::Race race)
{
	_coordinators.insert(std::pair<std::string, Coordinator*>("UnitDiscoveryCoordinator", new UnitDiscoveryCoordinator(*this)));

	if( race == BWAPI::Races::Zerg)
	{
		_raceDescriptor = new ZergDescriptor();
	}
}

bool Gateway::Update()
{
	for(std::map<std::string, Coordinator*>::iterator it = _coordinators.begin(); it != _coordinators.end(); ++it)
	{
		it->second->Update();
	}
	return true;
}

bool Gateway::RegisterNotification(const Notification &notification) const
{
	bool retVal = false;
	std::string target = notification.GetTarget();
	std::map<std::string, Coordinator*>::const_iterator found = _coordinators.find(target);
	if(found != _coordinators.end())
	{
		found->second->ProcessNotification(notification);
		retVal = true;
	}
	return retVal;
}
