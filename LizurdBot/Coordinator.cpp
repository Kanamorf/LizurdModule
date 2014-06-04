#include "Coordinator.h"


Coordinator::Coordinator(Gateway &gateway, std::string name) :
	_name(name),
	_gateway(gateway)
{
}


Coordinator::~Coordinator(void)
{
}


bool Coordinator::Update()
{
	bool retVal = false;
	if(UpdateInternal())
		retVal = AfterUpdateInternal();
	return retVal;
}