#include "pch.h"
#include "AScene.h"

AScene::AScene(StringRef name) :
	m_Name(name)
{
}

void AScene::DestroyEntities()
{
	// EntityManager::GetInstance().DestroyInScene(entities, GetName());
}

StringRef AScene::GetName() const
{
	return m_Name;
}