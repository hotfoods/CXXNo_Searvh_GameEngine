#include "RTexture.h"


RTexture::RTexture() {
	mTexture = NULL;
	mHeight = 0;
	mWidth = 0;
}

RTexture::~RTexture() {
	free();
}

bool RTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer) 
{
	//ȥ��Ԥ�ȴ��ڵ�����
	free();

	//������
	SDL_Texture* newTexture = NULL;

	//��ָ��·������ͼ��
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//��ɫͼ���Ķ�Ӧ��ֵ
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//�ӱ������ش�������
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//��ȡͼ��ߴ�
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//���Ѿɵļ��ر���
		SDL_FreeSurface(loadedSurface);
	}

	//���سɹ�
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif

void RTexture::free()
{
	//�ͷŴ��ڵ�����
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void RTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//�������� rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void RTexture::setBlendMode(SDL_BlendMode blending)
{
	//���������Ϸ�ʽ
	SDL_SetTextureBlendMode(mTexture, blending);
}

void RTexture::setAlpha(Uint8 alpha)
{
	//��������alpha����
	SDL_SetTextureAlphaMod(mTexture, alpha);
}


void RTexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//������Ⱦ��Ļ�ռ�
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//���ü�����Ⱦ�ߴ�
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//��Ⱦ����Ļ
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int RTexture::getWidth()
{
	return mWidth;
}

int RTexture::getHeight()
{
	return mHeight;
}