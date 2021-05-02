#pragma once
#include "Utils/TypeAlias.h"

class AScene
{
public:
	explicit AScene(StringRef name);
	virtual ~AScene() = default;
	
	virtual void LoadResources() = 0;
	virtual void CreateEntities() = 0;
	
	virtual void Initialize() = 0;
	virtual void Deinitialize() = 0;
	
	virtual void DestroyEntities();
	virtual void UnloadResources() = 0;
	
	StringRef GetName() const;
private:
	String m_Name;
};
