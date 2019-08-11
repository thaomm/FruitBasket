#pragma once
#include "Sprite2D.h"
class Bomb :
	public Sprite2D
{
public:
	Bomb(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Bomb();
	bool		IsActive();
	void		SetActive(bool status);

	void		Update(float deltaTime) override;

	void		SetColliderSize(float size);
	float		GetColliderSize();

	void		SetDamage(float damage);
	float		GetDamage();

private:
	int		m_Heal;
	bool	m_active;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_Damage;
	float	m_SizeCollider;

	float distance(Vector2 pos, Vector2 target);
};

