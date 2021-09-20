#include	"psvscommon.hlsl"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(float4 Pos : POSITION,
                float4 Color : COLOR)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

	// ���W�ϊ�
    Pos.w = 1.0f;
    output.Pos = mul(Pos, World);
    output.Pos = mul(output.Pos, Projection);
    
	// �J���[�l�Z�b�g
    output.Color = Color;
    return output;
}
