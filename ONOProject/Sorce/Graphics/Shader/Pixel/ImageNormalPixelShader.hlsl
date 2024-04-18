#include"PixelShader2DHeader.hlsli"

Texture2D maskTex : register(t1); //マスク画像
Texture2D frameTex : register(t2); //フレーム画像

PS_OUTPUT main(PS_INPUT input) : SV_TARGET
{
    float4 result = float4(0.0f, 0.0f, 0.0f, 0.0f);

    result = tex.Sample(texSampler, input.uv);
    if (result.a <= 0.0f)
    {
        discard;
    }
    
    return result;
}