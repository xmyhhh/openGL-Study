#include "game.h"
#include "resource_manager.h"
#include "spriteRenderer.h"


SpriteRenderer* Renderer;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}

void Game::Init()
{
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
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{

	Texture2D texture2d = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(texture2d,
		glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}