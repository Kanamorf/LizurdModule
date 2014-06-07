#pragma once
#include "Base.h"
#include "Defines.h"
#include <BWAPI.h>

namespace Lizurd
{
	class Goal;
	typedef std::vector<Goal*> GoalVector;
	typedef std::map<BWAPI::UnitType, GoalVector> GoalMap;
	typedef std::pair<BWAPI::UnitType, Goal*> GoalMapPair;

	class Goal
	{
	public:
		Goal(GoalType type, GoalState state);
		Goal(GoalType type, GoalState state, float ratio);
		Goal(GoalType type, GoalState state, float ratio, int total);
		virtual ~Goal(void);
		BWAPI::Unit GetUnit();
		GoalType GetGoalType() const;
		GoalState GetState() const;
		float GetRatio() const { return _ratio; }

	private:
		GoalType _goalType;
		GoalState _goalState;
		float _ratio;
		int _total;
	};
}