#pragma once

class VBO
{
public:



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
	int _id;

private:

	vector<float> _vertices;
	vector<unsigned int> _indices;
	vector<float> _colors;
};

