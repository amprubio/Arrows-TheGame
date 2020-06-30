#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>
#include <time.h>

using namespace std;
using uint = unsigned int;

Game::Game()
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);

	window_ = SDL_CreateWindow("BOW and ARROW", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	for (int i = 0; i < N_TEXTURES; i++) {
		texture[i] = new Texture(renderer_, textures[i].route, textures[i].fil, textures[i].col);
	}

	bow = new Bow ({ 0,0 }, { 0, BOW_VELOCITY },100,150, texture[BT], texture[BT2], texture[AT], this);

	Balloon* b = new Balloon({ WIN_HEIGHT, WIN_HEIGHT }, 512, 512, {0,BALLOON_VELOCITY},true,texture[BL]);
	balloons.push_back(b);
}

Game::~Game()
{
}

void Game::Run()
{
	while (availableArrows<20) {
		HandleEvent();
		BalloonGenerate();
		update();
		render();

		SDL_Delay(1000 / FRAME_RATE);

	}
}

void Game::HandleEvent()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		bow->handleEvents(event);
	}
}

void Game::render()
{

	SDL_RenderClear(renderer_);
	texture[BG]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	bow->render();

	for (auto& arrow : arrows) {
		arrow->render();
	}
	for (auto& balloon : balloons) {
		balloon->Render();
	}

	SDL_RenderPresent(renderer_);
}



void Game::update()
{
	bow->update();
	for (auto& arrow : arrows) {
		arrow->update();
	}
}

bool Game::Collision(Balloon* b)
{
	for (int i = 0; i < arrows.size(); i++) {
		if (SDL_HasIntersection(b->GetRect(), arrows[i]->GetPoint())) {
			return true;
		}
	}
	return false;
}

void Game::shoot(Arrow* arrow)
{
	arrows.push_back(arrow);
	availableArrows--;
}

void Game::BalloonGenerate()
{
}
