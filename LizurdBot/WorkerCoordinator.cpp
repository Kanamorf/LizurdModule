#include "WorkerCoordinator.h"
#include "GatherOrder.h"

WorkerCoordinator::WorkerCoordinator(Gateway &gateway) :
	Coordinator(gateway, WorkerCoord)
{
}


WorkerCoordinator::~WorkerCoordinator(void)
{
}

bool WorkerCoordinator::UpdateInternal()
{ 
	for(std::vector<BWAPI::Unit>::iterator it = _workers.begin(); it != _workers.end(); ++it)
	{
		if((*it)->isIdle())
		{
			GatherOrder *order = new GatherOrder(*it);
			_gateway.AddOrder(order);
		}
	}
	return true;
}

bool WorkerCoordinator::AfterUpdateInternal()
{
	return false;
}

bool WorkerCoordinator::ProcessNotification(Notification &notification)
{
	bool retVal = false;
	if(notification.size() == 1)
	{
		if(notification.GetAction() == Notification::Action::RegisterUnit)
		{
			RegisterWorker(notification);
			retVal = true;
		}
		else if(notification.GetAction() == Notification::Action::DeRegisterUnit)
		{
			DeRegisterWorker(notification);
			retVal = true;
		}
	}

	return retVal;
}

/// <summary>
/// Registers the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
void WorkerCoordinator::RegisterWorker(Notification &notification)
{
	BWAPI::Unit unit = notification.back();
	Logger::GetInstance().Log(GetName(), "Registering unit: " + unit->getType().getName());

		if(unit->getType().isWorker())
		{
			_workers.push_back(unit);
		}

}

/// <summary>
/// DeRegisters the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
void WorkerCoordinator::DeRegisterWorker(Notification &notification)
{
	BWAPI::Unit unit = notification.back();
	Logger::GetInstance().Log(GetName(), "DeRegistering unit: " + unit->getType().getName());
	VectorRemove(_workers, unit);
}