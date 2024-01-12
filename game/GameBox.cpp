#include "GameBox.h"

GameBox::GameBox()
{
}

GameBox::~GameBox()
{
	free;
}

//游戏盒子虚拟化
bool GameBox::init()
{
	//初始化初始化判断标志 flag
	bool success = true;

	//初始化 SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL 未能成功初始化  SDL错误:" << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//将纹理过滤设置为线性
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "警告：未启用线性纹理过滤" << endl;
		}

		//创建窗口
		gWindow = SDL_CreateWindow("mygame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "无法创建窗口！ SDL 错误: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//为窗口创建垂直同步渲染器
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				cout<<"渲染器未能被创建! SDL 错误: "<<SDL_GetError()<<endl;
				success = false;
			}
			else
			{
				//初始化渲染颜色
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//初始化图片加载
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout<<"SDL_image 未能被加载! SDL_image 错误: "<<IMG_GetError()<<endl;
					success = false;
				}
			}
		}
	}
	return success;
}



bool GameBox::loadMedia()
{
	//加载成功标志
	bool success = true;
	if (!protRTexture.loadFromFile("d:/sdl2/study/30/dot.bmp",gRenderer)){
		cout << " 加载主角纹理文件失败！" << endl;
		success = false;
	}

	if (!BGRTexture.loadFromFile("d:/sdl2/study/30/bg.png",gRenderer)) {
		cout << " 加载背景纹理文件失败！" << endl;
		success = false;
	}

	//加载map列表的纹理图片
	for (auto it = texturePath.begin(); it != texturePath.end(); it++) {
		if (!it->first.loadFromFile(it->second, gRenderer)) {
			cout << " 加载纹理文件失败！" << endl;
			success = false;
		}
	}

	return success;
}

void GameBox::close()
{

	//释放纹理对象
	for (auto it = texturePath.begin(); it != texturePath.end(); it++) {
		it->first.free();
	}

	//注销窗口	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//退出SDL系统
	IMG_Quit();
	SDL_Quit();
}

bool GameBox::mainLoop()
{
	//加载sdl并创建窗口
	if (!init())
	{
		cout<<"初始化失败 ！"<<endl;
	}
	else
	{
		//加载media
		if (!loadMedia())
		{
			cout<<"加载资源文件失败!"<<endl;
		}
		else
		{
			//主循环 flag
			bool quit = false;

			//事件句柄
			SDL_Event e;

			//The dot that will be moving around on the screen
			//Dot dot;

			//相机
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			//主循环
			while (!quit)
			{
				//处理时间队列
				while (SDL_PollEvent(&e) != 0)
				{
					//输入退出
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//处理移动事件
					protagonist.handleEvent(e);
				}

				//移动
				protagonist.move();

				//将主角放在中央
				camera.x = (protagonist.getPosX() + Role::ROLE_WIDTH / 2) - SCREEN_WIDTH / 2;
				camera.y = (protagonist.getPosY() + Role::ROLE_HEIGHT / 2) - SCREEN_HEIGHT / 2;

				//保持相机边缘
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

				//清除上一帧画面
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background
				BGRTexture.render(0, 0, gRenderer,&camera);

				//Render 主角
				//protagonist.render(camera.x, camera.y,protRTexture,gRenderer);
				protRTexture.render(protagonist.getPosX() - camera.x,protagonist.getPosY()-camera.y,gRenderer);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//释放资源关闭sdl
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
