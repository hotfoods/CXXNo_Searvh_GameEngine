#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RTexture.h"
#include "GlobalVari.h"


/*
角色
*/
class Role
{
public:
	//尺寸
	static const int ROLE_WIDTH = 20;
	static const int ROLE_HEIGHT = 20;

	//最大轴速度
	static const int ROLE_VEL = 10;

	//初始化变量
	Role();

	//按键事件处理并调整角色速度
	void handleEvent(SDL_Event& e);

	//移动
	void move();

	//显示屏幕上相对于相机的角色
	void render(int camX, int camY, RTexture gTexture, SDL_Renderer* gRenderer);

	//获取位置
	int getPosX();
	int getPosY();

private:
	//实际位置
	int mPosX, mPosY;

	//动量
	int mVelX, mVelY;
};

