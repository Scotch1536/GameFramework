#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "../Data/VertexProto.h"

#include "CComponent.h"

using Microsoft::WRL::ComPtr;

//�����_�[�R���|�[�l���g�N���X
class CRenderComponent :public CComponent
{
private:
	ID3D11VertexShader* mVertexShader = nullptr;		// ���_�V�F�[�_�[
	ID3D11PixelShader* mPixelShader = nullptr;			// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout* mVertexLayout = nullptr;			// ���_�t�H�[�}�b�g

public:
	CRenderComponent(CActor& owner , int priority = 100);

	//���_�V�F�[�_����
	void GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);

	//�s�N�Z���V�F�[�_����
	void GeneratePixelShader(std::string psFilePath);

	//�`��
	void Render(unsigned int stride,
		unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* cBMaterial);

};