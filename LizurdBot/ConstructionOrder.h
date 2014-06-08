#pragma once
#include "order.h"

namespace Lizurd
{
	class ConstructionOrder :
		public Order
	{
	public:
		ConstructionOrder(std::string name, TaskPriority priority);
		ConstructionOrder(std::string name, BWAPI::Unit executor, TaskPriority priority);
		~ConstructionOrder(void);

		virtual bool IsReady() const override;
		virtual bool Execute() override;
		BWAPI::UnitType GetResultUnit() const { return _result; };
		void SetResultUnit(const BWAPI::UnitType &result) { _result = result; }
		void SetTilePosition(const BWAPI::TilePosition &position) { _position = position; }

	private:
		BWAPI::UnitType _result;
		BWAPI::TilePosition _position;
	};
}