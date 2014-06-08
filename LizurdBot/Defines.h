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
			GetNextConstructionGoal
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

	struct ResourceValue
	{
		ResourceValue(int mineral, int vespene, int supply, int maxSupply): Minerals(mineral), Supply(supply), Vespene(vespene), MaxSupply(maxSupply){}
		ResourceValue(int mineral, int vespene, int supply): Minerals(mineral), Supply(supply), Vespene(vespene), MaxSupply(0){}
		ResourceValue(): Minerals(0), Supply(0), Vespene(0), MaxSupply(0){}
		int Minerals;
		int Supply;
		int Vespene;
		int MaxSupply;
		inline bool operator==( const ResourceValue &other ) { return Minerals == other.Minerals && Supply == other.Supply && Vespene == other.Vespene; };
		inline bool operator>=( const ResourceValue &other ) { return Minerals >= other.Minerals && Supply >= other.Supply && Vespene >= other.Vespene; };
		inline bool operator>( const ResourceValue &other ) { return Minerals > other.Minerals || Supply > other.Supply || Vespene > other.Vespene; };
		inline bool operator<( const ResourceValue &other ) { return !operator>=(other); };
		inline bool operator<=( const ResourceValue &other ) { return !operator>(other); };
		inline bool operator!=( const ResourceValue &other ){ return !operator==(other); };

		inline ResourceValue operator+( const ResourceValue &other ) 
		{ 
			int minerals = Minerals + other.Minerals; 
			int vespene = Vespene + other.Vespene;
			int supply = Supply + other.Supply;
			int maxSupply = MaxSupply + other.MaxSupply;
			return ResourceValue(minerals, vespene, supply, maxSupply);  
		};
		inline ResourceValue operator+( const ResourceValue &other ) const
		{ 
			int minerals = Minerals + other.Minerals; 
			int vespene = Vespene + other.Vespene;
			int supply = Supply + other.Supply;
			int maxSupply = MaxSupply + other.MaxSupply;
			return ResourceValue(minerals, vespene, supply, maxSupply);  
		};
		inline ResourceValue operator-=( const ResourceValue &other ) { *this = *this - other; return *this; };
		inline ResourceValue operator-( const ResourceValue &other ) 
		{
			int minerals = Minerals - other.Minerals; 
			int vespene = Vespene - other.Vespene;
			int supply = Supply - other.Supply;
			int maxSupply = MaxSupply - other.MaxSupply;
			return ResourceValue(minerals, vespene, supply, maxSupply); 
		};
		inline ResourceValue operator-( const ResourceValue &other ) const
		{
			int minerals = Minerals - other.Minerals; 
			int vespene = Vespene - other.Vespene;
			int supply = Supply - other.Supply;
			int maxSupply = MaxSupply - other.MaxSupply;
			return ResourceValue(minerals, vespene, supply, maxSupply); 
		};
		inline ResourceValue operator+=( const ResourceValue &other ) { *this = *this + other; return *this; };
		static ResourceValue Zero() { return ResourceValue(0, 0, 0, 0); };
	};


}