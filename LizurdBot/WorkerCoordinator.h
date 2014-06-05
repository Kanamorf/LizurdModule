#pragma once
#include "Coordinator.h"

class WorkerCoordinator :
	public Coordinator
{
public:
	WorkerCoordinator(Gateway &gateway);
	~WorkerCoordinator(void);

	virtual bool ProcessNotification(Notification &notification) override;

	virtual bool UpdateInternal() override;
	virtual bool AfterUpdateInternal() override;

private:
	void RegisterWorker(Notification &notification);
	void DeRegisterWorker(Notification &notification);


	std::vector<BWAPI::Unit> _workers;
};

