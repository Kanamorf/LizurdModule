/*

The MIT License

Copyright (c) <year> <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
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

Taken from the BWSAL (Broodwar Standard Addon library): http://code.google.com/p/bwsal/ .

*/


#pragma once
#include <BWAPI.h>
#include "RectangleArray.h"

namespace Lizurd
{

	class BuildingPlacer 
	{
	public:

		bool canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type) const;
		bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type) const;
		bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const;
		BWAPI::TilePosition getBuildLocation(BWAPI::UnitType type) const;
		BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position,BWAPI::UnitType type) const;
		BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position,BWAPI::UnitType type, int buildDist) const;
		void reserveTiles(BWAPI::TilePosition position, int width, int height);
		void freeTiles(BWAPI::TilePosition position, int width, int height);
		void setBuildDistance(int distance);
		int getBuildDistance() const;
		bool isReserved(int x, int y) const;
		static BuildingPlacer& GetInstance();

	private:	
		static BuildingPlacer* _instance;
		static void CleanUp();
		BuildingPlacer();
		Util::RectangleArray<bool> reserveMap;
		int buildDistance;
	};

}