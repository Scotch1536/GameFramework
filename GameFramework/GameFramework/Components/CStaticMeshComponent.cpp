//!
//! @file
//! @brief �X�^�e�B�b�N���b�V���R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include <string>

#include "../Managers/CModelDataManager.h"
#include "../Managers/CDirectXResourceManager.h"
#include "../Actor/CActor.h"

#include "CStaticMeshComponent.h"
#include "CRenderComponent.h"

CStaticMeshComponent::CStaticMeshComponent(CActor& owner , CTransform& parentTrans , CModelData& model , std::string vertexShaderPath , std::string pixelShaderPath)
	:CComponent(owner , 90) ,
	Transform(owner , parentTrans) ,
	mModel(&model) ,
	mRenderComponent(*new CRenderComponent(owner))
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
}

void CStaticMeshComponent::Update()
{
	//�`�施�ߒǉ�
	mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPAQUE3D });
}

void CStaticMeshComponent::Render()
{
	//GPU�ւ̍s��̃Z�b�g�����N�G�X�g
	Transform.RequestSetMatrix();

	for(auto& mesh : mModel->GetMeshes())
	{
		unsigned int indexSize = static_cast <unsigned int>(mesh.Indices.size());

		//�e�N�X�`�������邩
		if(mesh.Textures.size() >= 1)
		{
			//�`��
			mRenderComponent.Render(sizeof(SVertexUV) , indexSize , mesh.Textures[0].TextureSRV ,
				mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
		}
		else
		{
			//�`��
			mRenderComponent.Render(sizeof(SVertexUV) , indexSize , nullptr ,
				mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
		}
	}
}