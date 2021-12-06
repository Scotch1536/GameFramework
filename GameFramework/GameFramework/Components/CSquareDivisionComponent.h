#pragma once
#include <DirectXMath.h>
#include <vector>
#include <array>
#include <unordered_map>
#include <string>

#include "CComponent.h"

using namespace DirectX;

class  CSquareDivisionComponent :public CComponent
{
protected:
	std::unordered_map<std::string , std::pair<int , int>> mAlias;		//ï ñº
	std::vector<std::array<XMFLOAT2 , 4>> mUVDivisionData;		//UVç¿ïW

public:
	CSquareDivisionComponent(CActor& owner , int divWidth , int divHeight);

	void GetUV(int index , std::array<XMFLOAT2 , 4>& result);
	void GetUV(std::string alias , std::array<XMFLOAT2 , 4>& result);

	void AddAlias(int start , int finish , std::string alias)
	{
		mAlias[alias].first = start;
		mAlias[alias].second = finish;
	};

	void AddAlias(int index , std::string alias)
	{
		mAlias[alias].first = index;
		mAlias[alias].second = index;
	};

	void DeleteAlias(std::string alias)
	{
		if(mAlias.count(alias) != 0) { mAlias.erase(alias); }
	}

};