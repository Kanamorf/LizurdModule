#pragma once
#include "BWAPI.h"
#include "Notification.h"
#include "Order.h"
#include <map>

namespace
{
	const std::string UnitDiscoveryCoord = "UnitDiscoveryCoordinator";
	const std::string WorkerCoord = "WorkerCoordinator";
	const std::string ResourceCoord = "ResourceCoordinator";
}

class RaceDescriptor;
class Coordinator;

class Gateway
{
public:
	Gateway(void);
	~Gateway(void);

	Result Initialise(BWAPI::Game *game, BWAPI::Race race);
	Result Update();
	Result RegisterNotification(Notification &notification) const;
	RaceDescriptor &GetRaceDescriptor() const { return *_raceDescriptor; }
	void DrawDebugInfo();
	void AddOrder(Order *order);
	
private:

	// GetGame is private as nothing apart from the gateway should be talking to the game.
	BWAPI::Game &GetGame() const { return *_game; }

private:
	std::map<std::string, Coordinator*> _coordinators;
	std::vector<Order*> _orders;
	RaceDescriptor *_raceDescriptor;
	BWAPI::Game *_game;
};

