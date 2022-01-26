#include <algorithm>

#include "CSquareDivisionComponent.h"

//!
//! @file
//! @brief �l�p�����R���|�[�l���g�̃\�[�X�t�@�C��
//!

CSquareDivisionComponent::CSquareDivisionComponent(CActor& owner , int divWidth , int divHeight):CComponent(owner)
{
	int arraySize = divWidth * divHeight;		//�z��̃T�C�Y���Z�o
	float ratioWidth = 1.0f / divWidth;			//������̉����̔䗦���Z�o
	float ratioHeight = 1.0f / divHeight;		//������̏c���̔䗦���Z�o

	mUVData.resize(arraySize);		//UV�f�[�^�z��̃T�C�Y���Đݒ�

	//UV�f�[�^�̏���������
	for(int i = 0; i < arraySize; ++i)
	{
		if(i == 0)
		{
			mUVData.at(i).at(0).x = 0.0f;
			mUVData.at(i).at(0).y = 0.0f;
		}
		else
		{
			if(i < divWidth)
			{
				mUVData.at(i).at(0).x = i * ratioWidth;
			}
			else
			{
				mUVData.at(i).at(0).x = i % divWidth*ratioWidth;
			}

			mUVData.at(i).at(0).y = i / divWidth * ratioHeight;
		}

		mUVData.at(i).at(1).x = mUVData.at(i).at(0).x + ratioWidth;
		mUVData.at(i).at(1).y = mUVData.at(i).at(0).y;

		mUVData.at(i).at(2).x = mUVData.at(i).at(0).x;
		mUVData.at(i).at(2).y = mUVData.at(i).at(0).y + ratioHeight;

		mUVData.at(i).at(3).x = mUVData.at(i).at(1).x;
		mUVData.at(i).at(3).y = mUVData.at(i).at(2).y;
	}
}

void CSquareDivisionComponent::GetUV(int index , std::array<XMFLOAT2 , 4>& result)
{
	//�C���f�b�N�X���N�����v
	index = std::clamp(index , 0 , static_cast<int>(mUVData.size() - 1));

	result = mUVData.at(index);
}

void CSquareDivisionComponent::GetUV(std::string alias , std::array<XMFLOAT2 , 4>& result)
{
	//�����̕ʖ������݂���Ȃ�
	if(mAlias.count(alias) != 0)
	{
		if(mAlias[alias].first == mAlias[alias].second)
		{
			result = mUVData.at(mAlias[alias].first);
		}
	}
}
