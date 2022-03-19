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
	// ��Ϸ״̬
	GameState  State;
	GLboolean  Keys[1024];
	GLuint     Width, Height;
	std::vector<GameLevel> Levels;
	GLuint                 Level;
	// ���캯��/��������
	Game(GLuint width, GLuint height);
	~Game();
	// ��ʼ����Ϸ״̬���������е���ɫ��/����/�ؿ���
	void Init();
	// ��Ϸѭ��
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render(); 
	void DoCollisions();
	void ResetLevel();
	void ResetPlayer();
};

#endif
