#include "global.hlsl"
#include "light.hlsl"

// PS
float4 TestPS(VS_OUTPUT input) : SV_Target
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    
    //return float4(input.normal, 1.f);
    return color;
}