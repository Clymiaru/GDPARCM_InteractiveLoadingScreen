#pragma once
#include "Utils/TypeAlias.h"

#define MAKE_COMPONENT(component)											\
	static String GetComponentName() { return #component; }					\
	virtual const char* GetName() const override { return #component; }

// A Component is just data where some systems can use to make stuff happen for entity types 
class Entity;
class AComponent
{
public:
	explicit AComponent(Entity& owner);
	virtual ~AComponent();
	
	Entity& GetOwner() const;
	
	virtual const char* GetName() const = 0;
	virtual String ToString() const
	{
		return GetName();
	}
	
	virtual AComponent* Clone(Entity& newOwner) = 0;
protected:
	Entity& m_Owner;
};

