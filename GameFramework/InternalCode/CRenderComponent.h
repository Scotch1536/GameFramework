#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "CComponent.h"
#include "VertexProto.h"

using Microsoft::WRL::ComPtr;

//�����_�[�R���|�[�l���g�N���X
class CRenderComponent :public CComponent
{
protected:
	ComPtr<ID3D11VertexShader> mVertexShader;			// ���_�V�F�[�_�[
	ComPtr<ID3D11PixelShader> mPixelShader;				// �s�N�Z���V�F�[�_�[
	ComPtr<ID3D11InputLayout> mVertexLayout;			// ���_�t�H�[�}�b�g

public:
	CRenderComponent(IActor& owner , int priority = 100);

	//���_�V�F�[�_����
	bool GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , const char* vsfile);

	//�s�N�Z���V�F�[�_����
	bool GeneratePixelShader(const char* psfile);

	//�`��
	void Render(unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* cBMaterial);
};