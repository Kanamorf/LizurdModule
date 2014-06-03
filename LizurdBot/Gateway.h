#pragma once
#include "Defines.h"
#include "Notification.h"

class Gateway
{
public:
	Gateway(void);
	~Gateway(void);

	Status ProcessNotification(const Notification &notification) const;
};

