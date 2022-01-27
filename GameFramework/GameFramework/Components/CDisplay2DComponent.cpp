//!
//! @file
//! @brief �f�B�X�v���C2D�R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include "../Managers/CDirectXResourceManager.h"
#include "../Actor/CActor.h"

#include "CRenderComponent.h"
#include "CDisplay2DComponent.h"

CDisplay2DComponent::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath , const XMFLOAT4& color ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath , false)
{
	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);

	//������
	Init(vertexShaderPath , pixelShaderPath);
}

CDisplay2DComponent::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath , false)
{
	//������
	Init(vertexShaderPath , pixelShaderPath);
}

void CDisplay2DComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);		//���_�V�F�[�_����
	mRenderComponent.GeneratePixelShader(pixelShaderPath);								//�s�N�Z���V�F�[�_����

	CreateVertexData();		//���_�f�[�^�쐬
	CreateIndexData();		//�C���f�b�N�X�f�[�^�쐬

	//���_&�C���f�b�N�X�o�b�t�@�̐���
	GenerateVertexAndIndexBuffer();
}

XMFLOAT2* CDisplay2DComponent::GetUV(int index)
{
	return &mVertices.at(index).Tex;
};

void CDisplay2DComponent::Update()
{
	//����������Ȃ����
	if(!this->mIsTranslucent)this->mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPACITY2D });		//�`�施�ߒǉ�
	else this->mOwnerInterface.AddRenderOrder({ *this,ERenderOption::TRANSLUCENT2D });						//�`�施�ߒǉ�
}

void CDisplay2DComponent::Render()
{
	//GPU�ւ̍s��̃Z�b�g�����N�G�X�g
	this->Transform.RequestSetMatrix();

	//�`��
	this->mRenderComponent.Render(sizeof(SVertex2D) , this->mIndices.size() , mTextureSRV , this->mVertexBuffer.Get() , this->mIndexBuffer.Get() , nullptr);
}