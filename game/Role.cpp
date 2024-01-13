#include "Role.h"

Role::Role()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Role::handleEvent(SDL_Event& e)
{
	//如果按下按键
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//判断是哪个按键
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= ROLE_VEL; break;
		case SDLK_DOWN: mVelY += ROLE_VEL; break;
		case SDLK_LEFT: mVelX -= ROLE_VEL; break;
		case SDLK_RIGHT: mVelX += ROLE_VEL; break;
		}
	}
	//如果释放按键
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//判断是那个按键
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += ROLE_VEL; break;
		case SDLK_DOWN: mVelY -= ROLE_VEL; break;
		case SDLK_LEFT: mVelX += ROLE_VEL; break;
		case SDLK_RIGHT: mVelX -= ROLE_VEL; break;
		}
	}
}

void Role::move()
{
	//向左向右
	mPosX += mVelX;

	//撞到边框
	if ((mPosX < 0) || (mPosX + ROLE_WIDTH > LEVEL_WIDTH))
	{
		//返回
		mPosX -= mVelX;
	}
	//向上向下走
	mPosY += mVelY+3;

	//撞到边框
	if ((mPosY < 0) || (mPosY + ROLE_HEIGHT > LEVEL_HEIGHT))
	{
		//返回
		mPosY -= mVelY+3;
	}
}

void Role::render(int camX, int camY,RTexture gTexture, SDL_Renderer* gRenderer)
{
	//渲染在相机之间
	gTexture.render(mPosX - camX, mPosY - camY, gRenderer);
}

int Role::getPosX()
{
	return mPosX;
}

int Role::getPosY()
{
	return mPosY;
}