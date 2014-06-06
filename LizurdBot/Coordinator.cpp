#include "Coordinator.h"


Coordinator::Coordinator(Gateway &gateway, std::string name) :
	_name(name),
	_gateway(gateway)
{
}


Coordinator::~Coordinator(void)
{
}


Result Coordinator::Update()
{
	Result retVal = Result::Failure;
	if(UpdateInternal() == Result::Success)
		retVal = AfterUpdateInternal();
	return retVal;
}

void Coordinator::VectorRemove(std::vector<BWAPI::Unit> &vector, BWAPI::Unit unit)
{
	std::vector<BWAPI::Unit>::iterator found = std::find(vector.begin(), vector.end(),unit);
	if(found != vector.end())
		vector.erase(found);
}