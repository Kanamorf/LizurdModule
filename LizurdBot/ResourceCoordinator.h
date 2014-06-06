#pragma once
#include "coordinator.h"
class ResourceCoordinator :
	public Coordinator
{
public:
	ResourceCoordinator(Gateway &gateway);
	~ResourceCoordinator(void);

	virtual bool ProcessNotificationInternal(Notification &notification) override;
	virtual bool UpdateInternal() override;
	virtual bool AfterUpdateInternal() override;

	ResourceValue GetCurrentResources() const;

private:
	ResourceValue _resources;
};

