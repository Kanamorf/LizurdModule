#pragma once
#include "Building.h"



class ZergHatchery :
	public Building
{
public:
	ZergHatchery(BWAPI::Unit building, Base &base);
	~ZergHatchery(void);

	virtual Order* ProduceUnit(BWAPI::UnitType type)  override;
	virtual bool IsOkToBuild() const override;
	virtual BWAPI::UnitType GetType() const override;
	virtual Order* CreateBuildOrder(BWAPI::TilePosition position) override;
	virtual bool CanBuild(BWAPI::UnitType type) override;
};

