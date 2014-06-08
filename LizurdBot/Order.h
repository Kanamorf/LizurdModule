#pragma once
#include <string>
#include "Defines.h"
#include "BWAPI.h"
#include "ResourceValue.h"

namespace
{
	const std::string GATHERORDER = "GatherOrder";
	const std::string VESPENEORDER = "VespeneOrder";
	const std::string SCOUTORDER = "ScoutOrder";
	const std::string ATTACKORDER = "AttackOrder";
}

namespace Lizurd
{


	class Order
	{
	public:
		Order(std::string name, TaskPriority priority);
		Order(std::string name, BWAPI::Unit executor, TaskPriority priority);
		virtual ~Order(void);
		virtual bool IsUnderway() const { return _isUnderway; };
		std::string GetNameWithID() const;
		void SetIsUnderway(const bool underway) { _isUnderway = underway; };
		TaskPriority GetPriority() const { return  _priority; };
		bool IsUnique() const { return  _isUnique; };	
		void SetExecutor(const BWAPI::Unit executor) { _executor = executor; };
		BWAPI::Unit GetExecutor() const { return _executor; };
		bool ShouldRetry();
		bool ShouldStart() const;
		ResourceValue GetCost() const { return _cost; };
		void SetCost(const ResourceValue cost) { _cost = cost; };
		void SetIsUnique(const bool unique) { _isUnique = unique; };
		int GetID() const { return _instanceId; }
		std::string GetName() const { return _name; }

		virtual bool IsComplete() const;
		virtual bool IsReady() const { return  false; };
		virtual bool Execute() =0;
		virtual BWAPI::TilePosition GetPredictedPosition() const { return BWAPI::TilePositions::None; };

	protected:
		std::string _name;
		TaskPriority _priority;
		BWAPI::Unit _executor;
		
		BWAPI::TilePosition _predictedPosition;
		bool _isUnique;
	private:	
		bool _isUnderway;
		bool _isReady;
		ResourceValue _cost;
		int _instanceId;
		static int _instanceCount;

	};

}