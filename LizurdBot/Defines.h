#pragma once
#include "TypeSafeEnum.h"


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
		ResourceUpdate,
		ResourceRequest,
		ResourceRelease,
		CurrentResources
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

typedef TypeSafeEnum<TaskPriorityDef> TaskPriority;
typedef TypeSafeEnum<ActionDef> Action;
typedef TypeSafeEnum<ResultDef> Result;

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
	inline bool operator>=( const ResourceValue &other ) { return Minerals >= other.Minerals && MaxSupply >= other.Supply + Supply && Vespene >= other.Vespene; };
	inline bool operator>( const ResourceValue &other ) { return Minerals > other.Minerals && MaxSupply > other.Supply + Supply && Vespene > other.Vespene; };
	inline bool operator<( const ResourceValue &other ) { return !operator>=(other); };
	inline bool operator<=( const ResourceValue &other ) { return !operator>(other); };
	inline bool operator!=( const ResourceValue &other ){ return !operator==(other); };

	inline ResourceValue operator+=( const ResourceValue &other ) {return ResourceValue(Minerals += other.Minerals, Vespene += other.Vespene, Supply += other.Supply, MaxSupply += other.MaxSupply); };
	inline ResourceValue operator-=( const ResourceValue &other ) {return ResourceValue(Minerals -= other.Minerals, Vespene -= other.Vespene, Supply -= other.Supply, MaxSupply -= other.MaxSupply); };
	inline ResourceValue operator-( const ResourceValue &other ) {return ResourceValue(Minerals - other.Minerals, Vespene - other.Vespene, Supply -other.Supply, MaxSupply - other.MaxSupply); };
	inline ResourceValue operator-( const ResourceValue &other ) const {return ResourceValue(Minerals - other.Minerals, Vespene - other.Vespene, Supply -other.Supply, MaxSupply - other.MaxSupply); };
	inline ResourceValue operator+( const ResourceValue &other ) {return ResourceValue(Minerals + other.Minerals, Vespene + other.Vespene, Supply + other.Supply, MaxSupply + other.MaxSupply); };
	inline ResourceValue operator+( const ResourceValue &other ) const {return ResourceValue(Minerals + other.Minerals, Vespene + other.Vespene, Supply + other.Supply, MaxSupply + other.MaxSupply); };
	static ResourceValue Zero() { return ResourceValue(0, 0, 0, 0); };
};
