#include	"psvscommon.hlsl"

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main(float4 Pos : POSITION,
                float4 Color : COLOR,
				float2 Tex : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

	// 座標変換
    Pos.w = 1.0f;
    output.Pos = mul(Pos, World);
    output.Pos = mul(output.Pos, Projection);

	// テクスチャ座標セット
    output.Tex = Tex;
    
	// カラー値セット
    output.Color = Color;
    return output;
}
