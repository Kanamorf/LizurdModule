#include "Base.h"
#include "RaceDescriptor.h"
#include "Building.h"
#include "Logger.h"

using Lizurd::Base;

Base::Base(void)
{
}


Base::~Base(void)
{
}

/// <summary>
/// Adds a unit to the base.
/// </summary>
/// <param name="unit">The unit.</param>
bool Base::AddUnit(BWAPI::Unit unit)
{
	bool success = false;
	if(unit->exists())
	{
		UnitMap::iterator it = _unitMap.find(unit->getType());
		if(it == _unitMap.end()) 
		{
			UnitVector *units = new UnitVector();
			units->push_back(unit);
			_unitMap.insert(make_pair(unit->getType(), units));
		}
		else 
		{
			it->second->push_back(unit);
		}
		success = true;
	}
	return success;
}


bool Lizurd::Base::AddBuilding(Building* building)
{
	bool success = false;
	if(building->GetUnit()->exists())
	{
		BuildingMap::iterator it = _buildingMap.find(building->GetUnit()->getType());
		if(it == _buildingMap.end()) 
		{
			BuildingVector *buildings = new BuildingVector();
			buildings->push_back(building);
			_buildingMap.insert(make_pair(building->GetUnit()->getType(), buildings));
		}
		else 
		{
			it->second->push_back(building);
		}
		success = true;
	}
	return success;
}


void Base::DrawDebugInfo()
{
	if(_commandCentre != nullptr)
	{
		int x = -50;
		int y = -60;
		BWAPI::Color playerColor = BWAPI::Broodwar->self()->getColor();
		BWAPI::Broodwar->drawCircleMap(_commandCentre->GetPosition().x, _commandCentre->GetPosition().y, 80, playerColor);
		if(_minerals.size() > 0)
		{
			int count = 0;
			for(BWAPI::Unitset::iterator it = _minerals.begin(); it != _minerals.end(); ++it)
			{
				BWAPI::Broodwar->drawCircleMap((*it)->getPosition().x -3, (*it)->getPosition().y-3, 20, playerColor);
				BWAPI::Broodwar->drawLineMap((*it)->getPosition().x, (*it)->getPosition().y, _commandCentre->GetPosition().x, _commandCentre->GetPosition().y, playerColor);
			}
			BWAPI::Broodwar->drawTextMap(_commandCentre->GetPosition().x+x, _commandCentre->GetPosition().y+y, "Buildings: %u", count);
			y += 10;
		}
		if(_buildingMap.size() > 0)
		{
			int count = 0;
			for(BuildingMap::const_iterator it = _buildingMap.begin(); it != _buildingMap.end(); ++it)
			{
				count += (*it).second->size();
				for(BuildingVector::const_iterator u = (*it).second->begin(); u != (*it).second->end(); ++u)
				{
					BWAPI::Broodwar->drawCircleMap((*u)->GetUnit()->getPosition().x -3, (*u)->GetUnit()->getPosition().y-3, 20, playerColor);
					BWAPI::Broodwar->drawLineMap((*u)->GetUnit()->getPosition().x, (*u)->GetUnit()->getPosition().y, _commandCentre->GetPosition().x, _commandCentre->GetPosition().y, playerColor);
				}
			}
			BWAPI::Broodwar->drawTextMap(_commandCentre->GetPosition().x+x, _commandCentre->GetPosition().y+y, "Buildings: %u", count);
			y += 10;
		}
		if(_unitMap.size() > 0)
		{
			int count = 0;
			for(UnitMap::const_iterator it = _unitMap.begin(); it != _unitMap.end(); ++it)
			{
				count += (*it).second->size();
				for(UnitVector::const_iterator u = (*it).second->begin(); u != (*it).second->end(); ++u)
				{
					BWAPI::Broodwar->drawCircleMap((*u)->getPosition().x -3, (*u)->getPosition().y-3, 20, playerColor);
					BWAPI::Broodwar->drawLineMap((*u)->getPosition().x, (*u)->getPosition().y, _commandCentre->GetPosition().x, _commandCentre->GetPosition().y, playerColor);
				}

			}
			BWAPI::Broodwar->drawTextMap(_commandCentre->GetPosition().x+x, _commandCentre->GetPosition().y+y, "Units: %u", count);
		}
	}
}

BWAPI::Unit Base::FindIdleUnit(const BWAPI::UnitType &type)
{
	Logger::GetInstance().Log("Base", "Looking for " + type.getName());
	BWAPI::Unit unit = FindIdleBuilding(type);
	if(unit == nullptr)
	{
		for(UnitMap::iterator it = _unitMap.begin(); it != _unitMap.end(); ++it)
		{
			if(type == it->first)
			{
				UnitVector *units = it->second;
				for(UnitVector::iterator itu = units->begin(); itu != units->end(); ++itu)
				{
					if((*itu) && (*itu)->isIdle())
					{
						unit = (*itu);
						break;
					}
				}
				if(unit != nullptr)
					break;
			}
		}
	}

	return unit;
}

BWAPI::Unit Base::FindIdleBuilding(const BWAPI::UnitType &type)
{
	BWAPI::Unit unit = nullptr;
	if(type.isBuilding())
	{
		if(_commandCentre != nullptr && type == _commandCentre->GetType())
		{
			if(_commandCentre->IsIdle())
				unit = _commandCentre->GetUnderLying();
		}
		else
		{
			for(BuildingMap::iterator it = _buildingMap.begin(); it != _buildingMap.end(); ++it)
			{
				if(type == it->first)
				{
					BuildingVector *buildings = it->second;
					for(BuildingVector::iterator building = buildings->begin(); building != buildings->end(); ++building)
					{
						if((*building) && (*building)->IsIdle())
						{
							unit = (*building)->GetUnderLying();
							break;
						}
					}
					if(unit != nullptr)
						break;
				}
			}
		}
	}	
	return unit;
}
/// <summary>
/// Remove the supplied unit from the base using its type as a clue to find it.
/// This is the faster of the two remove methods.
/// </summary>
/// <param name="unit">The unit to remove.</param>
bool Base::RemoveUnitByType(BWAPI::Unit unit)
{
	Logger::GetInstance().Log("Base", "RemoveUnitByType. Code not implemented yet.");
	return false;
}

/// <summary>
/// Remove the supplied unit from the base using its pointer to find it.
/// This remove method is used when a unit morphs...Its pointer stays the same
/// but its type will have changed
/// This is the slower of the two remove methods.
/// </summary>
/// <param name="unit">The unit to remove.</param>
bool Lizurd::Base::RemoveUnitByPointer(BWAPI::Unit unit)
{
	bool retVal = false;
	if(_commandCentre->GetUnderLying() == unit)
	{
		Logger::GetInstance().Log("Base", "Removing a command centre from a base by pointer.");
		delete _commandCentre;
		_commandCentre = nullptr;
		retVal = true;
	}
	else
	{
		// buildings first as there are likely to be less of them
		retVal = RemoveBuildingByPointer(unit);

		if(retVal == false)
		{
			for(UnitMap::iterator it = _unitMap.begin(); it != _unitMap.end(); ++it)
			{
				UnitVector *units = it->second;
				UnitVector::iterator found = units->end();
				for(UnitVector::iterator itu = units->begin(); itu != units->end(); ++itu)
				{
					if((*itu))
					{
						if(unit == (*itu))
						{
							found = itu;
							break;
						}
					}
				}
				if(found != units->end())
				{
					Logger::GetInstance().Log("Base", "Removing a unit from a base by pointer.");
					units->erase(found);
					retVal = true;
					break;
				}
			}
		}
	}
	return retVal;
}

void Base::Initialise()
{
	_minerals = _commandCentre->GetUnit()->getUnitsInRadius(1024, BWAPI::Filter::IsMineralField);
}

bool Base::RemoveBuildingByPointer(const BWAPI::Unit unit)
{
	bool success = false;
	for(BuildingMap::iterator it = _buildingMap.begin(); it != _buildingMap.end(); ++it)
	{
		BuildingVector *buildings = it->second;
		BuildingVector::iterator found = buildings->end();
		for(BuildingVector::iterator building = buildings->begin(); building != buildings->end(); ++building)
		{
			if((*building))
			{
				if(unit == (*building)->GetUnderLying())
				{
					found = building;
					break;
				}
			}
		}
		if(found != buildings->end())
		{
			Logger::GetInstance().Log("Base", "Removing a building from a base by pointer.");
			Building* building = *found;
			buildings->erase(found);
			delete building;
			building = nullptr;
			success = true;
			break;
		}
	}
	return success;
}