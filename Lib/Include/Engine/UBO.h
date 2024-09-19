#pragma once

template <typename T>
class UBO
{
public:
	UBO();
	~UBO();

public:
	void Create(string blockName);

public:
	void SetName(const string& name) { _name = name; }
	string GetName() { return _name; }

public:
	template <typename U>
	void PushData(U& data);

private:
	string _name;
	unsigned int _id;
	unsigned int _index;

private:
	int _currOffset = 0;
};

template<typename T>
inline UBO<T>::UBO()
{
}

template<typename T>
inline UBO<T>::~UBO()
{
	glDeleteBuffers(1, &_id);
}

template<typename T>
inline void UBO<T>::Create(string blockName)
{
	_name = blockName;

	auto& shader = RENDER->GetShader();
	_index = shader->GetUniformBlockLocation(_name.c_str());
	glUniformBlockBinding(shader->GetID(), _index, 0);

	glGenBuffers(1, &_id);
	glBindBuffer(GL_UNIFORM_BUFFER, _id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(T), nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, _id, 0, sizeof(T));
}

template<typename T>
template<typename U>
inline void UBO<T>::PushData(U& data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _id);
	glBufferSubData(GL_UNIFORM_BUFFER, _currOffset, sizeof(U), value_ptr(data));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	_currOffset += sizeof(U);
}
