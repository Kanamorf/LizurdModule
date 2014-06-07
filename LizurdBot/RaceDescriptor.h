#pragma once
#include <vector>
#include "BWAPI.h"
#include "Building.h"

class RaceDescriptor
{
public:

	RaceDescriptor();
	virtual ~RaceDescriptor(void);
	virtual BWAPI::UnitType GetCommandCenterType() const = 0;
	virtual Building& GetNewCommandCenter(BWAPI::Unit unit) = 0;
	virtual BWAPI::UnitType GetWorkerType() const = 0;

protected:
	std::vector<Building*> _buildings;
};

