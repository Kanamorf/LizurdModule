#pragma once
#include <string>
#include <vector>
#include "BWAPI.h"

class Notification
{
public:
	Notification(std::string target);
	~Notification(void);

	void push_back(BWAPI::Unit);
	BWAPI::Unit back() const;
	size_t size() const;
	std::string GetTarget() const { return _target; }

private:
	std::string _target;
	std::vector<BWAPI::Unit> _units;
};

