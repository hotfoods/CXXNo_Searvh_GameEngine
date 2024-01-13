#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RTexture.h"
#include "GlobalVari.h"


/*
��ɫ
*/
class Role
{
public:
	//�ߴ�
	static const int ROLE_WIDTH = 20;
	static const int ROLE_HEIGHT = 20;

	//������ٶ�
	static const int ROLE_VEL = 10;

	//��ʼ������
	Role();

	//�����¼�����������ɫ�ٶ�
	void handleEvent(SDL_Event& e);

	//�ƶ�
	void move();

	//��ʾ��Ļ�����������Ľ�ɫ
	void render(int camX, int camY, RTexture gTexture, SDL_Renderer* gRenderer);

	//��ȡλ��
	int getPosX();
	int getPosY();

private:
	//ʵ��λ��
	int mPosX, mPosY;

	//����
	int mVelX, mVelY;
};

