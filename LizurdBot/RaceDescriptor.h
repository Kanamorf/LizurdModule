#pragma once
#include "BWAPI.h"

class RaceDescriptor
{
public:

	RaceDescriptor();
	virtual ~RaceDescriptor(void);
	virtual BWAPI::UnitType GetCommandCenterType() const = 0;
	virtual BWAPI::UnitType GetWorkerType() const = 0;

private:

	BWAPI::Race _race;
};

