#include "Coordinator.h"

using namespace Lizurd;

Coordinator::Coordinator(Gateway &gateway, std::string name) :
	_name(name),
	_gateway(gateway)
{
}


Coordinator::~Coordinator(void)
{
}


Result Coordinator::Update(int frameNo)
{
	Result retVal = Result::Failure;
	if(UpdateInternal(frameNo) == Result::Success)
		retVal = AfterUpdateInternal();
	return retVal;
}

