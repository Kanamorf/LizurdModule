#pragma once
#include "BWAPI.h"
#include "LizurdModule.h"
#include "Notification.h"
#include "Gateway.h"
#include "Defines.h"
#include "Logger.h"


namespace Lizurd
{
	class Coordinator
	{
	public:
		Coordinator(Gateway &gateway, std::string name);
		virtual ~Coordinator(void);

		virtual Result ProcessNotificationInternal(Notification &notification) = 0;
		virtual Result UpdateInternal() = 0;
		virtual Result AfterUpdateInternal() = 0;
		virtual void DrawDebugInfo(){}
		Result Update();
		std::string GetName() const { return _name; }
		inline bool operator==(const Coordinator & m) const { return m._name == _name; }



	protected:
		template<class T>
		void VectorRemove(std::vector<T> &vector, T unit)
		{
			std::vector<T>::iterator found = std::find(vector.begin(), vector.end(),unit);
			if(found != vector.end())
				vector.erase(found);
		}
		Gateway &_gateway;
	private:

		std::string _name;


	};

}