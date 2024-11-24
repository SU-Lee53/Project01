#include "global.hlsl"

DEBUG_OUTPUT DEBUG_VS(DEBUG_INPUT input)
{
    DEBUG_OUTPUT output;
    
    output.position = mul(input.position, matLocal);
    output.position = mul(output.position, matWorld);
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProjection);
    
    return output;
}

float4 DEBUG_PS(DEBUG_OUTPUT input) : SV_Target
{
    return input.color;
}