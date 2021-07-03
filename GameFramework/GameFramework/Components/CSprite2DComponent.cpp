#include <string>

#include "../Managers/CTextureManager.h"
#include "../Actor/CActor.h"

#include "CSprite2DComponent.h"
#include "CRenderComponent.h"

CSprite2DComponent::CSprite2DComponent(CActor& owner, CTextureData& texture, std::string vertexShaderPath, std::string pixelShaderPath, int priority)
	:CComponent(owner, priority), Transform(owner), 
	mTexture(texture), mRenderComponent(*new CRenderComponent(owner))
{
	//�A�N�^�[(owner)�Ƀ����_�[�S���̃R���|�[�l���g�Ƃ��ēo�^
	mOwnerInterface.RegisterRenderComponent(*this);

	// ���_�f�[�^�̒�`�i�A�j���[�V�����Ή��j
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//�G�������g���m��
	unsigned int numElements = ARRAYSIZE(layout);
	mRenderComponent.GenerateVertexShader(layout, numElements, vertexShaderPath.c_str());
	mRenderComponent.GeneratePixelShader(pixelShaderPath.c_str());

}

void CSprite2DComponent::Render()
{
	Transform.RequestSetMatrix();

}