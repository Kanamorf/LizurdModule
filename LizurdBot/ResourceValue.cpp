#include "ResourceValue.h"

using namespace Lizurd;

bool ResourceValue::IsAffordable(const ResourceValue &cost) const
{
	bool isAffordable = false;
	if(Minerals >= cost.Minerals && Vespene >= cost.Vespene)
	{
		if(Supply + cost.Supply >= MaxSupply)
		{
			isAffordable = true;
		}
	}
	return isAffordable;
}
