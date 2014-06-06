// The WorkerCoordinator is the only thing that keeps track of all of the
// worker units in the game. It will issue Orders to these workers so they 
// gather minerals and vespyne. Workers can be requested by other coordinators
// for example the BuildingCoordinator may need a worker to build a building,
// in this case the WorkerCoordinator will select a worker and pass control of
// if to the BuildingCoordinator for the life of the build order, at which point 
// control passes back to the WorkerCoordinator.


#include "WorkerCoordinator.h"
#include "GatherOrder.h"

WorkerCoordinator::WorkerCoordinator(Gateway &gateway) :
	Coordinator(gateway, WorkerCoord)
{
}


WorkerCoordinator::~WorkerCoordinator(void)
{
}

Result WorkerCoordinator::UpdateInternal()
{ 
	for(std::vector<BWAPI::Unit>::iterator it = _workers.begin(); it != _workers.end(); ++it)
	{
		if((*it)->isIdle())
		{
			GatherOrder *order = new GatherOrder(*it);
			_gateway.AddOrder(order);
		}
	}
	return Result::Success;
}

Result WorkerCoordinator::AfterUpdateInternal()
{
	return Result::Failure;
}

Result WorkerCoordinator::ProcessNotificationInternal(Notification &notification)
{
	Result retVal = Result::Failure;
	if(notification.size() == 1)
	{
		if(notification.GetAction() == Action::RegisterUnit)
		{
			RegisterWorker(notification);
			retVal = Result::Success;
		}
		else if(notification.GetAction() == Action::DeRegisterUnit)
		{
			DeRegisterWorker(notification);
			retVal = Result::Success;
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