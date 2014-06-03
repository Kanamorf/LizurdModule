#pragma once
namespace
{
	enum Status
	{
		Failure,
		Succeeded
	};

	bool Success(Status status)
	{
		return status == Status::Succeeded;
	}
	bool Failed(Status status)
	{
		return !Success(status);
	}
}