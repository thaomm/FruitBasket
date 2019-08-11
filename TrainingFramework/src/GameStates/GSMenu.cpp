#include "GSMenu.h"

GSMenu::GSMenu()
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");
	
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	//help button
	texture = ResourceManagers::GetInstance()->GetTexture("button_help");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 400);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_HELP);
		});
	m_listButton.push_back(button);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 500);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 600);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::HandleMouseEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
