#include "Bomb.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>
#include "Player.h"

Bomb::Bomb(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_active = false;
	m_MaxCooldown = 10.3;
	m_Cooldown = 0.0;
	m_speed = 250;
	m_MaxSpeed = 500;
	m_Heal = 5;
	m_Damage = 10;
	m_SizeCollider = 20;
}

Bomb::~Bomb()
{
}

bool Bomb::IsActive()
{
	return m_active;
}

void Bomb::SetActive(bool status)
{
	m_active = status;
	m_Heal = 10;
}

void Bomb::Update(float deltaTime)
{
	if (!m_active)
		return;

	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltaTime;
	}

	Vector2 pos = Get2DPosition();
	pos.y = pos.y + m_speed * deltaTime;
	Set2DPosition(pos);

	if (pos.y > Application::screenHeight) {
		m_active = false;
	}
}

float Bomb::distance(Vector2 pos, Vector2 target)
{
		return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

void Bomb::SetDamage(float damage)
{
	m_Damage = damage;
}

float Bomb::GetDamage()
{
	return m_Damage;
}


void Bomb::SetColliderSize(float size)
{
	m_SizeCollider = size;
}

float Bomb::GetColliderSize()
{
	return m_SizeCollider;
}
