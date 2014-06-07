#pragma once
#include "Order.h"

namespace Lizurd
{

	class ProductionOrder :
		public Order
	{
	public:
		ProductionOrder(std::string name, TaskPriority priority);
		ProductionOrder(std::string name, BWAPI::Unit executor, TaskPriority priority);
		~ProductionOrder(void);

		virtual bool IsReady() const override;
		virtual bool Execute() override;
		BWAPI::UnitType GetResultUnit() const { return _result; };
		void SetResultUnit(const BWAPI::UnitType &result) { _result = result; }

	private:
		BWAPI::UnitType _result;
	};

}