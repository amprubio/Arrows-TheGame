#include "Texture.h"
#include <iostream>

using namespace std;

Texture::~Texture() {
	try {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		w = h = 0;
	}
	catch (exception e) {
		cout << "Error deleting texture " << e.what() << endl;
	}
}

void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw std::invalid_argument("Error loading surface from " + filename);// ("Error loading surface from " + filename);
	//texture = nullptr;
	//this->~Texture();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw "Error loading texture from " + filename;
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}