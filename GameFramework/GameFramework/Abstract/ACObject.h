#pragma once
#include <string>

class ACObject
{
private:
	std::string mID;

public:
	ACObject(std::string id):mID(id) {};
	virtual ~ACObject() = default;

	const std::string& GetID()
	{
		return mID;
	}
};