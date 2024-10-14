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
    
    float3 tangentSpaceNormal = (map.rgb + 2.0f - 1.0f);
    float3 worldNormal = mul(tangentSpaceNormal, TBN);
    
    normal = worldNormal;
}


float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
    float4 ambientColor = 0;
    float4 diffuseColor = 0;
    float4 specularColor = 0;
    float4 emissiveColor = 0;
    
    // ambient
    {
        float4 color = GlobalLight.ambient * Material.ambient;
        ambientColor = diffuseMap.Sample(sampler0, uv) * color;
    }
    
    // diffuse
    {
        float4 color = diffuseMap.Sample(sampler0, uv);
        float value = dot(-GlobalLight.direction, normalize(normal));
        diffuseColor = color * value * GlobalLight.diffuse * Material.diffuse;
    }
    
    // specular
    {
        float3 R = GlobalLight.direction - (2 * normal * dot(GlobalLight.direction, normal));
        R = normalize(R);
    
        float3 cameraPosition = -matViewInv._41_42_43;
        float3 E = normalize(cameraPosition - worldPosition);
	
        float value = saturate(dot(R, E)); // same as clamp(0,1)
        float specular = pow(value, 10);
    
        specularColor = GlobalLight.specular * Material.specular * specular;
    }
    
    // Emissive
    {
        //float3 cameraPosition = -matViewInv._41_42_43;
        //float3 E = normalize(cameraPosition - worldPosition);
    
        //float value = saturate(dot(E, normal));
        //float emissive = 1.0f - value;
    
        //// min, max, x -> make smooth with hermite interpolation
        //emissive = smoothstep(0.0f, 1.0f, emissive);
        //emissive = pow(emissive, 2);
        //emissiveColor = Material.emissive * emissive;
        emissiveColor = Material.emissive;
    }
    
    return ambientColor + diffuseColor + specularColor + emissiveColor;
    
}



#endif