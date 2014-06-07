#pragma once
#include "BWAPI.h"
#include "Defines.h"
#include "Base.h"
#include "Order.h"
#include "BuildingNames.h"


namespace Lizurd
{

	class Building
	{
	public:
		Building(BWAPI::Unit building, Base &base, ResourceValue cost, std::string name);
		~Building(void);

		BWAPI::Position GetPosition() const;
		BWAPI::TilePosition GetTilePosition() const;
		BWAPI::Player GetPlayer() const;
		int GetDistance(BWAPI::Unit unit) const;
		bool IsIdle() const;
		Base& GetParentBase() const { return _parentBase; }
		virtual Order* ProduceUnit(BWAPI::UnitType type) =0;
		virtual bool IsOkToBuild() const =0;
		virtual BWAPI::UnitType GetType() const = 0;
		virtual Order* CreateBuildOrder(BWAPI::TilePosition position) =0;
		virtual bool CanBuild(BWAPI::UnitType type) =0;

	private:

		BWAPI::Unit _building;
		Base &_parentBase;
		std::vector<BWAPI::UnitType> _preconditions;
		BWAPI::UnitType _type;
		unsigned int _quantityPerBase;
		std::string _name;
		ResourceValue _cost;
	};
}