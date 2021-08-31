#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <string>

#include "../Interfaces/IRender.h"
#include "../Data/VertexProto.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class CRenderComponent;

template<class VertexType = SVertexColor>
class CPrimitiveMeshComponent :public CComponent , public IRender
{
protected:
	ComPtr<ID3D11Buffer> mVertexBuffer;			//���_�o�b�t�@
	ComPtr<ID3D11Buffer> mIndexBuffer;			//�C���f�b�N�X�o�b�t�@

	CRenderComponent& mRenderComponent;

	std::vector<VertexType> mVertices;			//���_�f�[�^
	std::vector<unsigned int> mIndices;			//�C���f�b�N�X�f�[�^

	XMFLOAT4 mColor;		//�J���[

	bool mIsTranslucent = false;		//���������ǂ���

	virtual void Init(std::string vertexShaderPath , std::string pixelShaderPath);
	virtual void CreateVertexData() = 0;
	virtual void CreateIndexData() = 0;

	void GenerateVertexAndIndexBuffer();

	void CheckTranslucent()
	{
		if(mColor.w < 1.0f)
		{
			mIsTranslucent = true;
		}
	}

public:
	CTransform Transform;			//�g�����X�t�H�[��

	CPrimitiveMeshComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color , std::string vertexShaderPath , std::string pixelShaderPath);

	const XMFLOAT4& GetColor()const
	{
		return mColor;
	}

	void SetColor(const XMFLOAT4& color);

	void Update()override;
	void Render()override;

};