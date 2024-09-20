#include "global.hlsl"

// VS
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    float4 position = mul(input.position, matWorld);
    position = mul(position, matView);
    position = mul(position, matProjection);
    
    output.position = position;
    output.color = input.color;
    
    return output;
}

// PS
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = input.color;
    return color;
}