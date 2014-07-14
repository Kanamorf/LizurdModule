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
	const std::string StrategyCoord = "StrategyCoordinator";
	const std::string ProductionCoord = "ProductionCoordinator";
	const std::string SquadCoord = "SquadCoordinator";
	const std::string ConstructionCoord = "ConstructionCoordinator";
}


namespace Lizurd
{

	class RaceDescriptor;
	class Coordinator;

	class Gateway
	{
	public:

		//Only one Logger so don't copy
		Gateway(const Gateway& gateway) {}         
		Gateway& operator=(const Gateway&);      
		static Gateway& GetInstance();
		

		Result Initialise(BWAPI::Game *game, BWAPI::Race race);
		Result Update(int frameNo);
		Result RegisterNotification(Notification &notification) const;
		RaceDescriptor &GetRaceDescriptor() const { return *_raceDescriptor; }
		void DrawDebugInfo();
		void AddOrder(Order *order);

	private:
		Gateway(void);
		~Gateway(void);
		// GetGame is private as nothing apart from the gateway should be talking to the game.
		BWAPI::Game &GetGame() const { return *_game; }

	private:
		std::map<Coordinators, Coordinator*> _coordinators;
		std::vector<Order*> _orders;
		RaceDescriptor *_raceDescriptor;
		BWAPI::Game *_game;
		static Gateway* _instance;
		Coordinator *_strategyCoordinator;
	};

}