#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


/*
纹理渲染模块

*/
class RTexture
{
public:
    RTexture();
    ~RTexture();
    

    bool loadFromFile(std::string path, SDL_Renderer* gRenderer) ;

#if defined(SDL_TTF_MAJOR_VERSION)
    //从字体字符串创建图像
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//解除分配纹理
	void free();

	//设置颜色调制
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//设置混合
	void setBlendMode(SDL_BlendMode blending);

	//设置 alpha 调制
	void setAlpha(Uint8 alpha);

	//在给objects渲染纹理
	void render(int x, int y, SDL_Renderer* gRenderer,SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//获取图像尺寸
	int getWidth();
	int getHeight();
private:
	//实际的硬件纹理
	SDL_Texture* mTexture;

	//图像尺寸
	int mWidth;
	int mHeight;
};

