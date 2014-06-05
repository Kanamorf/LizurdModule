#pragma once
#include "BWAPI.h"
#include "Notification.h"
#include "Order.h"
#include <map>

namespace
{
	const std::string UnitDiscoveryCoord = "UnitDiscoveryCoordinator";
	const std::string WorkerCoord = "WorkerCoordinator";
}

class RaceDescriptor;
class Coordinator;

class Gateway
{
public:
	Gateway(void);
	~Gateway(void);

	void Initialise(BWAPI::Race race);
	bool Update();
	bool RegisterNotification(Notification &notification) const;
	RaceDescriptor &GetRaceDescriptor() const { return *_raceDescriptor; }

	void AddOrder(Order *order);

private:
	std::map<std::string, Coordinator*> _coordinators;
	std::vector<Order*> _orders;
	RaceDescriptor *_raceDescriptor;
};

