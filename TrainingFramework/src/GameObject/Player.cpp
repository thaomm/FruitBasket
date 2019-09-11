#include "Player.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>

Player::Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_TargetPosition = Vector2(0, 0);
	m_MaxCooldown = 0.1;
	m_Cooldown = 0.0;
	m_speed = 500;
	m_MaxSpeed = 500;
	m_Heal = 3;
	m_SizeCollider = 15;
	m_isAlive = true;
}

Player::~Player()
{
}


void Player::MoveToPossition(Vector2 pos)
{
	m_TargetPosition = pos;
}

void Player::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;

	if (m_Heal <= 0)
	{
		m_isAlive = false;
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
		SoundManager::GetInstance()->PlaySound("gameover");
		SoundManager::GetInstance()->PauseSound("background");

		return;
	}
	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltatime;
	}

	Vector2 pos = Get2DPosition();

	if (pos.x < m_TargetPosition.x){
		pos.x += m_speed * deltatime;
		if (pos.x > m_TargetPosition.x)	pos.x = m_TargetPosition.x;
	}
	if (pos.x > m_TargetPosition.x){
		pos.x -= m_speed * deltatime;
		if (pos.x < m_TargetPosition.x)	pos.x = m_TargetPosition.x;
	}
	Set2DPosition(pos);
}

float Player::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

void Player::CheckCollider(std::vector<std::shared_ptr<Fruit>> listFruit, std::vector<std::shared_ptr<Bomb>> listBomb)
{
	Vector2 pos = Get2DPosition();
	for (auto fruit : listFruit)
	{
		if (fruit->IsActive())
		{
			if (distance(pos, fruit->Get2DPosition()) < m_SizeCollider + fruit->GetColliderSize())
			{
				fruit->SetActive(false);
				GSPlay::m_score += 10;
				SoundManager::GetInstance()->PlaySound("score");
				SoundManager::GetInstance()->PlaySound("drop");
			}
		}
	}

	for (auto bomb : listBomb)
	{
		if (bomb->IsActive())
		{
			if (distance(pos, bomb->Get2DPosition()) < m_SizeCollider + bomb->GetColliderSize())
			{
				bomb->SetActive(false);
				m_Heal--;
				SoundManager::GetInstance()->PlaySound("explosive");
			}
		}
	}

}

void Player::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Player::GetColliderSize()
{
	return m_SizeCollider;
}

void Player::SetHeal(int heal)
{
	m_Heal = heal;
}

int Player::GetHeal()
{
	return m_Heal;
}

bool Player::IsAlive()
{
	return m_isAlive;
}
