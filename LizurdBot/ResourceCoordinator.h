#pragma once
#include "coordinator.h"
#include "ResourceValue.h"

namespace Lizurd
{

	class ResourceCoordinator :
		public Coordinator
	{
	public:
		ResourceCoordinator(Gateway &gateway);
		~ResourceCoordinator(void);

		virtual Result ProcessNotificationInternal(Notification &notification) override;
		virtual Result UpdateInternal(int frameNo) override;
		virtual Result AfterUpdateInternal() override;

		ResourceValue GetCurrentResources() const;

	private:

		Result RequestResources(ResourceValue value);
		Result ReleaseResources(ResourceValue value);

	private:
		ResourceValue _totalResources;
		ResourceValue _reservedResources;
	};

}