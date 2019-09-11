#include <sstream>
#include <iomanip>
#include <thread>

#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Text.h"
#include "Player.h"
#include "Fruit.h"
#include "Bomb.h"


int GSPlay::m_score = 0;
GSPlay::GSPlay()
{
	m_SpawnCooldown = 0.5;
	m_score = 0;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	//home button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth - 40, 40);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		SoundManager::GetInstance()->PauseSound("background");
		});
	m_listButton.push_back(button);

	//basket
	texture = ResourceManagers::GetInstance()->GetTexture("Player");
	m_Player = std::make_shared<Player >(model, shader, texture);
	m_Player->Set2DPosition(Application::screenWidth / 2, Application::screenHeight - 150);
	m_Player->MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 200));
	m_Player->SetSize(111, 60);
	if (!m_Player->GetHeal()) {

	}

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("pixel");
	m_playerHealText = std::make_shared< Text>(shader, font, "x ", TEXT_COLOR::RED, 0.8);
	m_playerHealText->Set2DPosition(Vector2(64, 52));
	m_scoreText = std::make_shared< Text>(shader, font, "x ", TEXT_COLOR::RED, 0.8);
	m_scoreText->Set2DPosition(Vector2(64, 100));

	//init sound
	SoundManager::GetInstance()->AddSound("explosive");
	SoundManager::GetInstance()->AddSound("score");
	SoundManager::GetInstance()->AddSound("background");
	SoundManager::GetInstance()->AddSound("drop");
	SoundManager::GetInstance()->AddSound("fall");
	SoundManager::GetInstance()->AddSound("gameover");
	SoundManager::GetInstance()->PlaySound("background");
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPlay::HandleMouseEvents(int x, int y)
{
	m_Player->MoveToPossition(Vector2(x, y));
}


void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{

	if (m_SpawnCooldown > 0)
	{
		m_SpawnCooldown -= deltaTime;
	}
	if (m_SpawnCooldown <= 0)
	{
		int flag = rand() % 2;
		if (flag == 1)		CreateRandomFruit();
		else CreateRandomBomb();
		m_SpawnCooldown = 0.5;
		SoundManager::GetInstance()->PlaySound("fall");
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	//update player
	if (m_Player->IsAlive())
	{
		m_Player->Update(deltaTime);

		m_Player->CheckCollider(m_listFruit, m_listBomb);
	}

	//update fruits
	for (auto fruit : m_listFruit)
	{
		if (fruit->IsActive())
		{
			fruit->Update(deltaTime);
		}
	}

	//update bomb
	for (auto bomb : m_listBomb)
	{
		if (bomb->IsActive())
		{
			bomb->Update(deltaTime);
		}
	}


	//update Score
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_score;
	std::string score = "x " + stream.str();
	m_scoreText->setText(score);
	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(0) << m_Player->GetHeal();
	std::string heal = "x " + stream2.str();
	m_playerHealText->setText(heal);
}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();

	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto fruit : m_listFruit)
		if (fruit->IsActive())
			fruit->Draw();

	for (auto bomb : m_listBomb)
		if (bomb->IsActive())
			bomb->Draw();

	if (m_Player->IsAlive())
		m_Player->Draw();

	//UI
	m_scoreText->Draw();
	m_playerHealText->Draw();
}

void GSPlay::CreateRandomFruit()
{

	int range = Application::screenWidth - 100 + 1;
	int num = rand() % range + 100;

	Vector2 pos;
	pos.x = num;
	pos.y = 10;

	for (auto fruit : m_listFruit)
	{
		if (!fruit->IsActive())
		{
			fruit->SetActive(true);
			fruit->Set2DPosition(pos);
			return;
		}
	}
	std::string fruitRand = "";
	int flag = rand() % 3;
	if (flag == 1) fruitRand = "fruit1";
	else if (flag == 2) fruitRand = "fruit2";
	else fruitRand = "fruit3";

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(fruitRand);

	std::shared_ptr<Fruit> fruit = std::make_shared<Fruit>(model, shader, texture);
	fruit->Set2DPosition(pos);
	fruit->SetSize(39, 52.5);
	m_listFruit.push_back(fruit);

}

void GSPlay::CreateRandomBomb()
{
	int range = Application::screenWidth - 100 + 1;
	int num = rand() % range + 100;

	Vector2 pos;
	pos.x = num;
	pos.y = 10;

	for (auto bomb : m_listBomb)
	{
		if (!bomb->IsActive())
		{
			bomb->SetActive(true);
			bomb->Set2DPosition(pos);
			return;
		}
	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bomb");

	std::shared_ptr<Bomb> bomb = std::make_shared<Bomb>(model, shader, texture);
	bomb->Set2DPosition(pos);
	bomb->SetSize(41, 37);
	m_listBomb.push_back(bomb);
	

}
