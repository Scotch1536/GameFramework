#include	"psvscommon.hlsl"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(float4 Pos : POSITION,
				float2 Tex : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

	// ���W�ϊ�
    Pos.w = 1.0f;
    output.Pos = mul(Pos, World);
    output.Pos = mul(output.Pos, Projection);

	// �e�N�X�`�����W�Z�b�g
    output.Tex = Tex;
    
	// �J���[�l�Z�b�g
    output.Color = 1.0f;
    return output;
}
