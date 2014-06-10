#pragma once
#include "building.h"
namespace Lizurd
{
	class TerranCommandCentre :
		public Building
	{
	public:
		TerranCommandCentre(BWAPI::Unit building, Base *base);
		~TerranCommandCentre(void);
	};
}