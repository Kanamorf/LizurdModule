/*

The MIT License

Copyright (c) <year> <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sub license, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Taken from the BWSAL (Broodwar Standard Addon library): http://code.google.com/p/bwsal/ 

*/

#include "BuildingPlacer.h"

using Lizurd::BuildingPlacer;

BuildingPlacer* BuildingPlacer::_instance = 0;

BuildingPlacer::BuildingPlacer()
{
	reserveMap.resize(BWAPI::Broodwar->mapWidth(), BWAPI::Broodwar->mapHeight());
	reserveMap.setTo(false);
	this->buildDistance=1;
}
bool BuildingPlacer::canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type) const
{
	//returns true if we can build this type of unit here. Takes into account reserved tiles.
	if (!BWAPI::Broodwar->canBuildHere(position, type))
		return false;
	for(int x = position.x; x < position.x + type.tileWidth(); x++)
		for(int y = position.y; y < position.y + type.tileHeight(); y++)
			if (reserveMap[x][y])
				return false;
	return true;
}
bool BuildingPlacer::canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type) const
{
	return canBuildHereWithSpace(position,type,this->buildDistance);
}
bool BuildingPlacer::canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const
{
	//returns true if we can build this type of unit here with the specified amount of space.
	//space value is stored in this->buildDistance.

	//if we can't build here, we of course can't build here with space
	if (!this->canBuildHere(position, type))
		return false;

	int width=type.tileWidth();
	int height=type.tileHeight();

	//make sure we leave space for add-ons. These types of units can have addons:
	if (type==BWAPI::UnitTypes::Terran_Command_Center ||
		type==BWAPI::UnitTypes::Terran_Factory || 
		type==BWAPI::UnitTypes::Terran_Starport ||
		type==BWAPI::UnitTypes::Terran_Science_Facility)
	{
		width+=2;
	}
	int startx = position.x - buildDist;
	if (startx<0) return false;
	int starty = position.y - buildDist;
	if (starty<0) return false;
	int endx = position.x + width + buildDist;
	if (endx>BWAPI::Broodwar->mapWidth()) return false;
	int endy = position.y + height + buildDist;
	if (endy>BWAPI::Broodwar->mapHeight()) return false;

	if (!type.isRefinery())
	{
		for(int x = startx; x < endx; x++)
			for(int y = starty; y < endy; y++)
				if (!BWAPI::Broodwar->isBuildable(x, y, true) || reserveMap[x][y])
					return false;
	}

	/*if (position.x>3)
	{
		int startx2=startx-2;
		if (startx2<0) startx2=0;
		for(int x = startx2; x < startx; x++)
			for(int y = starty; y < endy; y++)
			{
				BWAPI::Unitset units = BWAPI::Broodwar->getUnitsOnTile(x, y);
				for(BWAPI::Unitset::iterator i = units.begin(); i != units.end(); i++)
				{
					if (!(*i)->isLifted())
					{
						BWAPI::UnitType type=(*i)->getType();
						if (type==BWAPI::UnitTypes::Terran_Command_Center ||
							type==BWAPI::UnitTypes::Terran_Factory || 
							type==BWAPI::UnitTypes::Terran_Starport ||
							type==BWAPI::UnitTypes::Terran_Science_Facility)
						{
							return false;
						}
					}
				}
			}
	}*/
	return true;
}
BWAPI::TilePosition BuildingPlacer::getBuildLocation(BWAPI::UnitType type) const
{
	//returns a valid build location if one exists, scans the map left to right
	for(int x = 0; x < BWAPI::Broodwar->mapWidth(); x++)
		for(int y = 0; y < BWAPI::Broodwar->mapHeight(); y++)
			if (this->canBuildHere(BWAPI::TilePosition(x, y), type))
				return BWAPI::TilePosition(x, y);
	return BWAPI::TilePositions::None;
}

BWAPI::TilePosition BuildingPlacer::getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type) const
{
	return getBuildLocationNear(position, type,this->buildDistance);
}

BWAPI::TilePosition BuildingPlacer::getBuildLocationNear(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const
{
	//returns a valid build location near the specified tile position.
	//searches outward in a spiral.
	int x      = position.x;
	int y      = position.y;
	int length = 1;
	int j      = 0;
	bool first = true;
	int dx     = 0;
	int dy     = 1;
	while (length < BWAPI::Broodwar->mapWidth()) //We'll ride the spiral to the end
	{
		//if we can build here, return this tile position
		if (x >= 0 && x < BWAPI::Broodwar->mapWidth() && y >= 0 && y < BWAPI::Broodwar->mapHeight())
			if (this->canBuildHereWithSpace(BWAPI::TilePosition(x, y), type, buildDist))
				return BWAPI::TilePosition(x, y);

		//otherwise, move to another position
		x = x + dx;
		y = y + dy;
		//count how many steps we take in this direction
		j++;
		if (j == length) //if we've reached the end, its time to turn
		{
			//reset step counter
			j = 0;

			//Spiral out. Keep going.
			if (!first)
				length++; //increment step counter if needed

			//first=true for every other turn so we spiral out at the right rate
			first =! first;

			//turn counter clockwise 90 degrees:
			if (dx == 0)
			{
				dx = dy;
				dy = 0;
			}
			else
			{
				dy = -dx;
				dx = 0;
			}
		}
		//Spiral out. Keep going.
	}
	return BWAPI::TilePositions::None;
}


void BuildingPlacer::reserveTiles(BWAPI::TilePosition position, int width, int height)
{
	for(int x = position.x; x < position.x + width && x < (int)reserveMap.getWidth(); x++)
		for(int y = position.y; y < position.y + height && y < (int)reserveMap.getHeight(); y++)
			reserveMap[x][y] = true;
}

void BuildingPlacer::freeTiles(BWAPI::TilePosition position, int width, int height)
{
	for(int x = position.x; x < position.x + width && x < (int)reserveMap.getWidth(); x++)
		for(int y = position.y; y < position.y + height && y < (int)reserveMap.getHeight(); y++)
			reserveMap[x][y] = false;
}

void BuildingPlacer::setBuildDistance(int distance)
{
	this->buildDistance=distance;
}
int BuildingPlacer::getBuildDistance() const
{
	return this->buildDistance;
}
bool BuildingPlacer::isReserved(int x, int y) const
{
	if (x<0 || y<0 || x>=(int)reserveMap.getWidth() || y>=(int)reserveMap.getHeight())
		return false;
	return reserveMap[x][y];
}

BuildingPlacer& BuildingPlacer::GetInstance()
{
	if(_instance == 0)
	{
		_instance = new BuildingPlacer();
	}
	return *_instance;
}
/// <summary>
/// Cleans up.
/// </summary>
void BuildingPlacer::CleanUp()
{
	delete _instance; 
	_instance = 0;
}