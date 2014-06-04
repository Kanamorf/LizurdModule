#pragma once
#include "BWAPI.h"
#include "Notification.h"
#include "Gateway.h"

class Coordinator
{
public:
	Coordinator(Gateway &gateway, std::string name);
	virtual ~Coordinator(void);

	virtual bool ProcessNotification(const Notification &notification) = 0;
	virtual bool UpdateInternal() = 0;
	virtual bool AfterUpdateInternal() = 0;

	bool Update();
	std::string GetName() const { return _name; }
	inline bool operator==(const Coordinator & m) const { return m._name == _name; }


protected:

	Gateway &_gateway;
private:

	std::string _name;
	

};

