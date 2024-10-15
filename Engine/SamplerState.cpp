#include "EnginePch.h"
#include "SamplerState.h"

SamplerState::SamplerState()
{

}

SamplerState::~SamplerState()
{
}

void SamplerState::Create()
{
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    {
        desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        desc.BorderColor[0] = 1;	// R 
        desc.BorderColor[1] = 0;	// G
        desc.BorderColor[2] = 0;	// B
        desc.BorderColor[3] = 1;	// A
        desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        desc.MaxAnisotropy = 16;
        desc.MaxLOD = FLT_MAX;
        desc.MinLOD = FLT_MAX;
        desc.MipLODBias = 0.0f;
    }

    HRESULT hr = DEVICE->CreateSamplerState(&desc, _samplerState.GetAddressOf());
    HR_ASSERT(hr);
}
