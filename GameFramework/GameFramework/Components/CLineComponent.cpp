#include <string>

#include "../ExternalCode/CDirectxGraphics.h"
#include "../Actor/CActor.h"
#include "CLineComponent.h"
#include "../Managers/CDirectXResourceManager.h"
#include "../ExternalCode/dx11mathutil.h"
#include"../Library/LCMath.h"

CLineComponent::CLineComponent(CActor& owner, XMFLOAT3 vertex1, XMFLOAT3 vertex2, XMFLOAT4 color, CTransform* parentTrans,
	std::string vertexShaderPath , 
	std::string pixelShaderPath, int priority) :CComponent(owner, priority), mOwnerTransform(parentTrans),mColor(color)
{
	mVertices.resize(2);
	mVertices.at(0) = vertex1;
	mVertices.at(1) = vertex2;
	mVertexSize = mVertices.size();

	Init(vertexShaderPath, pixelShaderPath);
}

CLineComponent::CLineComponent(CActor& owner, XMFLOAT3 start, XMFLOAT3 direction, float length,
	XMFLOAT4 color, CTransform* parentTrans,
	std::string vertexShaderPath,
	std::string pixelShaderPath, int priority) :CComponent(owner, priority), mOwnerTransform(parentTrans), mColor(color)
{
	mVertices.resize(2);
	LCMath::CalcFloat3Normalize(direction, direction);
	mVertices.at(0) = start;
	mVertices.at(1) = LCMath::CalcFloat3Scalar(direction,length);
	mVertexSize = mVertices.size();

	Init(vertexShaderPath, pixelShaderPath);
}

void CLineComponent::Init(std::string vertexShaderPath, std::string pixelShaderPath)
{
	//�A�N�^�[(owner)�Ƀ����_�[�S���̃R���|�[�l���g�Ƃ��ēo�^
	mOwnerInterface.AddRenderComponent(*this);

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	CDirectXResourceManager& buf = CDirectXResourceManager::GetInstance();

	mVertexShader = buf.GetVertexShader(vertexShaderPath);
	mPixelShader = buf.GetPixelShader(pixelShaderPath);
	CreateVertexBufferWrite(CDirectXGraphics::GetInstance()->GetDXDevice(),
		sizeof(XMFLOAT3), mVertices.size(), (void*)mVertices.data(), &mVertexBuffer);

	if (mOwnerTransform != nullptr)
	{
		mOwnerTransform->SetMatrixUpdateTimeFunction(std::bind(&CLineComponent::SetShouldUpdate, std::ref(*this), true));
	}
}


void CLineComponent::Render()
{
	mOwnerTransform->RequestSetMatrix();
	ID3D11DeviceContext* devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// ���_�o�b�t�@���Z�b�g����
	unsigned int stride = sizeof(XMFLOAT3);
	unsigned  offset = 0;
	devcontext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);

	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);		// �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
	devcontext->IASetInputLayout(mLayout.Get());			// ���_���C�A�E�g�Z�b�g

	devcontext->VSSetShader(mVertexShader.Get(), nullptr, 0);		// ���_�V�F�[�_�[���Z�b�g
	devcontext->PSSetShader(mPixelShader.Get(), nullptr, 0);		// �s�N�Z���V�F�[�_�[���Z�b�g

	devcontext->Draw(
		mVertexSize,							// ���_��
		0);									// ���_�o�b�t�@�̍ŏ�����g��
}

void CLineComponent::Update()
{
	if (mOwnerTransform != nullptr)
	{
		if (mShouldUpdate)
		{
			mShouldUpdate = false;
			XMFLOAT3 scale = mOwnerTransform->GetWorldScale();
			XMFLOAT4X4 resultMTX = mOwnerTransform->GetWorldMatrixResult();
			XMFLOAT4X4 scaleMTX;
			DX11MtxScale(scale.x, scale.y, scale.z, scaleMTX);
			LCMath::InverseMatrix(scaleMTX, scaleMTX);
			DX11MtxMultiply(resultMTX, resultMTX, scaleMTX);

			std::vector<XMFLOAT3> vertices;

			for(auto& v: mVertices)
			{
				XMFLOAT3 vertex;
				DX11Vec3MulMatrix(vertex, v, resultMTX);
				vertices.emplace_back(vertex);
			}

			//���_�Z�b�g
			D3D11_MAPPED_SUBRESOURCE pData;

			HRESULT hr = CDirectXGraphics::GetInstance()->GetImmediateContext()->Map(mVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
			if (SUCCEEDED(hr)) {
				memcpy_s(pData.pData, pData.RowPitch, (void*)(vertices.data()), sizeof(XMFLOAT3) * vertices.size());
				CDirectXGraphics::GetInstance()->GetImmediateContext()->Unmap(mVertexBuffer.Get(), 0);
			}

		}
	}
}
