#pragma once
#include "Building.h"

namespace Lizurd
{
	class ZergHydraliskDen :
		public Building
	{
	public:
		ZergHydraliskDen(BWAPI::Unit building);
		ZergHydraliskDen(BWAPI::Unit building, Base* base);
		~ZergHydraliskDen(void);

		virtual Order* ProduceUnit(BWAPI::UnitType type)  override;
		virtual bool IsOkToBuild() const override;
		virtual BWAPI::UnitType GetType() const override;
		virtual Order* CreateBuildOrder(BWAPI::TilePosition position) override;
		virtual bool CanBuild(BWAPI::UnitType type) override;
	};
}