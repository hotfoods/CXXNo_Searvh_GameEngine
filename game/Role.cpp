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
	//������°���
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//�ж����ĸ�����
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= ROLE_VEL; break;
		case SDLK_DOWN: mVelY += ROLE_VEL; break;
		case SDLK_LEFT: mVelX -= ROLE_VEL; break;
		case SDLK_RIGHT: mVelX += ROLE_VEL; break;
		}
	}
	//����ͷŰ���
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//�ж����Ǹ�����
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
	//��������
	mPosX += mVelX;

	//ײ���߿�
	if ((mPosX < 0) || (mPosX + ROLE_WIDTH > LEVEL_WIDTH))
	{
		//����
		mPosX -= mVelX;
	}
	//����������
	mPosY += mVelY+3;

	//ײ���߿�
	if ((mPosY < 0) || (mPosY + ROLE_HEIGHT > LEVEL_HEIGHT))
	{
		//����
		mPosY -= mVelY+3;
	}
}

void Role::render(int camX, int camY,RTexture gTexture, SDL_Renderer* gRenderer)
{
	//��Ⱦ�����֮��
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