#include "EnginePch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{

}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Create(const vector<uint32>& indices)
{
	_stride = sizeof(uint32);
	_count = static_cast<uint32>(indices.size());

	D3D11_BUFFER_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = static_cast<uint32>(_stride * _count);

	D3D11_SUBRESOURCE_DATA data;
	memset(&data, 0, sizeof(data));
	data.pSysMem = indices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &data, _buffer.GetAddressOf());
	HR_ASSERT(hr);
}
