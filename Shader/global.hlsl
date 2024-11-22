#ifndef __GLOBAL__
#define __GLOBAL__

////////////////////
// IN_OUT structs //
////////////////////

struct VS_INPUT
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct DEBUG_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct DEBUG_OUTPUT
{
    float4 position : SV_POSITION;
    float3 worldPosition : POSITION1;
    float4 color : COLOR;
};

/////////////////////
// ConstantBuffers //
/////////////////////

cbuffer CameraData : register(b0)
{
    row_major matrix matView;
    row_major matrix matProjection;
    row_major matrix matViewInv;
}

cbuffer TransformData : register(b1)
{
    row_major matrix matLocal;
    row_major matrix matWorld;
}


Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
Texture2D specularMap : register(t2);

SamplerState sampler0 : register(s0);





#endif