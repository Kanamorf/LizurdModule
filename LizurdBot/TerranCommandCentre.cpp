#include "TerranCommandCentre.h"

using namespace Lizurd;

TerranCommandCentre::TerranCommandCentre(BWAPI::Unit building, Base &base):
	Building(building, base, ResourceValue(300, 0, 0), TerranCommandCentreName)
{
}


TerranCommandCentre::~TerranCommandCentre(void)
{
}
