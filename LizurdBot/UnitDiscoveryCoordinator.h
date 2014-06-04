#pragma once
#include "Coordinator.h"


class UnitDiscoveryCoordinator : public Coordinator
{
public:
	UnitDiscoveryCoordinator(Gateway &gateway);
	~UnitDiscoveryCoordinator(void);

	
	virtual bool ProcessNotification(const Notification &notification) override;

	virtual bool UpdateInternal() override;
	virtual bool AfterUpdateInternal() override;

private:
	void RegisterUnit(BWAPI::Unit unit);

private:
	std::vector<BWAPI::Unit> _commandCentres;
	std::vector<BWAPI::Unit> _localUnits;
	std::vector<BWAPI::Unit> _localBuildings;
};

