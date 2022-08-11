#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<sstream>

using namespace std;

int winH = 1400;
int winW = 650;

class menu{
	public:
		menu();
		~menu();
		bool loadFromFile(string path);
		bool loadFromRenderedText(string textureText, SDL_Color textColor);
		void free();
		void render(SDL_Rect renderQuad);
		int getWidth();
		int getHeight();

private:
	SDL_Texture* pTexture;
	int pWidth;
	int pHeight;
};


//For Music
Mix_Music* bMusic = NULL;//gb music
Mix_Chunk* sMusic = NULL;//click music


//For font
TTF_Font* gFont = NULL;
menu gTexth1;
menu gTexth2;
menu gTexth3;
SDL_Color textColor = { 255,0,0 };
SDL_Color textColorA = { 0,255,0 };

//For SDL 
SDL_Event e;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect sAndl;//For Size and Location


//For bg
menu gBackgroundTexture;


//My functions
void create_window() {
	gWindow = SDL_CreateWindow("Golf Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winH, winW, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		cout << "tere is an error :" << SDL_GetError() << endl;
	}
	else {
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL) {
			cout << "tere is an error in renderer :" << SDL_GetError() << endl;
		}
		else {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
}
void my_Init() {
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}


	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "SDL could not inislize :" << SDL_GetError() << endl;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << "SDL_Mixer notinisize :" << Mix_GetError() << endl;
	}
}
void my_render() {
	//SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(gRenderer);

	sAndl = { 0,0,winH,winW};
	gBackgroundTexture.render(sAndl);

	sAndl = { 100,75,200,150 };
	gTexth1.render(sAndl);

	sAndl = { 120,250,150,100 };
	gTexth2.render(sAndl);

	sAndl = { 120,350,150,100 };
	gTexth3.render(sAndl);
}
int start() {
	int activ = 2;
	while (1) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				return 0;

			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					if (activ != 2) {
						gTexth2.loadFromRenderedText("Play", textColorA);
						gTexth3.loadFromRenderedText("Quit", textColor);
						activ = 2;
						Mix_PlayChannel(-1, sMusic, 0);
					}
					break;

				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					if (activ != 1) {
						gTexth2.loadFromRenderedText("Play", textColor);
						gTexth3.loadFromRenderedText("Quit", textColorA);
						activ = 1;
						Mix_PlayChannel(-1, sMusic, 0);
					}
					break;

				case SDL_SCANCODE_RETURN:
					return activ;
					Mix_PlayChannel(-1, sMusic, 0);
					break;
				}
			}
		}
		my_render();
		SDL_RenderPresent(gRenderer);
	}
}


//Other Functions
menu::menu() {
	pTexture = NULL;
	pWidth = 0;
	pHeight = 0;
}
menu::~menu() {
	free();
}
bool menu::loadFromFile(string path) {
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "Unable to load img :" << IMG_GetError() << endl;
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			cout << "Unable to create texture :" << SDL_GetError() << endl;
		}
		else {
			pWidth = loadedSurface->w;
			pHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	pTexture = newTexture;
	return pTexture != NULL;
}
bool menu::loadFromRenderedText(string textureText, SDL_Color textColor) {
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL) {
		cout << "unabe to render text :" << TTF_GetError() << endl;
	}
	else {
		pTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (pTexture == NULL) {
			cout << "unable to create texture :" << SDL_GetError() << endl;
		}
		else {
			pWidth = textSurface->w;
			pHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return pTexture != NULL;
}
void menu::free() {
	if (pTexture != NULL) {
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
		pWidth = 0;
		pHeight = 0;
	}
}
void menu::render(SDL_Rect renderQuad) {
	SDL_RenderCopy(gRenderer, pTexture, NULL, &renderQuad);
}
int menu::getWidth() {
	return pWidth;
}
int menu::getHeight() {
	return pHeight;
}
bool loadMedia() {
	bool success = true;
	//load textures
	if (!gBackgroundTexture.loadFromFile("../texture image/mBg.png")) {
		cout << "faild to load bachground texture\n";
		success = false;
	}


	// load fonsts
	gFont = TTF_OpenFont("../ttf files/Roboto-Medium.ttf", 28);
	if (gFont == NULL) {
		cout << "faild to load font :" << TTF_GetError() << endl;
		success = false;
	}
	else {
		textColor = { 255,0,0 };
		gTexth1.loadFromRenderedText("Golf", textColor);
		gTexth2.loadFromRenderedText("Play", textColorA);
		gTexth3.loadFromRenderedText("Quit", textColor);
	}


	//load music
	bMusic = Mix_LoadMUS("../sounds/bMusic.mp3");
	if (bMusic == NULL) {
		cout << "failsed to load snd :" << Mix_GetError() << endl;
		success = false;
	}
	sMusic = Mix_LoadWAV("../sounds/sMusic.wav");
	if (sMusic == NULL) {
		cout << "failsed to load snd :" << Mix_GetError() << endl;
		success = false;
	}
	Mix_PlayMusic(bMusic, -1);
	Mix_VolumeMusic(1);
	return success;
}
void close() {

	//texture
	gTexth1.free();
	gTexth2.free();
	gTexth3.free();
	gBackgroundTexture.free();

	//text font and time
	TTF_CloseFont(gFont);
	gFont = NULL;


	//sounds
	Mix_FreeChunk(sMusic);
	sMusic = NULL;
	Mix_FreeMusic(bMusic);
	bMusic = NULL;


	//renderer ans window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
