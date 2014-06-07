#pragma once
#include <string>
#include <vector>
#include "Defines.h"
#include "BWAPI.h"


namespace Lizurd
{
	class Notification
	{
	public:

		Notification(std::string target);
		~Notification(void);

		void push_back(BWAPI::Unit);
		BWAPI::Unit back() const;
		size_t size() const;
		std::string GetTarget() const { return _target; }
		void SetTarget(const std::string &target) { _target = target; }
		void SetAction(const Action &action) { _action = action; }
		Action GetAction() const { return _action; }
		void SetResourceValue(const ResourceValue &value) { _value = value; }
		ResourceValue GetResourceValue() const { return _value; }

	private:
		std::string _target;
		std::vector<BWAPI::Unit> _units;
		Action _action;
		ResourceValue _value;
	};

}