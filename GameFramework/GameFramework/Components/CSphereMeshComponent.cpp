//!
//! @file
//! @brief �X�t�B�A���b�V���R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include "../Actor/CActor.h"

#include "../Library/LCMath.h"

#include "CSphereMeshComponent.h"
#include "CRenderComponent.h"

CSphereMeshComponent::CSphereMeshComponent(CActor& owner , CTransform& parentTrans ,const XMFLOAT4& color , int divNum , float radius ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPrimitiveMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath) ,
	mRadius(radius) ,
	mDivisionNumber(divNum)
{
	//������
	Init(vertexShaderPath , pixelShaderPath);
}

void CSphereMeshComponent::CreateVertexData()
{
	float azimuth = 0.0f;			//���ʊp
	float elevation = 0.0f;			//�p

	XMFLOAT3 Normal;

	//���ʊp�Ƌp���狅���b�V���̒��_�f�[�^���쐬
	for(int y = 0; y <= mDivisionNumber; ++y)
	{
		//�p���Z�b�g
		elevation = (XM_PI* static_cast<float>(y)) / static_cast<float>(mDivisionNumber);

		//�p�ɉ��������a���Z�o
		float r = mRadius * sinf(elevation);

		for(int x = 0; x <= mDivisionNumber; ++x)
		{
			//���ʊp���Z�b�g
			azimuth = (2 * XM_PI * static_cast<float>(x)) / static_cast<float>(mDivisionNumber);

			//���_�쐬
			SVertexColor v;
			v.Pos.x = r * cosf(azimuth);
			v.Pos.y = mRadius * cosf(elevation);
			v.Pos.z = r * sinf(azimuth);
			v.Normal = v.Pos;
			v.Color = mColor;

			mVertices.emplace_back(v);
		}
	}
}

void CSphereMeshComponent::CreateIndexData()
{
	for(int y = 0; y < mDivisionNumber; ++y)
	{
		for(int x = 0; x < mDivisionNumber; ++x)
		{
			int count = (mDivisionNumber + 1)*y + x;

			//�㔼��
			mIndices.emplace_back(count);
			mIndices.emplace_back(count + 1);
			mIndices.emplace_back(count + 1 + (mDivisionNumber + 1));

			//������
			mIndices.emplace_back(count);
			mIndices.emplace_back(count + (mDivisionNumber + 1) + 1);
			mIndices.emplace_back(count + (mDivisionNumber + 1));
		}
	}
}
