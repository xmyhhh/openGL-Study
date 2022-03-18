#include "game.h"
#include "resource_manager.h"
#include "spriteRenderer.h"
#include <gameLevel.h>
#include<glfw/glfw3.h>
#include<iostream>
SpriteRenderer* Renderer;
GameObject* Player;

// 初始化挡板的大小
const glm::vec2 PLAYER_SIZE(100, 20);
// 初始化当班的速率
const GLfloat PLAYER_VELOCITY(500.0f);

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

void Game::Init()
{
	// Start Game within Menu State
	this->State = GAME_ACTIVE;
	//const glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	// 加载着色器
	ResourceManager::LoadShader("code/shader/sprite.vs", "code/shader/sprite.fs", nullptr, "sprite");
	// 配置着色器
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
		static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// 设置专用于渲染的控制
	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);
	// 加载纹理
	ResourceManager::LoadTexture("resource/textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("resource/textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("resource/textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("resource/textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("resource/textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("resource/textures/block_solid.png", GL_FALSE, "block_solid");

	// 加载关卡
	GameLevel one; one.Load("resource/level/one", this->Width, this->Height * 0.5);
	GameLevel two; two.Load("resource/level/two", this->Width, this->Height * 0.5);
	GameLevel three; three.Load("resource/level/three", this->Width, this->Height * 0.5);
	GameLevel four; four.Load("resource/level/four", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 1;
	glm::vec2 playerPos = glm::vec2(
		this->Width / 2 - PLAYER_SIZE.x / 2,
		this->Height - PLAYER_SIZE.y
	);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		// 移动挡板
		
		if (this->Keys[GLFW_KEY_A]== GL_TRUE)
		{
			if (Player->Position.x >= 0)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D]== GL_TRUE)
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
	}
}

void Game::Render()
{

	Texture2D texture2D_face = ResourceManager::GetTexture("face");
	Texture2D texture2D_bg = ResourceManager::GetTexture("background");


	if (this->State == GAME_ACTIVE)
	{
		// 绘制背景
		Renderer->DrawSprite(texture2D_bg,
			glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
		);
		// 绘制关卡
		this->Levels[this->Level].Draw(*Renderer);
		// 绘制player
		Player->Draw(*Renderer);
	}
	else {
		Renderer->DrawSprite(texture2D_face,
			glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}