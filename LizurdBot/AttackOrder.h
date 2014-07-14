#pragma once
#include "order.h"

namespace Lizurd
{
	class AttackOrder :
		public Order
	{
	public:
		AttackOrder(TaskPriority priority);
		~AttackOrder(void);
		void AddUnits(const BWAPI::Unitset &units);
		virtual bool Execute() override;
		void SetTarget(const BWAPI::Position &target) { _target = target; } 

	private:
		BWAPI::Unitset _units;
		BWAPI::Position _target;
	};
}