#include <string>

#include "../Managers/CModelDataManager.h"
#include "../Actor/CActor.h"

#include "CStaticMeshComponent.h"
#include "CRenderComponent.h"

CStaticMeshComponent::CStaticMeshComponent(CActor& owner , ModelData& model , std::string vertexShaderPath , std::string pixelShaderPath , int priority)
	:CComponent(owner , priority) ,
	mTransform(owner) ,
	mModel(&model) ,
	mRenderComponent(*new CRenderComponent(owner))
{
	mAttribute = CComponent::EAttribute::RENDER;

	//�A�N�^�[(owner)�Ƀ����_�[�S���̃R���|�[�l���g�Ƃ��ēo�^
	mOwnerInterface.RegisterRenderComponent(*this);

	// ���_�f�[�^�̒�`�i�A�j���[�V�����Ή��j
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath.c_str());
	mRenderComponent.GeneratePixelShader(pixelShaderPath.c_str());
}

void CStaticMeshComponent::Render()
{
	mTransform.RequestSetMatrix();

	for(auto& mesh : mModel->GetMeshes())
	{
		unsigned int indexSize = static_cast <unsigned int>(mesh.m_indices.size());

		if(mesh.m_textures.size() >= 1)
		{
			mRenderComponent.Render(indexSize , mesh.m_textures[0].texture ,
				mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
		}
		else
		{
			MessageBox(NULL , "Not Found Texture!!" , "error" , MB_OK);
			exit(1);
		}
	}
}