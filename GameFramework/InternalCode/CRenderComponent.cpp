#include "CRenderComponent.h"
#include "CDirectxGraphics.h"
#include "Shader.h"

CRenderComponent::CRenderComponent(IActor& owner):CComponent(owner)
{
	mPriority = 100;
}

bool CRenderComponent::GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , const char* vsfile)
{
	ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	bool sts = CreateVertexShader(device ,
		vsfile ,
		"main" ,
		"vs_5_0" ,
		layout ,
		layoutSize ,
		&mVertexShader ,
		&mVertexLayout);
	if(!sts)
	{
		MessageBox(nullptr , "CreateVertexShader error" , "error" , MB_OK);
		return false;
	}

	return true;
}

bool CRenderComponent::GeneratePixelShader(const char* psfile)
{
	ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

	// �s�N�Z���V�F�[�_�[�𐶐�
	bool sts = CreatePixelShader(
		device ,
		psfile ,
		"main" ,
		"ps_5_0" ,
		&mPixelShader);
	if(!sts)
	{
		MessageBox(nullptr , "CreatePixelShader error" , "error" , MB_OK);
		return false;
	}

	return true;
}

//void CRenderComponent::SetData(unsigned int indexSize ,
//	ID3D11ShaderResourceView* shaderResourceView ,
//	ID3D11Buffer* vertexBuffer ,
//	ID3D11Buffer* indexBuffer ,
//	ID3D11Buffer* cBMaterial)
//{
//	mIndexBuffer = indexBuffer;
//	mShaderResourceView = shaderResourceView;
//	mVertexBuffer = vertexBuffer;
//	mIndexBuffer = indexBuffer;
//	mCBMaterial = cBMaterial;
//}

void CRenderComponent::Render(unsigned int indexSize ,
	ID3D11ShaderResourceView* shaderResourceView ,
	ID3D11Buffer* vertexBuffer ,
	ID3D11Buffer* indexBuffer ,
	ID3D11Buffer* cBMaterial)
{
	ID3D11DeviceContext*	devcontext;			// �f�o�C�X�R���e�L�X�g

	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();
	// ���_�t�H�[�}�b�g���Z�b�g
	devcontext->IASetInputLayout(mVertexLayout.Get());
	// ���_�V�F�[�_�[���Z�b�g
	devcontext->VSSetShader(mVertexShader.Get() , nullptr , 0);
	// �s�N�Z���V�F�[�_�[���Z�b�g
	devcontext->PSSetShader(mPixelShader.Get() , nullptr , 0);
	// ���_�o�b�t�@���Z�b�g
	devcontext->IASetVertexBuffers(0 , 1 , &vertexBuffer , &stride , &offset);
	// �C���f�b�N�X�o�b�t�@���Z�b�g
	devcontext->IASetIndexBuffer(indexBuffer , DXGI_FORMAT_R32_UINT , 0);
	// �g�|���W�[���Z�b�g
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// SRV���Z�b�g
	devcontext->PSSetShaderResources(0 , 1 , &shaderResourceView);

	//else {
	//	// �^����SRV���Z�b�g
	//	devcontext->PSSetShaderResources(0, 1, &m_whitesrv);
	//}

	// �}�e���A����VS�փZ�b�g
	devcontext->VSSetConstantBuffers(3 , 1 , &cBMaterial);
	devcontext->PSSetConstantBuffers(3 , 1 , &cBMaterial);

	// �C���f�b�N�X�o�b�t�@�𗘗p���ĕ`��
	devcontext->DrawIndexed(indexSize , 0 , 0);

}

void CRenderComponent::Update()
{

}