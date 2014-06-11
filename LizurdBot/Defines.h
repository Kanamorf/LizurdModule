#pragma once
#include "TypeSafeEnum.h"
#include "BWAPI.h"
#include <queue>

namespace Lizurd
{
	class Goal;
	typedef std::queue<Goal*> GoalQueue;

	struct TaskPriorityDef
	{
		enum type
		{
			High,
			Gather,
			Medium,
			Low
		};
	};
	struct CoordinatorDef
	{
		enum type
		{
			ResourceCoordinator,
			ConstructionCoordinator,
			ProductionCoordinator,
			WorkerCoordinator,
			UnitDiscoveryCoordinator,
			StrategyCoordinator
		};
	};
	struct ActionDef
	{
		enum type
		{
			None,
			RegisterUnit,
			DeRegisterUnit,
			MorphUnit,
			ResourceUpdate,
			RequestIdleUnit,
			ResourceRequest,
			ResourceRelease,
			CurrentResources,
			GetNextProductionGoal,
			GetNextConstructionGoal,
			NewBuildingFinished
		};
	};

	struct ResultDef
	{
		enum type
		{
			Failure,
			Success,
			InsufficientResources,
			InsufficientReservedResources
		};
	};
	struct GoalStateDef
	{
		enum type
		{
			Replace, // Clear previous goals and replace with this
			Extend	//Add this goal to the current goal list
		};
	};
	struct GoalTypeDef
	{
		enum type
		{
			None,
			TrainWorker, 
			TrainZergling,
			TrainOverlord,

			BuildSpawningPool,
		};
	};
	typedef TypeSafeEnum<TaskPriorityDef> TaskPriority;
	typedef TypeSafeEnum<ActionDef> Action;
	typedef TypeSafeEnum<ResultDef> Result;
	typedef TypeSafeEnum<GoalStateDef> GoalState;
	typedef TypeSafeEnum<GoalTypeDef> GoalType;
	typedef TypeSafeEnum<CoordinatorDef> Coordinators;
}