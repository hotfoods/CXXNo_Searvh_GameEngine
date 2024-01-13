#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


/*
������Ⱦģ��

*/
class RTexture
{
public:
    RTexture();
    ~RTexture();
    

    bool loadFromFile(std::string path, SDL_Renderer* gRenderer) ;

#if defined(SDL_TTF_MAJOR_VERSION)
    //�������ַ�������ͼ��
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//�����������
	void free();

	//������ɫ����
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//���û��
	void setBlendMode(SDL_BlendMode blending);

	//���� alpha ����
	void setAlpha(Uint8 alpha);

	//�ڸ�objects��Ⱦ����
	void render(int x, int y, SDL_Renderer* gRenderer,SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//��ȡͼ��ߴ�
	int getWidth();
	int getHeight();
private:
	//ʵ�ʵ�Ӳ������
	SDL_Texture* mTexture;

	//ͼ��ߴ�
	int mWidth;
	int mHeight;
};

