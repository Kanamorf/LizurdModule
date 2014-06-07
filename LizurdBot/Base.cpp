#include "Base.h"

#include "Building.h"

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
			UnitVector units;
			units.push_back(unit);
			_unitMap.insert(make_pair(unit->getType(),units));
		}
		else 
		{
			it->second.push_back(unit);
		}
		success = true;
	}
	return success;
}


void Base::DrawDebugInfo()
{
	int x = -50;
	int y = -60;
	BWAPI::Color playerColor = BWAPI::Broodwar->self()->getColor();
	BWAPI::Broodwar->drawCircleMap(_commandCentre->GetPosition().x, _commandCentre->GetPosition().y, 80, playerColor);
	if(_buildingMap.size() > 0)
	{
		int count = 0;
		for(BuildingMap::const_iterator it = _buildingMap.begin(); it != _buildingMap.end(); ++it)
		{
			count += (*it).second.size();
		}
		BWAPI::Broodwar->drawTextMap(_commandCentre->GetPosition().x+x, _commandCentre->GetPosition().y+y, "Buildings: %u", count);
		y += 10;
	}
	if(_unitMap.size() > 0)
	{
		int count = 0;
		for(UnitMap::const_iterator it = _unitMap.begin(); it != _unitMap.end(); ++it)
		{
			count += (*it).second.size();
			for(UnitVector::const_iterator u = (*it).second.begin(); u != (*it).second.end(); ++u)
			{
				BWAPI::Broodwar->drawCircleMap((*u)->getPosition().x -3, (*u)->getPosition().y-3, 20, playerColor);
				BWAPI::Broodwar->drawLineMap((*u)->getPosition().x, (*u)->getPosition().y, _commandCentre->GetPosition().x, _commandCentre->GetPosition().y, playerColor);
			}

		}
		BWAPI::Broodwar->drawTextMap(_commandCentre->GetPosition().x+x, _commandCentre->GetPosition().y+y, "Units: %u", count);
	}

}