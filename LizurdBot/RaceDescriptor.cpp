#include "RaceDescriptor.h"


RaceDescriptor::RaceDescriptor()
{
}


RaceDescriptor::~RaceDescriptor(void)
{
}

/// <summary>
/// Gets the instance.
/// </summary>
/// <returns>The instance of the logger class</returns>
RaceDescriptor& RaceDescriptor::GetInstance()
{
	if(_instance == 0)
	{
		_instance = new RaceDescriptor();
	}
	return *_instance;
}

void RaceDescriptor::Initialise(BWAPI::Race race)
{
	_race = race;
	if(_race == BWAPI::Races::Zerg)
	{
		_commandCentre = BWAPI::UnitTypes::Zerg_Hatchery;
		_worker = BWAPI::UnitTypes::Zerg_Drone;
	}
	else if(_race == BWAPI::Races::Terran)
	{
		_commandCentre = BWAPI::UnitTypes::Terran_Command_Center;
		_worker = BWAPI::UnitTypes::Terran_SCV;
	}
	else if(_race == BWAPI::Races::Protoss)
	{
		_commandCentre = BWAPI::UnitTypes::Protoss_Nexus;
		_worker = BWAPI::UnitTypes::Protoss_Scout;
	}
}

/// <summary>
/// Cleans up.
/// </summary>
void RaceDescriptor::CleanUp()
{
	delete _instance; 
	_instance = 0;
}