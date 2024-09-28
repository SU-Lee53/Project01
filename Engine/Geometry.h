#pragma once

template <typename T>
class Geometry
{
public:
	Geometry();
	~Geometry();

public:
	const vector<T>& GetVertices() { return _vertices; }
	const vector<uint32>& GetIndices() { return _indices; }

	void AddVertex(const T& vertex) { _vertices.push_back(vertex); }
	void AddVertices(const vector<T>& vertices) { _vertices.insert(_vertices.end(), vertices.begin(), vertices.end()); }
	void SetVertices(const vector<T>& vertices) { _vertices = vertices; }

	void AddIndex(uint32 index) { _indices.push_back(index); }
	void AddIndices(const vector<uint32>& indices) { _indices.insert(_indices.end(), indices.begin(), indices.end()); }
	void SetIndices(const vector<uint32>& indices) { _indices = indices; }


private:
	vector<T> _vertices;
	vector<uint32> _indices;
};

template<typename T>
inline Geometry<T>::Geometry()
{
}

template<typename T>
inline Geometry<T>::~Geometry()
{
}
