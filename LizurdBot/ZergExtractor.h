#pragma once
#include "building.h"

namespace Lizurd
{
	class ZergExtractor:
		public Building
	{
	public:
		ZergExtractor(BWAPI::Unit building);
		ZergExtractor(BWAPI::Unit building, Base* base);
		~ZergExtractor(void);

		virtual Order* ProduceUnit(BWAPI::UnitType type)  override;
		virtual bool IsOkToBuild() const override;
		virtual BWAPI::UnitType GetType() const override;
		virtual Order* CreateBuildOrder(BWAPI::TilePosition position) override;
		virtual bool CanBuild(BWAPI::UnitType type) override;
	};
}