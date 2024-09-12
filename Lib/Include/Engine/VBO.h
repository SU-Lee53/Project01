#pragma once

enum class BufferType
{
	Vertex = 0,
	Color,
	Element,

	End
};

enum
{
	BUFFER_TYPE_COUNT = static_cast<int>(BufferType::End)
};

class VBO
{
public:
	VBO();
	~VBO();

public:
	// Getter
	void SetVertexBuffer(const vector<float>& buffer) { _vertices = vector<float>(buffer.begin(), buffer.end()); }
	void SetColorBuffer(const vector<float>& buffer) { _colors = vector<float>(buffer.begin(), buffer.end()); }
	void SetIndexBuffer(const vector<unsigned int>& buffer) { _indices = vector<unsigned int>(buffer.begin(), buffer.end()); }

	// Setter
	vector<float>& GetVertexBuffer() { return _vertices; }
	vector<float>& GetColorBuffer() { return _colors; }
	vector<unsigned>& GetIndexBuffer() { return _indices; }

private:
	array<unsigned int, BUFFER_TYPE_COUNT> _ids;

private:
	vector<float> _vertices;
	vector<unsigned int> _indices;
	vector<float> _colors;

};

