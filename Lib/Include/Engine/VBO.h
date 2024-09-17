#pragma once

enum class BUFFER_TYPE
{
	Vertex = 0,
	Color,
	Index,

	End
};

enum
{
	BUFFER_TYPE_COUNT = static_cast<int>(BUFFER_TYPE::End)
};

template <typename T, BUFFER_TYPE bufTy>
class VBO
{
public:
	using elementType = T;

public:
	VBO();
	~VBO();

public:
	// Getter
	void SetBuffer(const vector<T>& buffer) { _data = vector<T>(buffer.begin(), buffer.end()); }

	// Setter
	vector<T>& GetBufferData() { return _data; }
	unsigned int& GetID() { return _id; }

private:
	unsigned int _id;

private:
	vector<T> _data;

};

template<typename T, BUFFER_TYPE bufTy>
inline VBO<T, bufTy>::VBO()
{
}

template<typename T, BUFFER_TYPE bufTy>
inline VBO<T, bufTy>::~VBO()
{
}
