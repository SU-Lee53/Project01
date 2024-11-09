#ifndef __LIGHT__
#define __LIGHT__

#include "global.hlsl"

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

cbuffer MaterialData : register(b2)
{
    MaterialDesc Material;
}

//////////////////
// Global Light //
//////////////////

struct GlobalLightDesc
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 emissive;
    float3 direction;
    float padding;
};

cbuffer GlobalLightData : register(b3)
{
    GlobalLightDesc GlobalLight;
};

////////////////
// Spot Light //
////////////////

struct SpotLightDesc
{
    float4 sPosition;
    // 16
    
    float3 sLightDirection;
    float padding0;
    // 16
    
    float3 sInnerConeDirPositive;
    float padding1;
    // 16
    
    float3 sOuterConeDirPositive;
    float padding2;
    // 16
    
    float4 sAmbient;
    float4 sDiffuse;
    float4 sSpecular;
    float4 sEmissive;
    // 16 * 4
};

cbuffer SpotLightData : register(b4)
{
    SpotLightDesc SpotLight;
};

////////////////////
// Normal Mapping //
////////////////////

void ComputeNormalMapping(inout float3 normal, float3 tangent, float2 uv)
{
    float4 map = normalMap.Sample(sampler0, uv);
    if(any(map.rgb) == false)
        return;
    
    float3 N = normalize(normal);
    float3 T = normalize(tangent);
    float3 B = normalize(cross(N, T));
    float3x3 TBN = float3x3(T, B, N);
    
    float3 tangentSpaceNormal = (map.rgb * 2.0f - 1.0f);
    float3 worldNormal = mul(tangentSpaceNormal, TBN);
    
    normal = worldNormal;
}

float4 ComputeAmbient(float2 uv)
{
    float4 color = GlobalLight.ambient * Material.ambient;
    return color;
}

float4 ComputeDiffuse(float3 normal, float2 uv)
{
    float4 color = diffuseMap.Sample(sampler0, uv);
    float value = max(dot(-GlobalLight.direction, normalize(normal)), 0);
    return color * value * GlobalLight.diffuse * Material.diffuse;
}

float4 ComputeSpecular(float3 normal, float2 uv, float3 worldPos, int power)
{
    float3 R = normalize(reflect(-GlobalLight.direction, normalize(normal)));
    float3 cameraPos = -matViewInv._41_42_43;
    float3 E = normalize(cameraPos - worldPos);
    
    float value = max(dot(R, E), 0);
    float specular = pow(value, power);
    //float4 color = specularMap.Sample(sampler0, uv) * Material.specular;
    
    return GlobalLight.specular * Material.specular * specular;
    
}

float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    // ambient
    {
        ambientColor = ComputeAmbient(uv);
    }
    
    // diffuse
    {
        diffuseColor = ComputeDiffuse(normal, uv);
    }
    
    // specular
    {
        specularColor = ComputeSpecular(normal, uv, worldPosition, 1024);
    }
    
    // Emissive
    {
        emissiveColor = Material.emissive;
    }
    
    return ambientColor + diffuseColor + specularColor + emissiveColor;
    
}



#endif