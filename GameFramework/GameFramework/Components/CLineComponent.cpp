//!
//! @file
//! @brief ���C���R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include "../Actor/CActor.h"
#include "../Managers/CDirectXResourceManager.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/Shader.h"
#include "../Library/LCMath.h"

#include "CLineComponent.h"

CLineComponent::CLineComponent(CActor& owner , const XMFLOAT3& start , const XMFLOAT3& end ,
	const XMFLOAT4& color , CTransform* parentTrans , std::string vertexShaderPath ,
	std::string pixelShaderPath , int priority):CComponent(owner , priority) ,
	mStartPoint(start) , mEndPoint(end) , mColor(color) , mParentTransform(parentTrans)
{
	//���_������
	mVertices.at(0).Pos = mStartPoint;
	mVertices.at(1).Pos = mEndPoint;
	mVertices.at(0).Color = mVertices.at(1).Color = mColor;

	//������
	Init(vertexShaderPath , pixelShaderPath);
}

CLineComponent::CLineComponent(CActor& owner , const XMFLOAT3& start , const XMFLOAT3& direction , float length ,
	const XMFLOAT4& color , CTransform* parentTrans , std::string vertexShaderPath ,
	std::string pixelShaderPath , int priority):CComponent(owner , priority) ,
	mStartPoint(start) , mColor(color) , mParentTransform(parentTrans)
{
	XMFLOAT3 dire = direction;

	//���K��
	LCMath::CalcFloat3Normalize(dire , dire);

	//���_������
	mVertices.at(0).Pos = mStartPoint;
	mVertices.at(1).Pos = mEndPoint = LCMath::CalcFloat3Scalar(dire , length);
	mVertices.at(0).Color = mVertices.at(1).Color = mColor;

	//������
	Init(vertexShaderPath , pixelShaderPath);
}

void CLineComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	CDirectXResourceManager& buf = CDirectXResourceManager::GetInstance();

	mVertexShader = buf.GetVertexShader(vertexShaderPath);
	mVertexLayout = buf.GetVertexLayout(layout , numElements , vertexShaderPath);
	mPixelShader = buf.GetPixelShader(pixelShaderPath);

	//���_�o�b�t�@�쐬
	CreateVertexBufferWrite(CDirectXGraphics::GetInstance()->GetDXDevice() ,
		sizeof(SVertexLine) , mVertices.size() , mVertices.data() , mVertexBuffer.GetAddressOf());

	//�e�̃g�����X�t�H�[�������݂���Ȃ�
	if(mParentTransform != nullptr)
	{
		//�g�����X�t�H�[���̍s��X�V���֐��Ɏ��g�̃��\�b�h��ǉ�
		mParentTransform->AddMatrixUpdateTimeFunction(std::bind(&CLineComponent::SetShouldUpdate , std::ref(*this) , true));
	}
}

void CLineComponent::Render()
{
	ID3D11DeviceContext* devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	//���_�o�b�t�@���Z�b�g����
	unsigned int stride = sizeof(SVertexLine);
	unsigned offset = 0;
	devcontext->IASetVertexBuffers(0 , 1 , mVertexBuffer.GetAddressOf() , &stride , &offset);		//���_�o�b�t�@�Z�b�g

	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);			//�g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
	devcontext->IASetInputLayout(mVertexLayout.Get());								//���_���C�A�E�g�Z�b�g

	devcontext->VSSetShader(mVertexShader.Get() , nullptr , 0);			//���_�V�F�[�_�[���Z�b�g
	devcontext->PSSetShader(mPixelShader.Get() , nullptr , 0);			//�s�N�Z���V�F�[�_�[���Z�b�g

	devcontext->Draw(2 , 0);		//�h���[�R�[��
}

void CLineComponent::Update()
{
	if(mShouldUpdate)
	{
		//�e�̃g�����X�t�H�[��������Ȃ�
		if(mParentTransform != nullptr)
		{
			mShouldUpdate = false;

			XMFLOAT3 scale = mParentTransform->GetWorldScale();						//�e�̃g�����X�t�H�[���̃��[���h�̃X�P�[�����擾
			XMFLOAT4X4 resultMTX = mParentTransform->GetWorldMatrixResult();		//�e�̃g�����X�t�H�[���̃��[���h�ϊ��s��擾
			XMFLOAT4X4 scaleMTX;

			DX11MtxScale(scale.x , scale.y , scale.z , scaleMTX);				//�X�P�[���s��쐬
			LCMath::InverseMatrix(scaleMTX , scaleMTX);							//�X�P�[���s����t�s�񉻂���
			LCMath::CalcMatrixMultply(resultMTX , scaleMTX , resultMTX);		//�e�̃g�����X�t�H�[���̃��[���h�ϊ��s�񂩂�X�P�[�����̂ݏ��O����

			std::vector<SVertexLine> vertices;

			for(auto& v : mVertices)
			{
				SVertexLine vertex;
				LCMath::CalcFloat3MultplyMatrix(v.Pos , resultMTX , vertex.Pos);		//���_�����[���h�ϊ�����
				vertex.Color = mColor;
				vertices.emplace_back(vertex);
			}

			//���_�o�b�t�@�X�V
			UpdateVertex(vertices.data() , vertices.size());
		}
		else
		{
			//���_�o�b�t�@�X�V
			UpdateVertex(mVertices.data() , mVertices.size());
		}
	}

	//�`�施�ߒǉ�
	mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPACITY3D });
}

void CLineComponent::UpdateVertex(void* source , int size)
{
	D3D11_MAPPED_SUBRESOURCE pData;

	//���_�o�b�t�@���X�V
	HRESULT hr = CDirectXGraphics::GetInstance()->GetImmediateContext()->Map(mVertexBuffer.Get() , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &pData);
	if(SUCCEEDED(hr))
	{
		memcpy_s(pData.pData , pData.RowPitch , source , sizeof(SVertexLine) * size);
		CDirectXGraphics::GetInstance()->GetImmediateContext()->Unmap(mVertexBuffer.Get() , 0);
	}
}
