#pragma once
#include <string>
#include <vector>
#include "Defines.h"
#include "BWAPI.h"

class Notification
{
public:
	enum Action
	{
		None,
		RegisterUnit,
		DeRegisterUnit
	};

	Notification(std::string target);
	~Notification(void);

	void push_back(BWAPI::Unit);
	BWAPI::Unit back() const;
	size_t size() const;
	std::string GetTarget() const { return _target; }
	void SetTarget(const std::string &target) { _target = target; }
	void SetAction(const Action &action) { _action = action; }
	Action GetAction() const { return _action; }

private:
	std::string _target;
	std::vector<BWAPI::Unit> _units;
	Action _action;
};

