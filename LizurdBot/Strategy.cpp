#include "Strategy.h"

using namespace Lizurd;

Strategy::Strategy(void)
{
}


Strategy::~Strategy(void)
{
}


void Strategy::AddOrUpdate(const StrategyType &type, const GoalMapPair &add)
{
	GoalMap *pGoalMap = nullptr;
	switch(type.Underlying())
	{
	case StrategyType::BuildingStrategy :
		pGoalMap = &_buildingStrategy;
		break;
	case StrategyType::UnitStrategy :
		pGoalMap = &_unitStrategy;
		break;
	case StrategyType::UpgrateStrategy :
		pGoalMap = &_upgrateStrategy;
		break;
	}

	GoalMap::iterator lb = pGoalMap->lower_bound(add.first);

	if(lb != pGoalMap->end() && !(pGoalMap->key_comp()(add.first, lb->first)))
	{
		// key already exists
		// update lb->second if you care to
		if((add.second)->GetState() == GoalState::Replace)
		{
			GoalVector vec;
			vec.push_back(add.second);
			(*pGoalMap)[add.first] = vec;
		}
		else
		{
			if(std::find((lb->second).begin(), (lb->second).end(), add.second) != (lb->second).end()) 
			{
				/* goalMap contains item */
			} 
			else 
			{
				(lb->second).push_back(add.second);
			}	
		}
	}
	else
	{
		// the key does not exist in the map
		// add it to the map
		GoalVector vec;
		vec.push_back(add.second);
		pGoalMap->insert(lb, GoalMap::value_type(add.first, vec));    // Use lb as a hint to insert,
		// so it can avoid another lookup
	}
}