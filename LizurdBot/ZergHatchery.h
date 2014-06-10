#pragma once
#include "Building.h"

namespace Lizurd
{

	class ZergHatchery :
		public Building
	{
	public:
		ZergHatchery(BWAPI::Unit building);
		ZergHatchery(BWAPI::Unit building, Base *base);
		~ZergHatchery(void);

		virtual Order* ProduceUnit(BWAPI::UnitType type)  override;
		virtual bool IsOkToBuild() const override;
		virtual BWAPI::UnitType GetType() const override;
		virtual Order* CreateBuildOrder(BWAPI::TilePosition position) override;
		virtual bool CanBuild(BWAPI::UnitType type) override;
		virtual Result Update(int frameNo) override;
	};

}