#pragma once
#include "Order.h"

namespace Lizurd
{
	class GatherOrder: public Order
	{
	public:
		GatherOrder(BWAPI::Unit unit);
		~GatherOrder(void);
		virtual bool IsReady() const;
		virtual bool Execute();
	};
}