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
		void AddOrUpdate(const StrategyType &type, const GoalMapPair &add);
	private:
		std::string _name;
		GoalMap _buildingStrategy;
		GoalMap _unitStrategy;
		GoalMap _upgrateStrategy;
		
	};
}