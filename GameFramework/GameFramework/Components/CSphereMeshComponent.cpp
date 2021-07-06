#include "../Actor/CActor.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/CDirectxGraphics.h"

#include "CSphereMeshComponent.h"
#include "CRenderComponent.h"

CSphereMeshComponent::CSphereMeshComponent(CActor& owner , float radius , int divNum , XMFLOAT4 color)
	:CComponent(owner , 100) ,
	mRenderComponent(*new CRenderComponent(owner)) ,
	mColor(color) ,
	mRadius(radius) ,
	mDivisionNumber(divNum) ,
	Transform(owner)
{
	if(mColor.w < 1.0f)
	{
		isAlpha = true;
	}
	else
	{
		//�A�N�^�[(owner)�Ƀ����_�[�S���̃R���|�[�l���g�Ƃ��ēo�^
		mOwnerInterface.AddRenderComponent(*this);
	}

	CreateVertex();
	CreateIndex();

	ID3D11Device* buf = CDirectXGraphics::GetInstance()->GetDXDevice();

	// ���_�o�b�t�@����
	bool sts = CreateVertexBufferWrite(buf , static_cast<unsigned int>(sizeof(SVertexUV)) ,
		static_cast<unsigned int>(mVertex.size()) ,
		mVertex.data() , &mVertexBuffer);
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(vertex buffer) error" , "Error" , MB_OK);
	}

	// �C���f�b�N�X�o�b�t�@����
	sts = CreateIndexBuffer(buf , static_cast<unsigned int>(mFace.size() * 3) ,
		mFace.data() , &mIndexBuffer);
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(index buffer) error" , "Error" , MB_OK);
	}

	// ���_�f�[�^�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , "Shader/vsnotex.hlsl");
	mRenderComponent.GeneratePixelShader("Shader/psnotex.hlsl");
}

void CSphereMeshComponent::CreateVertex()
{
	float azimuth = 0.0f;			// ���ʊp
	float elevation = 0.0f;			// �p

	XMFLOAT3 Normal;

	// ���ʊp�Ƌp���狅���b�V���̒��_�f�[�^���쐬
	for(unsigned int y = 0; y <= mDivisionNumber; y++)
	{
		elevation = (XM_PI* static_cast<float>(y)) / static_cast<float>(mDivisionNumber);		// �p���Z�b�g

		float r = mRadius * sinf(elevation);					// �p�ɉ��������a���v�Z

		for(unsigned int x = 0; x <= mDivisionNumber; x++)
		{
			azimuth = (2 * XM_PI * static_cast<float>(x)) / static_cast<float>(mDivisionNumber);		// ���ʊp���Z�b�g

			SVertexColor v;
			v.Pos.x = r * cosf(azimuth);
			v.Pos.y = mRadius * cosf(elevation);
			v.Pos.z = r * sinf(azimuth);

			DX11Vec3Normalize(Normal , Normal);			// �@�����v�Z
			v.Normal = Normal;							// �@�����Z�b�g

			v.Color = mColor;				// ���_�J���[

			mVertex.emplace_back(v);
		}
	}
}

void CSphereMeshComponent::CreateIndex()
{
	// �C���f�b�N�X����
	for(unsigned int y = 0; y < mDivisionNumber; y++)
	{
		for(unsigned int x = 0; x < mDivisionNumber; x++)
		{
			int count = (mDivisionNumber + 1)*y + x;			// ������W�̃C���f�b�N�X

			Face f;
			// �㔼��
			f.idx[0] = count;
			f.idx[1] = count + 1;
			f.idx[2] = count + 1 + (mDivisionNumber + 1);

			mFace.emplace_back(f);

			// ������
			f.idx[0] = count;
			f.idx[1] = count + (mDivisionNumber + 1) + 1;
			f.idx[2] = count + (mDivisionNumber + 1);

			mFace.emplace_back(f);
		}
	}
}

void CSphereMeshComponent::Update()
{
	if(isAlpha)mOwnerInterface.RequestAddAlphaRenderComponentToLevel(*this);
}

void CSphereMeshComponent::Render()
{
	Transform.RequestSetMatrix();

	mRenderComponent.Render(sizeof(SVertexColor) , static_cast<unsigned int>(mFace.size() * 3) , nullptr , mVertexBuffer.Get() , mIndexBuffer.Get() , nullptr);
}