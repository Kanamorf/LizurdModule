#pragma once
#include "Defines.h"
#include "Notification.h"

class Coordinator
{
public:
	Coordinator(void);
	virtual ~Coordinator(void);

	virtual Status ProcessNotification(const Notification *pNotification) const = 0;

};

