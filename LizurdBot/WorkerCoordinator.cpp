// The WorkerCoordinator is the only thing that keeps track of all of the
// worker units in the game. It will issue Orders to these workers so they 
// gather minerals and vespyne. Workers can be requested by other coordinators
// for example the BuildingCoordinator may need a worker to build a building,
// in this case the WorkerCoordinator will select a worker and pass control of
// if to the BuildingCoordinator for the life of the build order, at which point 
// control passes back to the WorkerCoordinator.


#include "WorkerCoordinator.h"
#include "GatherOrder.h"
#include "RaceDescriptor.h"
#include "GasOrder.h"

using namespace Lizurd;

WorkerCoordinator::WorkerCoordinator(Gateway &gateway) :
	Coordinator(gateway, WorkerCoord),
	_gatheringGas(0)
{
}


WorkerCoordinator::~WorkerCoordinator(void)
{
}

Result WorkerCoordinator::UpdateInternal(int frameNo)
{ 
	std::vector<BWAPI::Unit> morphedWorkers;
	for(std::vector<BWAPI::Unit>::iterator it = _workers.begin(); it != _workers.end(); ++it)
	{
		if(((*it)->getType() != _gateway.GetRaceDescriptor().GetWorkerType()))
		{
			// Zerg specific code is bad.....
			morphedWorkers.push_back(*it);
			continue;
		}
		if((*it)->isIdle())
		{
			GatherOrder *order = new GatherOrder(*it);
			_gateway.AddOrder(order);
		}
	}
	for(std::vector<BWAPI::Unit>::iterator it = morphedWorkers.begin(); it != morphedWorkers.end(); ++it)
	{
		VectorRemove(_workers, *it);
	}
	return Result::Success;
}

Result WorkerCoordinator::AfterUpdateInternal()
{
	if(_extractors.size() > 0 && _gatheringGas < _extractors.size() * 3)
	{
		Notification notification(Coordinators::WorkerCoordinator);
		FindIdleUnit(notification);
		GasOrder *order = new GasOrder(notification.GetLastUnit());		
		order->SetExtractor(_extractors[0]);
		_gateway.AddOrder(order);
		++_gatheringGas;
	}
	return Result::Success;
}

Result WorkerCoordinator::ProcessNotificationInternal(Notification &notification)
{
	Result retVal = Result::Failure;

	if(notification.GetAction() == Action::RegisterOwnUnit)
	{
		RegisterWorker(notification);
		retVal = Result::Success;
	}
	else if(notification.GetAction() == Action::DeRegisterUnit)
	{
		DeRegisterWorker(notification);
		retVal = Result::Success;
	}
	else if(notification.GetAction() == Action::RequestIdleUnit)
	{
		Logger::GetInstance().Log(GetName(), "Action::RequestIdleUnit");
		retVal = FindIdleUnit(notification);
	}
	else if(notification.GetAction() == Action::NewGasCollector)
	{
		Logger::GetInstance().Log(GetName(), "Action::NewGasCollector");
		ProcessNewGasCollector(notification);
	}
	return retVal;
}

/// <summary>
/// Registers the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
void WorkerCoordinator::RegisterWorker(Notification &notification)
{
	if(notification.UnitSize() == 1)
	{
		BWAPI::Unit unit = notification.GetLastUnit();
		Logger::GetInstance().Log(GetName(), "Registering unit: " + unit->getType().getName());

		if(unit->getType().isWorker())
		{
			_workers.push_back(unit);
		}
	}
}

/// <summary>
/// DeRegisters the unit in preparation for the next update.
/// </summary>
/// <param name="unit">The unit.</param>
void WorkerCoordinator::DeRegisterWorker(Notification &notification)
{
	if(notification.UnitSize() == 1)
	{
		BWAPI::Unit unit = notification.GetLastUnit();
		Logger::GetInstance().Log(GetName(), "DeRegistering unit: " + unit->getType().getName());
		VectorRemove(_workers, unit);
	}
}

Result WorkerCoordinator::FindIdleUnit(Notification &notification)
{
	Logger::GetInstance().Log(GetName(), "FindIdleUnit");
	Result retVal = Result::Failure;
	for(std::vector<BWAPI::Unit>::iterator it = _workers.begin(); it != _workers.end(); ++it)
	{
		if((*it)->isIdle())
		{
			Logger::GetInstance().Log(GetName(), "FindIdleUnit: Found Idle");
			notification.AddUnit(*it);
			retVal = Result::Success;
			break;
		}
	}
	// We didn't find an idle worker so grab any worker to do the job.
	// Prefer mineral miners over vespene
	if(retVal != Result::Success)
	{

		for(std::vector<BWAPI::Unit>::iterator it = _workers.begin(); it != _workers.end(); ++it)
		{
			if ((*it)->isGatheringMinerals())
			{
				Logger::GetInstance().Log(GetName(), "FindIdleUnit: Grabbing none idle");
				notification.AddUnit(*it);
				retVal = Result::Success;
				break;
			}
		}
	}
	return retVal;
}


void WorkerCoordinator::ProcessNewGasCollector(Notification &notification)
{
	BWAPI::Unit extractor = notification.GetLastUnit();
	if(extractor != nullptr)
	{
		FindIdleUnit(notification);
		BWAPI::Unit unit = notification.GetLastUnit();
		if(unit != nullptr)
		{
			GasOrder *order = new GasOrder(unit);
			order->SetExtractor(extractor);
			_gateway.AddOrder(order);
		}
		_extractors.push_back(extractor);
	}
}