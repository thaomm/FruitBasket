#pragma once
#include "Sprite2D.h"
#include <Fruit.h>
#include <Bomb.h>

class Player : public Sprite2D
{
	
public:
	Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Player();

	void MoveToPossition(Vector2 pos);
	void Update(GLfloat deltatime) override;

	void CheckCollider(std::vector<std::shared_ptr<Fruit>> listFruit, std::vector<std::shared_ptr<Bomb>> listBomb);

	void		SetColliderSize(float size);
	float		GetColliderSize();

	void		SetHeal(int heal);
	int			GetHeal();
	bool		IsAlive();
private:
	Vector2 m_TargetPosition;
	int		m_Heal;
	bool	m_isAlive;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_SizeCollider;


	float distance(Vector2 pos, Vector2 target);
};
