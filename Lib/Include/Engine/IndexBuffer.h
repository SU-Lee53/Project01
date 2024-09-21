#pragma once
class IndexBuffer
{
	IndexBuffer();
	~IndexBuffer();

public:
	ComPtr<ID3D11Buffer> GetComPtr() const { return _buffer; }
	uint32 GetStride() const { return _stride; }
	uint32 GetOffset() const { return _offset; }
	uint32 GetCount() const { return _count; }

public:
	void Create(const vector<uint32>& indices);

private:
	ComPtr<ID3D11Buffer> _buffer;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;
};

