#pragma once
#include "Order.h"

namespace Lizurd
{
	class GasOrder: public Order
	{
	public:
		GasOrder(BWAPI::Unit unit);
		~GasOrder(void);
		virtual bool IsReady() const;
		virtual bool Execute();
		void SetExtractor(BWAPI::Unit extractor) { _extractor = extractor; }

	private:
		BWAPI::Unit _extractor;
	};
}