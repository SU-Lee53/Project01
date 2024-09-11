#pragma once
class VAO
{

private:
	template <typename T, typename = enable_if_t<disjunction_v<is_integral<T>, is_floating_point<T>>>>
	struct Buffer
	{
		int id = 0;
		vector<T> buffer;
	};


	Buffer<float> _vertices;
	Buffer<unsigned int> _indices;
	Buffer<float> _colors;
};

