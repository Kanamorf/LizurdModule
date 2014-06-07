#pragma once
#include "RaceDescriptor.h"
class ZergDescriptor :
	public RaceDescriptor
{
public:
	ZergDescriptor(void);
	~ZergDescriptor(void);
	virtual BWAPI::UnitType GetCommandCenterType() const override { return BWAPI::UnitTypes::Zerg_Hive; }
	virtual BWAPI::UnitType GetWorkerType() const override  { return BWAPI::UnitTypes::Zerg_Drone; }
	virtual Building& GetNewCommandCenter(BWAPI::Unit unit) override;
};

