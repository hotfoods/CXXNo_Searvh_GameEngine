#include "GameBox.h"

GameBox::GameBox()
{
}

GameBox::~GameBox()
{
	free;
}

//��Ϸ�������⻯
bool GameBox::init()
{
	//��ʼ����ʼ���жϱ�־ flag
	bool success = true;

	//��ʼ�� SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL δ�ܳɹ���ʼ��  SDL����:" << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//�������������Ϊ����
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "���棺δ���������������" << endl;
		}

		//��������
		gWindow = SDL_CreateWindow("mygame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "�޷��������ڣ� SDL ����: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Ϊ���ڴ�����ֱͬ����Ⱦ��
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				cout<<"��Ⱦ��δ�ܱ�����! SDL ����: "<<SDL_GetError()<<endl;
				success = false;
			}
			else
			{
				//��ʼ����Ⱦ��ɫ
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//��ʼ��ͼƬ����
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout<<"SDL_image δ�ܱ�����! SDL_image ����: "<<IMG_GetError()<<endl;
					success = false;
				}
			}
		}
	}
	return success;
}



bool GameBox::loadMedia()
{
	//���سɹ���־
	bool success = true;
	if (!protRTexture.loadFromFile("d:/sdl2/study/30/dot.bmp",gRenderer)){
		cout << " �������������ļ�ʧ�ܣ�" << endl;
		success = false;
	}

	if (!BGRTexture.loadFromFile("d:/sdl2/study/30/bg.png",gRenderer)) {
		cout << " ���ر��������ļ�ʧ�ܣ�" << endl;
		success = false;
	}

	//����map�б������ͼƬ
	for (auto it = texturePath.begin(); it != texturePath.end(); it++) {
		if (!it->first.loadFromFile(it->second, gRenderer)) {
			cout << " ���������ļ�ʧ�ܣ�" << endl;
			success = false;
		}
	}

	return success;
}

void GameBox::close()
{

	//�ͷ��������
	for (auto it = texturePath.begin(); it != texturePath.end(); it++) {
		it->first.free();
	}

	//ע������	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//�˳�SDLϵͳ
	IMG_Quit();
	SDL_Quit();
}

bool GameBox::mainLoop()
{
	//����sdl����������
	if (!init())
	{
		cout<<"��ʼ��ʧ�� ��"<<endl;
	}
	else
	{
		//����media
		if (!loadMedia())
		{
			cout<<"������Դ�ļ�ʧ��!"<<endl;
		}
		else
		{
			//��ѭ�� flag
			bool quit = false;

			//�¼����
			SDL_Event e;

			//The dot that will be moving around on the screen
			//Dot dot;

			//���
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			//��ѭ��
			while (!quit)
			{
				//����ʱ�����
				while (SDL_PollEvent(&e) != 0)
				{
					//�����˳�
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//�����ƶ��¼�
					protagonist.handleEvent(e);
				}

				//�ƶ�
				protagonist.move();

				//�����Ƿ�������
				camera.x = (protagonist.getPosX() + Role::ROLE_WIDTH / 2) - SCREEN_WIDTH / 2;
				camera.y = (protagonist.getPosY() + Role::ROLE_HEIGHT / 2) - SCREEN_HEIGHT / 2;

				//���������Ե
				if (camera.x < 0)
				{
					camera.x = 0;
				}
				if (camera.y < 0)
				{
					camera.y = 0;
				}
				if (camera.x > LEVEL_WIDTH - camera.w)
				{
					camera.x = LEVEL_WIDTH - camera.w;
				}
				if (camera.y > LEVEL_HEIGHT - camera.h)
				{
					camera.y = LEVEL_HEIGHT - camera.h;
				}

				//�����һ֡����
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background
				BGRTexture.render(0, 0, gRenderer,&camera);

				//Render ����
				//protagonist.render(camera.x, camera.y,protRTexture,gRenderer);
				protRTexture.render(protagonist.getPosX() - camera.x,protagonist.getPosY()-camera.y,gRenderer);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//�ͷ���Դ�ر�sdl
	close();
	return false;
}



bool GameBox::insertRole(Role role, RTexture rtexture,string path)
{
	return false;
}

bool GameBox::removeRole(Role role)
{
	return false;
}

RTexture GameBox::getRoleTexture(Role role)
{
	return RTexture();
}

bool GameBox::isRoleInMap(Role role)
{
	return false;
}
