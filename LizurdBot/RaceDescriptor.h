#pragma once
#include <vector>
#include "BWAPI.h"


namespace Lizurd
{
	class Base;

	class RaceDescriptor
	{
	public:

		RaceDescriptor();
		virtual ~RaceDescriptor(void);
		virtual BWAPI::UnitType GetCommandCenterType() const = 0;
		virtual Base* CreateBaseFromCommandCentre(BWAPI::Unit unit) = 0;
		virtual BWAPI::UnitType GetWorkerType() const = 0;
	};

}