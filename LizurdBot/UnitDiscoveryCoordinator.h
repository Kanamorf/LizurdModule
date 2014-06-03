#pragma once
#include "Defines.h"
#include "Coordinator.h"


class UnitDiscoveryCoordinator : public Coordinator
{
public:
	UnitDiscoveryCoordinator(void);
	~UnitDiscoveryCoordinator(void);

	void RegisterUnit(BWAPI::Unit unit);
	virtual Status ProcessNotification(const Notification *pNotification) const override;

private:

	std::vector<BWAPI::Unit> _commandCentres;
	std::vector<BWAPI::Unit> _localUnits;
	std::vector<BWAPI::Unit> _localBuildings;
};

