#pragma once
#include "Coordinator.h"


class UnitDiscoveryCoordinator : public Coordinator
{
public:
	UnitDiscoveryCoordinator(Gateway &gateway);
	~UnitDiscoveryCoordinator(void);

	
	virtual Result ProcessNotificationInternal(Notification &notification) override;
	virtual Result UpdateInternal() override;
	virtual Result AfterUpdateInternal() override;

private:
	void RegisterUnit(Notification &notification);
	void DeRegisterUnit(Notification &notification);
	

private:
	std::vector<BWAPI::Unit> _commandCentres;
	std::vector<BWAPI::Unit> _localUnits;
	std::vector<BWAPI::Unit> _localBuildings;
};

