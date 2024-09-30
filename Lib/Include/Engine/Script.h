#pragma once

class GameObject;

class Script
{
public:
	Script();
	virtual ~Script();

public:
	virtual void Init();
	virtual void Update();

public:
	void SetOwner(shared_ptr<GameObject> obj) { _owner = obj; }
	shared_ptr<GameObject> GetOwner() const;

private:
	weak_ptr<GameObject> _owner;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Script;

};

