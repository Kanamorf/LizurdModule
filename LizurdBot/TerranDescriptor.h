#pragma once
#include "RaceDescriptor.h"

namespace Lizurd
{
	class TerranDescriptor :
		public RaceDescriptor
	{
	public:
		TerranDescriptor(void);
		~TerranDescriptor(void);
		virtual BWAPI::UnitType GetCommandCenterType() const override { return BWAPI::UnitTypes::Terran_Command_Center; }
			virtual BWAPI::UnitType GetWorkerType() const override  { return BWAPI::UnitTypes::Terran_SCV; }
			virtual void CreateBaseFromCommandCentre(BWAPI::Unit unit, Base *base) override;
			virtual Strategy* GetDefaultStrategy() const override;
			virtual Goal* GetSupplyGoal() const override;
	};
}