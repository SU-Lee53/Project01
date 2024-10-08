#pragma once

class SamplerState
{
public:
    SamplerState();
    ~SamplerState();

    ComPtr<ID3D11SamplerState> GetComPtr() const { return _samplerState; }

    void Create();

private:
    ComPtr<ID3D11SamplerState> _samplerState;
};

