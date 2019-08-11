#pragma once
#include "gamestatebase.h"
#include <GameButton.h>


class Player;
class Bomb;
class Fruit;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleMouseEvents(int x, int y) override;

	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void Update(float deltaTime) override;
	void Draw() override;
	
	static int m_score;

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_scoreText;
	std::shared_ptr<Text>  m_playerHealText;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Bomb>> m_listBomb;
	std::vector<std::shared_ptr<Fruit>> m_listFruit;

	float m_SpawnCooldown;
	void CreateRandomFruit();
	void CreateRandomBomb();
};

