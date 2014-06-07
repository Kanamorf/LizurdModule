#pragma once
#include "coordinator.h"
class ResourceCoordinator :
	public Coordinator
{
public:
	ResourceCoordinator(Gateway &gateway);
	~ResourceCoordinator(void);

	virtual Result ProcessNotificationInternal(Notification &notification) override;
	virtual Result UpdateInternal() override;
	virtual Result AfterUpdateInternal() override;

	ResourceValue GetCurrentResources() const;

private:

	Result RequestResources(ResourceValue value);
	Result ReleaseResources(ResourceValue value);

private:
	ResourceValue _totalResources;
	ResourceValue _reservedResources;
};
