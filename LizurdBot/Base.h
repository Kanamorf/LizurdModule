#pragma once
#include "BWAPI.h"

#include <vector>
#include <set>

namespace Lizurd
{
	class Building;
	class RaceDescriptor;

	typedef std::vector<Building*> BuildingVector;
	typedef std::map<BWAPI::UnitType, BuildingVector*> BuildingMap;
	typedef std::vector<BWAPI::Unit> UnitVector;
	typedef std::map<BWAPI::UnitType, UnitVector*> UnitMap;


	class Base
	{
	public:
		Base(void);
		~Base(void);

		void Initialise();
		void SetCommandCentre(Building* commandCentre) { _commandCentre = commandCentre; }
		Building& GetCommandCentre() const { return *_commandCentre; }
		void DrawDebugInfo();
		bool AddUnit(BWAPI::Unit unit);
		bool AddBuilding(Building* building);
		bool RemoveUnit(BWAPI::Unit unit);
		void SetRaceDescriptor(RaceDescriptor *descriptor) { _descriptor = descriptor; }
		RaceDescriptor& GetRaceDescriptor() const { return *_descriptor; }
		BWAPI::Unit FindIdleUnit(const BWAPI::UnitType &type);
		BWAPI::Unit FindIdleBuilding(const BWAPI::UnitType &type);
		bool RemoveUnitByType(BWAPI::Unit unit);
		bool RemoveUnitByPointer(BWAPI::Unit unit);
		bool RemoveBuildingByPointer(const BWAPI::Unit unit);

	private:

		Building *_commandCentre;
		BuildingMap _buildingMap;
		UnitMap _unitMap;
		RaceDescriptor *_descriptor;
		BWAPI::Unitset _minerals;
		BWAPI::Unitset _geysers;
	};

}
