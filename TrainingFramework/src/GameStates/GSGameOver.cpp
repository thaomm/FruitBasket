#include "GSGameOver.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>

GSGameOver::GSGameOver()
{
}

GSGameOver::~GSGameOver()
{
}

void GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_gameover");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 480);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 580);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	//score
	int score = GSPlay::m_score;
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("pixel");
	m_FinalScore = std::make_shared< Text>(shader, font, "x " + std::to_string(score), TEXT_COLOR::RED, 0.8);
	m_FinalScore->Set2DPosition(Vector2(215, 378));
}

void GSGameOver::Exit()
{
}

void GSGameOver::Pause()
{
}

void GSGameOver::Resume()
{
}

void GSGameOver::HandleEvents()
{
}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSGameOver::HandleMouseEvents(int x, int y)
{
}

void GSGameOver::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSGameOver::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_FinalScore->Draw();
}
