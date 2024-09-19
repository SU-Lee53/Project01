#pragma once


// To get _bindingPoint, you MUST use UBO<T>::GetBindingPoint()
static unsigned int _bindingPointCounter = 0;

template <typename T>
class UBO
{
public:
	UBO();
	~UBO();

public:
	void Create();

public:
	unsigned int GetID() { return _id; }

	template<typename U>
	void SetSubData(const U& data);
private:
	unsigned int GetBindingPoint() { return ++_bindingPointCounter; }
	void SetBindingPoint() { _bindingPoint = GetBindingPoint(); }

public:
	void BindUniformBlock(string blockName);

private:
	unsigned int _id = 0;

private:
	unsigned int _bindingPoint = 0;
	unsigned int _offset = 0;
};

template<typename T>
inline UBO<T>::UBO()
{
	_bindingPoint = GetBindingPoint();
}

template<typename T>
inline UBO<T>::~UBO()
{
}

template<typename T>
inline void UBO<T>::Create()
{
	glGenBuffers(1, &_id);
	glBindBuffer(GL_UNIFORM_BUFFER, _id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(T), /* ? */NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, _bindingPoint);
	glBindBufferRange(
		GL_UNIFORM_BUFFER,
		_bindingPoint,
		_id,
		0,
		sizeof(T)
	);
}

template<typename T>
inline void UBO<T>::BindUniformBlock(string blockName)
{
	unsigned int loc = RENDER->GetShader()->GetUniformBlockLocation(blockName);
	
	SetBindingPoint();
	glUniformBlockBinding(RENDER->GetShader()->GetID(), loc, _bindingPoint);

	Manager::GetInstance().GetManager<MANAGER_TYPE::Render>();
}

template<typename T>
template<typename U>
inline void UBO<T>::SetSubData(const U& data)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _id);
	glBufferSubData(GL_UNIFORM_BUFFER, _offset, sizeof(U), &data);
	glBindBuffer(GL_UNIFORM_BUFFER, _bindingPoint);

	_offset += sizeof(U);
}
