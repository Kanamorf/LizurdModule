#pragma once
#include "Defines.h"
#include "Notification.h"

class Gateway
{
public:
	Gateway(void);
	~Gateway(void);

	Status RegisterNotification(const Notification *pNotification) const;
};

