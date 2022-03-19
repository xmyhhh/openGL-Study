//#pragma once
#ifndef game_H
#define game_H
#include <glad/glad.h>
#include <vector>
#include <gameLevel.h>
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
class Game
{
public:
	// 游戏状态
	GameState  State;
	GLboolean  Keys[1024];
	GLuint     Width, Height;
	std::vector<GameLevel> Levels;
	GLuint                 Level;
	// 构造函数/析构函数
	Game(GLuint width, GLuint height);
	~Game();
	// 初始化游戏状态（加载所有的着色器/纹理/关卡）
	void Init();
	// 游戏循环
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render(); 
	void DoCollisions();
	void ResetLevel();
	void ResetPlayer();
};

#endif
