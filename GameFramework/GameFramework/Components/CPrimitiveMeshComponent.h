//!
//! @file
//! @brief �v���~�e�B�u���b�V���R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <string>

#include "../Interfaces/IRender.h"
#include "../Data/MeshDataDefinition.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class CRenderComponent;

//! @brief �v���~�e�B�u���b�V���R���|�[�l���g�N���X
template<class VertexType = SVertexColor>
class CPrimitiveMeshComponent :public CComponent , public IRender
{
protected:
	ComPtr<ID3D11Buffer> mVertexBuffer;			//!< ���_�o�b�t�@
	ComPtr<ID3D11Buffer> mIndexBuffer;			//!< �C���f�b�N�X�o�b�t�@

	CRenderComponent& mRenderComponent;			//!< �����_�[�R���|�[�l���g

	std::vector<VertexType> mVertices;			//!< ���_�f�[�^
	std::vector<unsigned int> mIndices;			//!< �C���f�b�N�X�f�[�^

	XMFLOAT4 mColor;							//!< �F���

	bool mIsTranslucent = false;				//!< ���������ǂ���

	//!
	//! @brief ������
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	virtual void Init(std::string vertexShaderPath , std::string pixelShaderPath);

	//! @brief ���_�f�[�^�쐬
	virtual void CreateVertexData() = 0;

	//! @brief �C���f�b�N�X�f�[�^�쐬
	virtual void CreateIndexData() = 0;

	//! @brief ���_&�C���f�b�N�X�o�b�t�@����
	void GenerateVertexAndIndexBuffer();

	//! @brief ���������ǂ����̃`�F�b�N
	void CheckTranslucent()
	{
		//�A���t�@�l��1�����Ȃ�
		if(mColor.w < 1.0f)
		{
			mIsTranslucent = true;
		}
	}

	//! @brief �X�V
	void Update()override;

	//! @brief �`��
	void Render()override;

public:
	CTransform Transform;			//!< �g�����X�t�H�[��

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] color �F���
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	CPrimitiveMeshComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color , std::string vertexShaderPath , std::string pixelShaderPath);

	//! @brief ���_�o�b�t�@�X�V
	void UpdateVertexBuffer();

	const XMFLOAT4& GetColor()const
	{
		return mColor;
	}

	void SetColor(const XMFLOAT4& color);

};