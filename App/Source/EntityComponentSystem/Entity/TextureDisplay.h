#pragma once
#include "AGameObject.h"
#include "Threading/IExecutionEvent.h"
#include "Threading/ThreadPool.h"
class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay : public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();

	void Initialize() override;

	void ProcessInput(sf::Event event) override;

	void Update(float deltaTime) override;

	void OnFinishExecution() override;

private:
	enum class StreamingType
	{
		BATCH_LOAD = 0,
        SINGLE_STREAM = 1
    };

	const StreamingType m_StreamingType = StreamingType::SINGLE_STREAM;

	const int STREAMING_LOAD_DELAY = 100;
	const int MAX_COLUMN = 28;
	const int MAX_ROW    = 22;
	const int MAX_ICONS  = 480;

	int m_Ticks;
	bool m_HasStartedStreaming;
	int m_ColumnGrid;
	int m_RowGrid;
	int m_IconIndex;
	List<IconObject*> m_IconList;

	ThreadPool* m_ThreadPool = new ThreadPool("TextureDisplay", 8);

	void SpawnObject();
};
