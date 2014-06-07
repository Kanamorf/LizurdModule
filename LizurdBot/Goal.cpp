#include "Goal.h"

using namespace Lizurd;

Goal::Goal(GoalType type, GoalState state):
	_goalState(state), _goalType(type), _ratio(1)
{
}

Goal::Goal( GoalType type, GoalState state, float ratio ):
	_goalState(state), _goalType(type), _ratio(ratio)
{

}

Goal::Goal(GoalType type, GoalState state, float ratio, int total):
	_goalState(state), _goalType(type), _ratio(ratio), _total(total)
{
}

Goal::~Goal(void)
{
}

GoalType Goal::GetGoalType() const
{
	return _goalType;
}

GoalState Goal::GetState() const
{
	return _goalState;
}



