#pragma once
#include <string>
#include <vector>
#include "Defines.h"
#include "BWAPI.h"
#include "ResourceValue.h"


namespace Lizurd
{
	class Notification
	{
	public:

		Notification(std::string target);
		~Notification(void);

		void AddUnit(BWAPI::Unit);
		BWAPI::Unit GetLastUnit();
		BWAPI::Unit PeekUnit() const;
		size_t UnitSize() const;
		std::string GetTarget() const { return _target; }
		void SetTarget(const std::string &target) { _target = target; }
		void SetAction(const Action &action) { _action = action; }
		Action GetAction() const { return _action; }
		void SetResourceValue(const ResourceValue &value) { _value = value; }
		ResourceValue GetResourceValue() const { return _value; }
		Goal* GetGoal() { return _goal; }
		void SetGoal(Goal* goal) { _goal = goal; }
		BWAPI::UnitType GetUnitType() const { return _type; }
		void SetUnitType(BWAPI::UnitType type) { _type = type; }
		void SetFrame(int frame) { _frame = frame; }
		int GetFrame() const { return _frame; }
	private:
		BWAPI::UnitType _type;
		std::string _target;
		std::vector<BWAPI::Unit> _units;
		Action _action;
		ResourceValue _value;
		Goal* _goal;
		int _frame;
	};

}