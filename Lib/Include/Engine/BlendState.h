#pragma once
class BlendState
{
public:
    BlendState();
    ~BlendState();

    const float* GetBlendFactor() const { return &_blendFactor; }
    uint32 GetSampleMask() const { return _sampleMask; }
    ComPtr<ID3D11BlendState> GetComPtr() const { return _blendState; }

    void Create(D3D11_RENDER_TARGET_BLEND_DESC blendDesc =
        {
            true,
            D3D11_BLEND_SRC_ALPHA,
            D3D11_BLEND_INV_SRC_ALPHA,
            D3D11_BLEND_OP_ADD,
            D3D11_BLEND_ONE,
            D3D11_BLEND_ZERO,
            D3D11_BLEND_OP_ADD,
            D3D11_COLOR_WRITE_ENABLE_ALL
        }, float factor = 0.f);


private:
    ComPtr<ID3D11BlendState> _blendState;
    float _blendFactor = 0xFFFFFFFF;
    uint32 _sampleMask = 0xFFFFFFFF;
};

