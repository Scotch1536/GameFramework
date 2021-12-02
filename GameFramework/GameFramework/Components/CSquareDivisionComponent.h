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
private:
	std::unordered_map<std::string , int> mAlias;		//ï ñº

protected:
	std::vector<std::array<XMFLOAT2 , 4>> mUVDivisionData;		//UVç¿ïW

public:
	CSquareDivisionComponent(CActor& owner , int divWidth , int divHeight);

	void GetUV(int index , std::array<XMFLOAT2 , 4>& result);
	void GetUV(std::string alias , std::array<XMFLOAT2 , 4>& result);

	void SetAlias(int index , std::string alias)
	{
		mAlias[alias] = index;
	};
};