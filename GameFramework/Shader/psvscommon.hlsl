Texture2D g_Tex : register(t0); // �e�N�X�`��
SamplerState g_SamplerLinear : register(s0); // �T���v���[

struct PointLight
{
    float4 LightPos;
    float4 Attenuation;
};
    
struct SpotLight
{
    float4 LightPos;
    float4 Attenuation;
    float4 Direction;
    float Angle;
};

//--------------------------------------------------------------------------------------
// �R���X�^���g�o�b�t�@
//--------------------------------------------------------------------------------------
cbuffer ConstantBufferWorld : register(b0)
{
    matrix World;
}

cbuffer ConstantBufferView : register(b1)
{
    matrix View;
}

cbuffer ConstantBufferProjection : register(b2)
{
    matrix Projection;
}

cbuffer ConstantBufferMaterial : register(b3)
{
    float4 ambientMaterial;
    float4 diffuseMaterial;
    float4 specularMaterial;
}

cbuffer ConstantBufferLight : register(b4)
{
    float4 EyePos;                  // ���_�ʒu
    float4 LightDirection;          // ���̕���
    float4 Ambient;                 // ����
    PointLight PointLights[10];
    SpotLight SpotLights[10];
}

cbuffer ConstantBufferViewPort : register(b5)
{
    uint4 ViewportWidth;        // �r���[�|�[�g��
    uint4 ViewportHeight;       // �r���[�|�[�g����
};


//--------------------------------------------------------------------------------------
// �\���̒�`
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
    float2 Tex : TEXCOORD;
    float4 WPos : TEXCOORD1;
    float4 Normal : TEXCOORD2;
};

