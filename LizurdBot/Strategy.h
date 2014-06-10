#pragma once
#include <string>
#include "Goal.h"
#include "Defines.h"

namespace Lizurd
{
	struct StrategyTypeDef
	{
		enum type
		{
			BuildingStrategy,
			UnitStrategy, 
			TrainZergling,
			UpgrateStrategy
		};
	};
	typedef TypeSafeEnum<StrategyTypeDef> StrategyType; 

	class Strategy
	{
	public:
		Strategy(void);
		~Strategy(void);

		void SetName(std::string name) { _name = name; }
		void AddOrUpdate(const StrategyType &type, Goal* add);
		Goal* GetNextUnitGoal();
		Goal* GetNextBuildingGoal();
		bool UnitGoalIsEmpty() const { return _unitStrategy.empty(); }
		bool BuildingGoalIsEmpty() const { return _buildingStrategy.empty(); }
	private:
		std::string _name;
		GoalQueue _buildingStrategy;
		GoalQueue _unitStrategy;
		GoalQueue _upgrateStrategy;
		
		
	};
}