#include "../Actor/CActor.h"
#include "../ExternalCode/dx11mathutil.h"

#include "../Library/LCMath.h"

#include "CSphereMeshComponent.h"
#include "CRenderComponent.h"

CSphereMeshComponent::CSphereMeshComponent(CActor& owner , CTransform& parentTrans , XMFLOAT4 color , int divNum , float radius ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPrimitiveMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath) ,
	mRadius(radius) ,
	mDivisionNumber(divNum)
{
	Init(vertexShaderPath , pixelShaderPath);
}

void CSphereMeshComponent::CreateVertexData()
{
	float azimuth = 0.0f;			// ���ʊp
	float elevation = 0.0f;			// �p

	XMFLOAT3 Normal;

	// ���ʊp�Ƌp���狅���b�V���̒��_�f�[�^���쐬
	for(int y = 0; y <= mDivisionNumber; ++y)
	{
		elevation = (XM_PI* static_cast<float>(y)) / static_cast<float>(mDivisionNumber);		// �p���Z�b�g

		float r = mRadius * sinf(elevation);			// �p�ɉ��������a���v�Z

		for(int x = 0; x <= mDivisionNumber; ++x)
		{
			azimuth = (2 * XM_PI * static_cast<float>(x)) / static_cast<float>(mDivisionNumber);		// ���ʊp���Z�b�g

			SVertexColor v;
			v.Pos.x = r * cosf(azimuth);
			v.Pos.y = mRadius * cosf(elevation);
			v.Pos.z = r * sinf(azimuth);

			XMFLOAT3 normVec;
			LCMath::CalcFloat3FromStartToGoal({ 0.0f,0.0f,0.0f } , v.Pos , normVec);

			DX11Vec3Normalize(Normal , normVec);		// �@�����v�Z
			v.Normal = Normal;							// �@�����Z�b�g

			v.Color = mColor;				// ���_�J���[

			mVertices.emplace_back(v);
		}
	}
}

void CSphereMeshComponent::CreateIndexData()
{
	// �C���f�b�N�X����
	for(int y = 0; y < mDivisionNumber; ++y)
	{
		for(int x = 0; x < mDivisionNumber; ++x)
		{
			int count = (mDivisionNumber + 1)*y + x;		// ������W�̃C���f�b�N�X

			// �㔼��
			mIndices.emplace_back(count);
			mIndices.emplace_back(count + 1);
			mIndices.emplace_back(count + 1 + (mDivisionNumber + 1));

			// ������
			mIndices.emplace_back(count);
			mIndices.emplace_back(count + (mDivisionNumber + 1) + 1);
			mIndices.emplace_back(count + (mDivisionNumber + 1));
		}
	}
}
