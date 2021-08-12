#pragma once

#include "../Interfaces/IRender.h"
#include "CComponent.h"
#include <DirectXMath.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>
#include "../ExternalCode/Shader.h"

using Microsoft::WRL::ComPtr;

class CLineComponent :public CComponent, public IRender
{
private:
	ComPtr<ID3D11Buffer>		mVertexBuffer;			// ���_�o�b�t�@
	ComPtr<ID3D11PixelShader>	mPixelShader;				// �s�N�Z���V�F�[�_�[
	ComPtr<ID3D11VertexShader>	mVertexShader;				// ���_�V�F�[�_�[
	ComPtr<ID3D11InputLayout>   mLayout;			// ���_�t�H�[�}�b�g��`
	size_t						mVertexSize;			// ���_��
	std::vector<XMFLOAT3>       mVertices;
	XMFLOAT4		mColor = {1.0f,1.0f,1.0f,1.0f};
	CTransform* mOwnerTransform;

	bool mShouldUpdate = true;

	void Init(std::string vertexShaderPath, std::string pixelShaderPath);

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}
public:

	CLineComponent(CActor& owner,XMFLOAT3 vertex1, XMFLOAT3 vertex2,
		XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }, CTransform* parentTrans=nullptr,
		std::string vertexShaderPath="Shader/vsline.hlsl", 
		std::string pixelShaderPath = "Shader/psline.hlsl", int priority = 90);

	CLineComponent(CActor& owner,XMFLOAT3 start, XMFLOAT3 direction,float length,
		XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }, CTransform* parentTrans=nullptr,
		std::string vertexShaderPath="Shader/vsline.hlsl", 
		std::string pixelShaderPath = "Shader/psline.hlsl", int priority = 90);


	//�J���[�Z�b�g
	void SetColor(XMFLOAT4 color) { mColor = color; }

	//�`��
	void Render()override;

	//�X�V
	void Update()override;
};