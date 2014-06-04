#pragma once
#include "Coordinator.h"

class WorkerCoordinator :
	public Coordinator
{
public:
	WorkerCoordinator(Gateway &gateway);
	~WorkerCoordinator(void);
};

