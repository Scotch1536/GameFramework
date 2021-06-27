#pragma once
#include <string>

class CObject
{
private:
	std::string mID;

public:
	CObject(std::string id):mID(id) {};
	virtual ~CObject() = default;

	virtual void Update() = 0;

	virtual void Render() = 0;

	const std::string& GetID()
	{
		return mID;
	}
};