#pragma once
class RasterizerState
{
public:
    RasterizerState();
    ~RasterizerState();

    ComPtr<ID3D11RasterizerState> GetComPtr() const { return _rasterizerState; }

    void Create();

private:
    ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
};

