#pragma once
#include "Coordinator.h"


class UnitDiscoveryCoordinator : public Coordinator
{
public:
	UnitDiscoveryCoordinator(Gateway &gateway);
	~UnitDiscoveryCoordinator(void);

	
	virtual bool ProcessNotificationInternal(Notification &notification) override;

	virtual bool UpdateInternal() override;
	virtual bool AfterUpdateInternal() override;

private:
	void RegisterUnit(Notification &notification);
	void DeRegisterUnit(Notification &notification);
	

private:
	std::vector<BWAPI::Unit> _commandCentres;
	std::vector<BWAPI::Unit> _localUnits;
	std::vector<BWAPI::Unit> _localBuildings;
};

