#pragma once
#include "BWAPI.h"
#include "Notification.h"
#include <map>

class RaceDescriptor;
class Coordinator;

class Gateway
{
public:
	Gateway(void);
	~Gateway(void);

	void Initialise(BWAPI::Race race);
	bool Update();
	bool RegisterNotification(const Notification &notification) const;

	RaceDescriptor &GetRaceDescriptor() const { return *_raceDescriptor; }

private:
	std::map<std::string, Coordinator*> _coordinators;
	RaceDescriptor *_raceDescriptor;
};

