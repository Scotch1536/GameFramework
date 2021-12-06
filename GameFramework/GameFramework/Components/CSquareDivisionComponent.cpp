#include <algorithm>

#include "CSquareDivisionComponent.h"

CSquareDivisionComponent::CSquareDivisionComponent(CActor& owner , int divWidth , int divHeight):CComponent(owner)
{
	int arraySize = divWidth * divHeight;
	float ratioWidth = 1.0f / divWidth;
	float ratioHeight = 1.0f / divHeight;

	mUVDivisionData.resize(arraySize);

	for(int i = 0; i < arraySize; ++i)
	{
		if(i == 0)
		{
			mUVDivisionData.at(i).at(0).x = 0.0f;
			mUVDivisionData.at(i).at(0).y = 0.0f;
		}
		else
		{
			if(i < divWidth)
			{
				mUVDivisionData.at(i).at(0).x = i * ratioWidth;
			}
			else
			{
				mUVDivisionData.at(i).at(0).x = i % divWidth*ratioWidth;
			}

			mUVDivisionData.at(i).at(0).y = i / divWidth * ratioHeight;
		}

		mUVDivisionData.at(i).at(1).x = mUVDivisionData.at(i).at(0).x + ratioWidth;
		mUVDivisionData.at(i).at(1).y = mUVDivisionData.at(i).at(0).y;

		mUVDivisionData.at(i).at(2).x = mUVDivisionData.at(i).at(0).x;
		mUVDivisionData.at(i).at(2).y = mUVDivisionData.at(i).at(0).y + ratioHeight;

		mUVDivisionData.at(i).at(3).x = mUVDivisionData.at(i).at(1).x;
		mUVDivisionData.at(i).at(3).y = mUVDivisionData.at(i).at(2).y;
	}
}

void CSquareDivisionComponent::GetUV(int index , std::array<XMFLOAT2 , 4>& result)
{
	index = std::clamp(index , 0 , static_cast<int>(mUVDivisionData.size()));

	result = mUVDivisionData.at(index);
}

void CSquareDivisionComponent::GetUV(std::string alias , std::array<XMFLOAT2 , 4>& result)
{
	if(mAlias.count(alias) != 0)
	{
		result = mUVDivisionData.at(mAlias[alias]);
	}
}
