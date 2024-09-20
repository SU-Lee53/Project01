//#include "global.hlsl"

struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

cbuffer CameraData : register(b0)
{
    row_major matrix matView;
    row_major matrix matProjection;
}

cbuffer TransformData : register(b1)
{
    row_major matrix matWorld;
}
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