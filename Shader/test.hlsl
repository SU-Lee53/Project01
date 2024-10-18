#include "global.hlsl"
#include "light.hlsl"

// VS
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.position = mul(input.position, matLocal);
    output.position = mul(output.position, matWorld);
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProjection);
    output.uv = input.uv;
    
    //output.normal = mul(input.normal, (float3x3) matLocal);
    output.normal = mul(input.normal, (float3x3) matWorld);
    
    //output.tangent = mul(input.tangent, (float3x3) matLocal);
    output.tangent = mul(input.tangent, (float3x3) matWorld);
    
    return output;
}

// PS
float4 PS(VS_OUTPUT input) : SV_Target
{
    ComputeNormalMapping(input.normal, input.tangent, input.uv);
    float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);
    
    //return float4(input.normal, 1.f);
    return color;
}