#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <vector>
#include <string>

#include "../Interfaces/IRender.h"
#include "../Data/VertexProto.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class CRenderComponent;

class CPrimitiveMeshComponent :public CComponent , public IRender
{
protected:
	ComPtr<ID3D11Buffer> mVertexBuffer;			//���_�o�b�t�@
	ComPtr<ID3D11Buffer> mIndexBuffer;			//�C���f�b�N�X�o�b�t�@

	CRenderComponent& mRenderComponent;

	std::vector<SVertexColor> mVertices;		//���_�f�[�^
	std::vector<unsigned int> mIndices;			//�C���f�b�N�X�f�[�^

	XMFLOAT4 mColor;		//�J���[

	bool isTranslucent = false;		//���������ǂ���

	virtual void CreateVertexData() = 0;
	virtual void CreateIndexData() = 0;

	void GenerateVertexAndIndexBuffer();

public:
	CTransform Transform;			//�g�����X�t�H�[��

	CPrimitiveMeshComponent(CActor& owner , XMFLOAT4 color , std::string vertexShaderPath , std::string pixelShaderPath);

	void Update()override;
	void Render()override;

};