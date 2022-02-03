//!
//! @file
//! @brief �����_�[�R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include <filesystem>

#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../Managers/CDirectXResourceManager.h"

#include "CRenderComponent.h"

CRenderComponent::CRenderComponent(CActor& owner , int priority):CComponent(owner , priority)
{}

void CRenderComponent::GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath)
{
	CDirectXResourceManager& buf = CDirectXResourceManager::GetInstance();

	mVertexShader = buf.GetVertexShader(vsFilePath);
	mVertexLayout = buf.GetVertexLayout(layout , layoutSize , vsFilePath);
}

void CRenderComponent::GeneratePixelShader(std::string psFilePath)
{
	mPixelShader = CDirectXResourceManager::GetInstance().GetPixelShader(psFilePath);
}

void CRenderComponent::Render(unsigned int stride ,
	unsigned int indexSize ,
	ID3D11ShaderResourceView* shaderResourceView ,
	ID3D11Buffer* vertexBuffer ,
	ID3D11Buffer* indexBuffer ,
	ID3D11Buffer* materialCB)
{
	unsigned int offset = 0;

	ID3D11DeviceContext* devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	//���_���C�A�E�g���Z�b�g
	devcontext->IASetInputLayout(mVertexLayout);

	//���_�V�F�[�_�[���Z�b�g
	devcontext->VSSetShader(mVertexShader , nullptr , 0);

	//�s�N�Z���V�F�[�_�[���Z�b�g
	devcontext->PSSetShader(mPixelShader , nullptr , 0);

	//���_�o�b�t�@���Z�b�g
	devcontext->IASetVertexBuffers(0 , 1 , &vertexBuffer , &stride , &offset);

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	devcontext->IASetIndexBuffer(indexBuffer , DXGI_FORMAT_R32_UINT , 0);

	//�g�|���W�[���Z�b�g
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//SRV�����݂��Ă����
	if(shaderResourceView != nullptr)
	{
		//SRV���Z�b�g
		devcontext->PSSetShaderResources(0 , 1 , &shaderResourceView);
	}
	else
	{
		ID3D11ShaderResourceView* white = nullptr;

		//�����̃p�X���J�����g�f�B���N�g�����瑶�݂��邩
		if(std::filesystem::exists("Assets/Textures/White/white.bmp"))
		{
			white = CDirectXResourceManager::GetInstance().GetTextureSRV("Assets/Textures/White/white.bmp");
		}
		else if(std::filesystem::exists("GameFramework/Assets/white.bmp"))
		{
			white = CDirectXResourceManager::GetInstance().GetTextureSRV("GameFramework/Assets/white.bmp");
		}
		else
		{
			MessageBox(nullptr , "Not Found White Texture" , "Error" , MB_OK);
		}

		//SRV���Z�b�g
		devcontext->PSSetShaderResources(0 , 1 , &white);
	}

	if(materialCB != nullptr)
	{
		//�}�e���A���萔�o�b�t�@���Z�b�g
		devcontext->VSSetConstantBuffers(3 , 1 , &materialCB);
		devcontext->PSSetConstantBuffers(3 , 1 , &materialCB);
	}

	//�C���f�b�N�X�o�b�t�@�𗘗p���ĕ`��
	devcontext->DrawIndexed(indexSize , 0 , 0);
}