#pragma once

template <typename T>
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

public:
	ComPtr<ID3D11Buffer> GetComPtr() const { return _buffer; }

public:
	void Create()
	{
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(desc));
		{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth = sizeof(T);
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, _buffer.GetAddressOf());
		HR_ASSERT(hr);
	}

	void PushData(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		memset(&subResource, 0, sizeof(subResource));

		DC->Map(_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		{
			memcpy(&subResource, &data, sizeof(T));
		}
		DC->Unmap(_buffer.Get(), 0);
	}


private:
	ComPtr<ID3D11Buffer> _buffer;

};

template<typename T>
inline ConstantBuffer<T>::ConstantBuffer()
{
}

template<typename T>
inline ConstantBuffer<T>::~ConstantBuffer()
{
}
