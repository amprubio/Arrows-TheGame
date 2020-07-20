#pragma once
class GameObject
{
public:	
	GameObject(){}
	virtual ~GameObject(){}
	
	virtual void render() const = 0;
	virtual bool update() = 0;
};