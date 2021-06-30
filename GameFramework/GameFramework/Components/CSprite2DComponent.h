#pragma once
#include <string>

#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "CComponent.h"

class CSprite2DComponent :public CComponent
{
private:
	// ���_�\����
	typedef struct {
		XMFLOAT3 pos; // ���W		
		XMFLOAT4 color; // �J���[
		XMFLOAT2 tex; // �e�N�X�`��;
	}Vertex;

	XMFLOAT2 mUv[4]; //�p�x
	XMFLOAT4 mColor = { 1.0f, 1.0f, 1.0f, 1.0f }; //�F
	float mAngle;
	ComPtr<ID3D11Buffer> mVertexBuffer = nullptr; // ���_�o�b�t�@
	ComPtr<ID3D11Buffer> mIndexBuffer = nullptr; // �C���f�b�N�X�o�b�t�@
	Vertex mVertex[4]; // ��`�S���_
	XMFLOAT4X4 mWorldmtx; // ���[���h�ϊ��s��
public:
	XMFLOAT2 mPos;			//���W
	XMFLOAT2 mBreadth;		//�� x:width y:height
	CSprite2DComponent(CActor& owner, std::string fileName, int priority = 45);

	void Update()override;
};