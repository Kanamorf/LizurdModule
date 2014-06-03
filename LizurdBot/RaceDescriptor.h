#pragma once
#include "BWAPI.h"


class RaceDescriptor
{
public:
	//Only one Logger so dont copy
	RaceDescriptor(const RaceDescriptor& raceDescriptor) {}         
	RaceDescriptor& operator=(const RaceDescriptor&);   
	static RaceDescriptor& GetInstance();

	void Initialise(BWAPI::Race race);
	BWAPI::UnitType GetCommandCenterType() const { return _commandCentre; }
	BWAPI::UnitType GetWorkerType() const { return _worker; }

private:
	RaceDescriptor();
	~RaceDescriptor(void);
	static void CleanUp();

private:
	static RaceDescriptor* _instance;
	BWAPI::UnitType _commandCentre;
	BWAPI::UnitType _worker;
	BWAPI::Race _race;
};

