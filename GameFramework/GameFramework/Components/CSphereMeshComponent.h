#pragma once
#include <vector>
#include <DirectXMath.h>

#include "../Interfaces/IRender.h"
#include "../ExternalCode/VertexProto.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

using namespace DirectX;

class CRenderComponent;

class CSphereMeshComponent :public CComponent , public IRender
{
private:
	// �C���f�b�N�X�f�[�^
	struct Face
	{
		unsigned int idx[3];
	};

	ComPtr<ID3D11Buffer>  mVertexBuffer;		// ���_�o�b�t�@
	ComPtr<ID3D11Buffer>  mIndexBuffer;			// �C���f�b�N�X�o�b�t�@

	CRenderComponent& mRenderComponent;

	std::vector<VertexColor> mVertex;		//���_�f�[�^
	std::vector<Face> mFace;				//�C���f�b�N�X�f�[�^

	XMFLOAT4 mColor;

	float mRadius;
	int mDivisionNumber;

	void CreateVertex();
	void CreateIndex();

public:
	CTransform Transform;			//�g�����X�t�H�[��

	CSphereMeshComponent(CActor& owner , float radius , int divNum , XMFLOAT4 color);

	void Render()override;
};