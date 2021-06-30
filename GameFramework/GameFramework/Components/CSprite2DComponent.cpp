#include "CSprite2DComponent.h"
#include "../ExternalCode/shaderhashmap.h"

CSprite2DComponent::CSprite2DComponent(CActor& owner, std::string fileName, int priority) :CComponent(owner, priority)
{
	// �g�p���钸�_�V�F�[�_�[��
	const char* vsfilename[] = {
		"shader/basicvs.hlsl"
	};

	// �g�p����s�N�Z���V�F�[�_�[��
	const char* psfilename[] = {
		"shader/basicps.hlsl", //�e�N�X�`���\��p
		"shader/basicnotexps.hlsl" //�e�N�X�`���\��Ȃ��p
	};

	// �f�o�C�X���擾����
	ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

	DX11MtxIdentity(mWorldmtx); // �����p��

	// �s�N�Z���V�F�[�_�[�𐶐�
	bool sts = ShaderHashmap::GetInstance()->SetPixelShader(psfilename[0]);
	if (!sts) {
		MessageBox(nullptr, "SetPixelShader error(basicps.hlsl)", "error", MB_OK);
		return;
	}

	// �s�N�Z���V�F�[�_�[�𐶐�
	sts = ShaderHashmap::GetInstance()->SetPixelShader(psfilename[1]);
	if (!sts) {
		MessageBox(nullptr, "SetPixelShader error(basicnotexps.hlsl)", "error", MB_OK);
		return;
	}

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// �G�������g��
	unsigned int numElements = ARRAYSIZE(layout);

	// ���_�V�F�[�_�[�𐶐�
	sts = ShaderHashmap::GetInstance()->SetVertexShader(vsfilename[0], layout, numElements);
	// ��1�����F���_�V�F�[�_�[�t�@�C����
	// ��2�����F���_���C�A�E�g
	// ��3�����F�G�������g��

// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	sts = CreateVertexBufferWrite(device, sizeof(Vertex), 4, mVertex, &(mVertexBuffer));
	// ��1�����F�f�o�C�X�I�u�W�F�N�g
	// ��2�����F1���_������o�C�g��
	// ��3�����F���_��
	// ��4�����F���_�f�[�^�i�[�������擪�A�h���X
	// ��5�����F���_�o�b�t�@

	if (!sts) {
		MessageBox(nullptr, "CreateVertexBuffer error", "error", MB_OK);
		return;
	}

	// �C���f�b�N�X�o�b�t�@�𐶐�
	uint32_t index[4] = { 0,1,2,3 };
	sts = CreateIndexBuffer(device, 4, index, &(mIndexBuffer));
	// ��1�����F�f�o�C�X�I�u�W�F�N�g
	// ��2�����F�C���f�b�N�X��
	// ��3�����F�C���f�b�N�X�i�[�������擪�A�h���X
	// ��4�����F�C���f�b�N�X�o�b�t�@

	if (!sts) {
		MessageBox(nullptr, "CreateIndexBuffer error", "error", MB_OK);
		return;
	}

	//UV���W�����l���
	mUv[0].x = 0.0f;
	mUv[0].y = 0.0f;
	mUv[1].x = 1.0f;
	mUv[1].y = 0.0f;
	mUv[2].x = 0.0f;
	mUv[2].y = 1.0f;
	mUv[3].x = 1.0f;
	mUv[3].y = 1.0f;
}

void CSprite2DComponent::Update()
{
	// Z����]
	DX11MtxRotationZ(mAngle, mWorldmtx);

	// �ʒu���Z�b�g
	mWorldmtx._41 = mPos.x;
	mWorldmtx._42 = mPos.y;
	mWorldmtx._43 = 0;

	// ���_�f�[�^�X�V
	Vertex	v[4] = {
		// ���W                                             // �J���[    // UV	
		XMFLOAT3(-mBreadth.x / 2.0f,-mBreadth.y / 2.0f, 0), mColor, mUv[0],
		XMFLOAT3( mBreadth.x / 2.0f,-mBreadth.y / 2.0f, 0), mColor, mUv[1],
		XMFLOAT3(-mBreadth.x / 2.0f, mBreadth.y / 2.0f, 0), mColor, mUv[2],
		XMFLOAT3( mBreadth.x / 2.0f, mBreadth.y / 2.0f, 0), mColor, mUv[3]
	};

	for (int i = 0; i < 4; i++) {
		mVertex[i] = v[i];
	}

	// ���_�o�b�t�@�X�V
	D3D11_MAPPED_SUBRESOURCE pData;
	ID3D11DeviceContext* devcontext;
	devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();
	HRESULT hr = devcontext->Map(mVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(mVertex), sizeof(Vertex) * 4);
		devcontext->Unmap(mVertexBuffer.Get(), 0);
	}
}