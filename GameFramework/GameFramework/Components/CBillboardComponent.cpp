#include "../Managers/CDirectXResourceManager.h"
#include "../Managers/CGameManager.h"

#include "CBillboardComponent.h"
#include "CRenderComponent.h"

//!
//! @file
//! @brief �r���{�[�h�R���|�[�l���g�̃\�[�X�t�@�C��
//!

CBillboardComponent::CBillboardComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , { 1.0f,1.0f,1.0f,1.0f } , vertexShaderPath , pixelShaderPath , false)
{
	Transform.SetIsBillboard(true);

	//������
	Init(vertexShaderPath , pixelShaderPath);

	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);
}

void CBillboardComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

void CBillboardComponent::Update()
{
	//�`�施�߂̒ǉ�
	mOwnerInterface.AddRenderOrder({ *this,ERenderOption::BILLBOARD,CGameManager::GetInstance().CalcDistanceToCamera(Transform.GetWorldLocation()) });
}

void CBillboardComponent::Render()
{
	//GPU�ւ̍s��̃Z�b�g�����N�G�X�g
	Transform.RequestSetMatrix();

	//�`��
	mRenderComponent.Render(sizeof(SVertexUV) , mIndices.size() , mTextureSRV , mVertexBuffer.Get() , mIndexBuffer.Get() , nullptr);
}