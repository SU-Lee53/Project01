#pragma once

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

	T GetBufferData() { return _data; }
	void SetBufferData(const T& data) { _data = data; }

private:
	unsigned int _id;

private:
	T _data;
};

template<typename T>
inline UBO<T>::UBO()
{
}

template<typename T>
inline UBO<T>::~UBO()
{
}

template<typename T>
inline void UBO<T>::Create()
{

}
