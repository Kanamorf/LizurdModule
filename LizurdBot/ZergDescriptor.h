#pragma once
#include "RaceDescriptor.h"
class ZergDescriptor :
	public RaceDescriptor
{
public:
	ZergDescriptor(void);
	~ZergDescriptor(void);
	virtual BWAPI::UnitType GetCommandCenterType() const { return BWAPI::UnitTypes::Zerg_Hive; }
	virtual BWAPI::UnitType GetWorkerType() const  { return BWAPI::UnitTypes::Zerg_Drone; }
};

