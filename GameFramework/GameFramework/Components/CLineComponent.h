#pragma once

#include <array>
#include <string>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <d3d11.h>

#include "../Interfaces/IRender.h"
#include "../Data/VertexProto.h"
#include "CComponent.h"

//!
//! @file
//! @brief ���C���R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

using Microsoft::WRL::ComPtr;

//! @brief ���C���R���|�[�l���g�N���X
class CLineComponent :public CComponent , public IRender
{
private:
	ComPtr<ID3D11Buffer> mVertexBuffer;				//!< ���_�o�b�t�@
	ComPtr<ID3D11PixelShader> mPixelShader;			//!< �s�N�Z���V�F�[�_�[
	ComPtr<ID3D11VertexShader> mVertexShader;		//!< ���_�V�F�[�_�[
	ComPtr<ID3D11InputLayout> mVertexLayout;		//!< ���_�t�H�[�}�b�g

	std::array<SVertexLine , 2> mVertices;		//!< ���_

	XMFLOAT3 mStartPoint;						//!< �n�_
	XMFLOAT3 mEndPoint;							//!< �I�_
	XMFLOAT4 mColor;							//!< �F

	//! @brief �e�̃g�����X�t�H�[��
	//! @details �K�p�����g�����X�t�H�[���̃��[���h�ϊ��s��ɃX�P�[�����O�̂ݏ��O����
	//! �ϊ����{�����̂ň����ɒ��ӂ��K�v
	CTransform* mParentTransform;

	bool mShouldUpdate = false;			//!< �X�V���ׂ���

	//!
	//! @brief ������
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	void Init(std::string vertexShaderPath , std::string pixelShaderPath);

	//! @brief �`��
	void Render()override;

	//! @brief �X�V
	void Update()override;

	//!
	//! @brief ���_�̍X�V
	//! @param[in] 
	void UpdateVertex(void* source , int size);

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

public:
	//!
	//! @brief �R���X�g���N�^
	//! @details �n�_�ƏI�_�����񂾐������ꍇ�̃R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] start �n�_
	//! @param[in] end �I�_
	//! @param[in] color �F���
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//! @param[in] priority �D��x
	//!
	CLineComponent(CActor& owner , const XMFLOAT3& start ,const XMFLOAT3& end ,
		const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } , CTransform* parentTrans = nullptr ,
		std::string vertexShaderPath = "Shader/vsline.hlsl" , std::string pixelShaderPath = "Shader/psline.hlsl" , int priority = 90);

	//!
	//! @brief �R���X�g���N�^
	//! @details �n�_����̌����ƒ����Ő������ꍇ�̃R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] start �n�_
	//! @param[in] direction ����
	//! @param[in] length ����
	//! @param[in] color �F���
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//! @param[in] priority �D��x
	//!
	CLineComponent(CActor& owner ,const XMFLOAT3& start ,const XMFLOAT3& direction , float length ,
		const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } , CTransform* parentTrans = nullptr ,
		std::string vertexShaderPath = "Shader/vsline.hlsl" , std::string pixelShaderPath = "Shader/psline.hlsl" , int priority = 90);

	void SetStartPoint(const XMFLOAT3& point)
	{
		mShouldUpdate = true;

		mVertices.at(0).Pos = mStartPoint = point;
	}

	void SetEndPoint(const XMFLOAT3& point)
	{
		mShouldUpdate = true;

		mVertices.at(1).Pos = mEndPoint = point;
	}

	void SetColor(XMFLOAT4 color)
	{
		mVertices.at(0).Color = mVertices.at(1).Color = mColor = color;
	}
};