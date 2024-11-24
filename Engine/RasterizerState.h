#pragma once
class RasterizerState
{
public:
    RasterizerState();
    ~RasterizerState();

    ComPtr<ID3D11RasterizerState> GetComPtr() const { return _rasterizerState; }

    void Create();

public:
    void SetState(ComPtr<ID3D11RasterizerState> rs) { _rasterizerState = rs; }

private:
    ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
};

