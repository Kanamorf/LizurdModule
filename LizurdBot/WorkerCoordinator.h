#pragma once
#include "Coordinator.h"

class WorkerCoordinator :
	public Coordinator
{
public:
	WorkerCoordinator(Gateway &gateway);
	~WorkerCoordinator(void);

	virtual Result ProcessNotificationInternal(Notification &notification) override;
	virtual Result UpdateInternal() override;
	virtual Result AfterUpdateInternal() override;

private:
	void RegisterWorker(Notification &notification);
	void DeRegisterWorker(Notification &notification);


	std::vector<BWAPI::Unit> _workers;
};

