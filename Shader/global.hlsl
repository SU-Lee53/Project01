#ifndef __GLOBAL__
#define __GLOBAL__

//struct VS_INPUT
//{
//    float4 position : POSITION;
//    float4 color : COLOR;
//};

//struct VS_OUTPUT
//{
//    float4 position : SV_POSITION;
//    float4 color : COLOR;
//};

struct VS_INPUT
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
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

#endif