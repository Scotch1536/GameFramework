#define _USE_MATH_DEFINES
#include <cmath>

#include "../Actor/CActor.h"
#include "../ExternalCode/dx11mathutil.h"

#include "CSphereMeshComponent.h"
#include "CRenderComponent.h"

CSphereMeshComponent::CSphereMeshComponent(CActor& owner , float radius , int divNum , XMFLOAT4 color)
	:CComponent(owner , 0) ,
	mRenderComponent(*new CRenderComponent(owner)) ,
	mColor(color) ,
	mRadius(radius) ,
	mDivisionNumber(divNum)
{
	//�A�N�^�[(owner)�Ƀ����_�[�S���̃R���|�[�l���g�Ƃ��ēo�^
	mOwnerInterface.RegisterRenderComponent(*this);

	CreateVertex();
	CreateIndex();

}

void CSphereMeshComponent::CreateVertex()
{
	float azimuth = 0.0f;			// ���ʊp
	float elevation = 0.0f;			// �p

	XMFLOAT3 Normal;

	// ���ʊp�Ƌp���狅���b�V���̒��_�f�[�^���쐬
	for(unsigned int y = 0; y <= mDivisionNumber; y++)
	{
		elevation = (M_PI* static_cast<float>(y)) / static_cast<float>(mDivisionNumber);		// �p���Z�b�g

		float r = mRadius * sinf(elevation);					// �p�ɉ��������a���v�Z

		for(unsigned int x = 0; x <= mDivisionNumber; x++)
		{
			azimuth = (2 * M_PI * static_cast<float>(x)) / static_cast<float>(mDivisionNumber);		// ���ʊp���Z�b�g

			VertexColor v;
			v.m_Pos.x = r * cosf(azimuth);
			v.m_Pos.y = mRadius * cosf(elevation);
			v.m_Pos.z = r * sinf(azimuth);

			DX11Vec3Normalize(v.m_Pos , Normal);			// �@�����v�Z
			v.m_Normal = Normal;							// �@�����Z�b�g

			v.m_Color = mColor;				// ���_�J���[

			mVertex.emplace_back(v);
		}
	}
}

void CSphereMeshComponent::CreateIndex()
{
	// �C���f�b�N�X����
	for(unsigned int y = 0; y < mDivisionNumber; y++)
	{
		for(unsigned int x = 0; x < mDivisionNumber; x++)
		{
			int count = (mDivisionNumber + 1)*y + x;			// ������W�̃C���f�b�N�X

			Face f;
			// �㔼��
			f.idx[0] = count;
			f.idx[1] = count + 1;
			f.idx[2] = count + 1 + (mDivisionNumber + 1);

			mFace.emplace_back(f);

			// ������
			f.idx[0] = count;
			f.idx[1] = count + (mDivisionNumber + 1) + 1;
			f.idx[2] = count + (mDivisionNumber + 1);

			mFace.emplace_back(f);
		}
	}
}