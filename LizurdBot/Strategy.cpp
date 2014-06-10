#include "Strategy.h"
#include "Logger.h"
#include <sstream>

using namespace Lizurd;

Strategy::Strategy(void)
{
}


Strategy::~Strategy(void)
{
}


void Strategy::AddOrUpdate(const StrategyType &type, Goal *add)
{
	Logger::GetInstance().Log("Strategy", "AddOrUpdate");
	GoalQueue *pGoalQueue = nullptr;
	switch(type.Underlying())
	{
	case StrategyType::BuildingStrategy :
		pGoalQueue = &_buildingStrategy;
		break;
	case StrategyType::UnitStrategy :
		pGoalQueue = &_unitStrategy;
		break;
	case StrategyType::UpgrateStrategy :
		pGoalQueue = &_upgrateStrategy;
		break;
	}

	if(add != nullptr)
	{
		if(add->GetState() == GoalState::Extend)
		{
			pGoalQueue->emplace(add);
		}
		else if(add->GetState() == GoalState::Replace)
		{
			// first off empty the container
			while(!pGoalQueue->empty())
			{
				Goal* goal = pGoalQueue->front();
				pGoalQueue->pop();
				if(goal)
				{
					delete goal;
					goal = nullptr;
				}
			}
			pGoalQueue->emplace(add);
		}
	}

}

Goal* Strategy::GetNextUnitGoal()
{
	Goal* goal = nullptr;
	if(_unitStrategy.size() > 0)
	{
		goal = _unitStrategy.front();
		_unitStrategy.pop();
	}
	return goal;
}

Goal* Strategy::GetNextBuildingGoal()
{
	Goal* goal = nullptr;
	if(_buildingStrategy.size() > 0)
	{
		goal = _buildingStrategy.front();
		_buildingStrategy.pop();
	}
	return goal;
}

