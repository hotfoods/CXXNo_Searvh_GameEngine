#pragma once
#include<iostream>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RTexture.h"
#include "GlobalVari.h"
#include "Role.h"
//#include <unordered_map>
#include<vector>
using namespace std;

class GameBox
{
public:
    GameBox();
    ~GameBox();
    bool insertRole(Role role ,RTexture rtexture,string path);
    bool removeRole(Role role);
    RTexture getRoleTexture(Role role);
    bool isRoleInMap(Role role);
    bool mainLoop();

    bool init();
    bool loadMedia();
    void close();

private:
    Role protagonist;
    RTexture protRTexture;
    RTexture BGRTexture;
    std::vector<pair<Role, RTexture>> rolemap;
    std::vector<pair<RTexture, std::string>> texturePath;

    //sdl ´°¿Ú
    SDL_Window* gWindow = NULL;

    //sdl äÖÈ¾ÒýÇæ
    SDL_Renderer* gRenderer = NULL;
};

