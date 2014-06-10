#pragma once
#include "RaceDescriptor.h"

namespace Lizurd
{
	class ProtossDescriptor :
		public RaceDescriptor
	{
	public:
		ProtossDescriptor(void);
		~ProtossDescriptor(void);
		virtual BWAPI::UnitType GetCommandCenterType() const override { return BWAPI::UnitTypes::Protoss_Nexus; }
			virtual BWAPI::UnitType GetWorkerType() const override  { return BWAPI::UnitTypes::Protoss_Scarab; }
			virtual void CreateBaseFromCommandCentre(BWAPI::Unit unit, Base *base) override;
			virtual Strategy* GetDefaultStrategy() const override;
			virtual Goal* GetSupplyGoal() const override;
	};
}