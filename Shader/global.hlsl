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

////////////////////
// IN_OUT structs //
////////////////////

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

//////////////
// Material //
//////////////

struct MaterialDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
};


/////////////////////
// ConstantBuffers //
/////////////////////

cbuffer CameraData : register(b0)
{
    row_major matrix matView;
    row_major matrix matProjection;
}

cbuffer TransformData : register(b1)
{
    row_major matrix matLocal;
    row_major matrix matWorld;
}

cbuffer MaterialData : register(b2)
{
    MaterialDesc desc;
}






#endif