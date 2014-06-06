#pragma once
#include "BWAPI.h"
#include "Notification.h"
#include "Gateway.h"
#include "Defines.h"
#include "Logger.h"

class Coordinator
{
public:
	Coordinator(Gateway &gateway, std::string name);
	virtual ~Coordinator(void);

	virtual Result ProcessNotificationInternal(Notification &notification) = 0;
	virtual Result UpdateInternal() = 0;
	virtual Result AfterUpdateInternal() = 0;

	Result Update();
	std::string GetName() const { return _name; }
	inline bool operator==(const Coordinator & m) const { return m._name == _name; }


protected:
	void VectorRemove(std::vector<BWAPI::Unit> &vector, BWAPI::Unit unit);
	Gateway &_gateway;
private:

	std::string _name;
	

};

