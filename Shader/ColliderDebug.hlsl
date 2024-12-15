#include "global.hlsl"

cbuffer DebugColor : register(b5)
{
    float4 color;
}

DEBUG_OUTPUT DEBUG_VS(DEBUG_INPUT input)
{
    DEBUG_OUTPUT output;
    
    output.position = mul(input.position, matLocal);
    output.position = mul(output.position, matWorld);
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProjection);
    output.color = color;
    return output;
}

float4 DEBUG_PS(DEBUG_OUTPUT input) : SV_Target
{
    return input.color;
}