#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

public:
	ComPtr<ID3D11Buffer> GetComPtr() const {return _buffer; }
	uint32 GetStride() const { return _stride; }
	uint32 GetOffset() const { return _offset; }
	uint32 GetCount() const { return _count; }

public:
	template <typename T>
	void Create(const vector<T>& vertices)
	{
		_stride = sizeof(T);
		_count = static_cast<uint32>(vertices.size());

		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(desc));
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.ByteWidth = static_cast<uint32>(_stride * _count);
		}

		D3D11_SUBRESOURCE_DATA data;
		memset(&data, 0, sizeof(data));
		data.pSysMem = vertices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &data, _buffer.GetAddressOf());
		HR_ASSERT(hr);
	}

private:
	ComPtr<ID3D11Buffer> _buffer;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;
};

