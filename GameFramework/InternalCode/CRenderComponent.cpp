#include "CRenderComponent.h"
#include "CDirectxGraphics.h"

void CRenderComponent::Render()
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
	devcontext->IASetVertexBuffers(0 , 1 , mVertexBuffer.GetAddressOf() , &stride , &offset);
	// �C���f�b�N�X�o�b�t�@���Z�b�g
	devcontext->IASetIndexBuffer(mIndexBuffer.Get() , DXGI_FORMAT_R32_UINT , 0);
	// �g�|���W�[���Z�b�g
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// SRV���Z�b�g
	devcontext->PSSetShaderResources(0 , 1 , mTexture.GetAddressOf());

	//else {
	//	// �^����SRV���Z�b�g
	//	devcontext->PSSetShaderResources(0, 1, &m_whitesrv);
	//}

	// �}�e���A����VS�փZ�b�g
	devcontext->VSSetConstantBuffers(3 , 1 , mCBMaterial.GetAddressOf());
	devcontext->PSSetConstantBuffers(3 , 1 , mCBMaterial.GetAddressOf());

	// �C���f�b�N�X�o�b�t�@�𗘗p���ĕ`��
	devcontext->DrawIndexed(mIndexSize , 0 , 0);
}