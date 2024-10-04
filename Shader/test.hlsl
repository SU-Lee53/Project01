#include "global.hlsl"

// VS
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    float4 position = mul(input.position, matWorld);
    position = mul(position, matView);
    position = mul(position, matProjection);
    
    output.position = position;
    output.uv = input.uv;
    
    return output;
}

Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
Texture2D specularMap : register(t2);

SamplerState sampler0 : register(s0);

// PS
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = diffuseMap.Sample(sampler0, input.uv);
    return color;
}