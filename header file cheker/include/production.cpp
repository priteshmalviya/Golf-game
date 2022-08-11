#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<sstream>
#include<iostream>
#include<string>
#include<cmath>

using namespace std;

class LTexture {
	public:
		LTexture();
		~LTexture();
		bool loadFromFile(string path);
		bool loadFromRenderedText(string textureText, SDL_Color textColor);
		void free();
		void render(SDL_Rect renderQuad);
		int getWidth();
		int getHeight();
		void changeColore(Uint8 red, Uint8 green, Uint8 blue);

	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight; 
};


//veruables foe while loop
string fotime1 = "Time=";
string fotime2 = " : ";
string score="";
int value = 1;
bool quit = false;
int x = 10, y = 465,s=0;
int k = x;
bool jump = false, colision = true, activemon=false;
int px, py,mox=1400;


//Music
Mix_Music* gMusic = NULL;
Mix_Chunk* gScratch = NULL;
Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;


//time and fonts
LTexture gTextTexture;
LTexture gTimeTextTexture;
stringstream timeText;


//sdl thing
SDL_Rect renderQuad;


//texeturs
LTexture gFooTexture;
LTexture gTreeTexture;
LTexture gSunTexture;
LTexture gCoinTexture;
LTexture gMonsterTexture;



//my function
void my_renderTree(int k) {
	for (int i = -k; i < 1400; i += 200) {
		renderQuad = { i, 365,100,200 };
		gTreeTexture.render(renderQuad);
	}
}
void g_render(int k) {
	SDL_SetRenderDrawColor(gRenderer, 135, 206, 235, 0xFF);
	SDL_RenderClear(gRenderer);

	renderQuad = { -k,562,1400,100 };
	gBackgroundTexture.render(renderQuad);

	renderQuad = { 1390 - k,562,1400,100 };
	gBackgroundTexture.render(renderQuad);

	renderQuad = { 650,50,50,50 };
	gSunTexture.render(renderQuad);

	renderQuad = { 10,10,100,50 };
	gTextTexture.render(renderQuad);
	

	my_renderTree(k);

	renderQuad = { x, 465,75,100 };
	gFooTexture.render(renderQuad);

	renderQuad = { 1300, 10,100,30 };
	gTimeTextTexture.render(renderQuad);

	renderQuad = { px, py,50,50 };
	gCoinTexture.render(renderQuad);

	renderQuad = { mox, 400,200,200 };
	gMonsterTexture.render(renderQuad);
}
bool detect_colision(int x, int y) {
	if (px <= -35) {
		return true;
	}
	if ((x + 50 >= px && x <= px + 50) && (y + 50 >= py && y <= py + 50)) {
		s += 10; 
		Mix_PlayChannel(-1, gMedium, 0);
		score = to_string(s);
		gTextTexture.loadFromRenderedText("SCORE :" + score, textColor);
		return true;
	}
	return false;
}
bool detect_mcolision(int x, int y) {
	if (x>mox){
		s -= 100;
		Mix_PlayChannel(-1, gLow, 0);
		score = to_string(s);
		gTextTexture.loadFromRenderedText("SCORE :" + score, textColor);
		activemon = false;
		mox = 1400;
		return true;
	}
	return false;
}
void dekteh() {
	switch (e.type) {
	case SDL_QUIT:
		quit = true;
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.scancode) {
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
		case SDL_SCANCODE_SPACE:
			//Mix_PlayChannel(-1, gHigh, 0);
			jump = true;
			break;

		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			//cout << x << endl;
			switch (value) {
			case 1:
				gFooTexture.loadFromFile("../texture image/np1.png");
				value++;
				break;

			case 3:
				gFooTexture.loadFromFile("../texture image/np2.png");
				value++;
				break;

			case 5:
				gFooTexture.loadFromFile("../texture image/np3.png");
				value++;
				break;

			case 7:
				gFooTexture.loadFromFile("../texture image/np4.png");
				value++;
				break;

			case 9:
				gFooTexture.loadFromFile("../texture image/np5.png");
				value++;
				break;

			case 11:
				gFooTexture.loadFromFile("../texture image/np6.png");
				value++;
				break;

			case 13:
				gFooTexture.loadFromFile("../texture image/np7.png");
				value++;
				break;

			case 15:
				gFooTexture.loadFromFile("../texture image/np8.png");
				value = 1;
				break;

			default:
				value++;
				break;
			}
			x += 10;
			//Mix_PlayChannel(-1, gScratch, 0);
			//textColor={252,222,56};
			score = to_string(s);
			gTextTexture.loadFromRenderedText("SCORE :" + score, textColor);
			if (x >= 500) {
				k += 10;
			}
			if (x >= 500) {
				px -= 10;
			}
			if (x >= 500 && activemon) {
				mox -= 10;
			}
			break;

		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			//cout << x << endl;
			switch (value) {
			case 1:
				gFooTexture.loadFromFile("../texture image/np8.png");
				value++;
				break;

			case 3:
				gFooTexture.loadFromFile("../texture image/np7.png");
				value++;
				break;

			case 5:
				gFooTexture.loadFromFile("../texture image/np6.png");
				value++;
				break;

			case 7:
				gFooTexture.loadFromFile("../texture image/np5.png");
				value++;
				break;

			case 9:
				gFooTexture.loadFromFile("../texture image/np4.png");
				value++;
				break;

			case 11:
				gFooTexture.loadFromFile("../texture image/np3.png");
				value++;
				break;

			case 13:
				gFooTexture.loadFromFile("../texture image/np2.png");
				value++;
				break;

			case 15:
				gFooTexture.loadFromFile("../texture image/np1.png");
				value = 1;
				break;

			default:
				value++;
				break;
			}
			//Mix_PlayChannel(-1, gScratch, 0);
			x -= 10;
			break;
		}
		colision = detect_colision(x, y);
		detect_mcolision(x, y);
	}
}
int g_start() {
	gTreeTexture.changeColore(260, 130, 520);
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			dekteh();
		}
		timeText.str("");
		if ((SDL_GetTicks() / 60000) < 10) {
			fotime1 = "Time=0";
		}
		else {
			fotime1 = "Time=";
		}
		if (((SDL_GetTicks() / 1000) % 60) < 10) {
			fotime2 = " : 0";
		}
		else {
			fotime2 = " : ";
		}
		timeText << fotime1 << (SDL_GetTicks() / 60000) << fotime2 << (SDL_GetTicks() / 1000) % 60;
		if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
		{
			printf("Unable to render time texture!\n");
		}
		if ((SDL_GetTicks() / 1000) % 20 == 0) {
			activemon = true;
		}
		if (x < 0) {
			x = 0;
		}
		else if (x > 500) {
			x = 500;
		}
		if (k >= 1400) {
			k = 0;
		}

		if (colision) {
			px = rand() % 1300;
			px += 20;
			py = rand() % 90;
			py += 425;
			colision = false;
		}
		g_render(k);
		SDL_RenderPresent(gRenderer);
	}
	quit = false;
	return 3;
}

//other functions
LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}
LTexture::~LTexture() {
	free();
}
void LTexture::changeColore(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
bool LTexture::loadFromFile(string path) {
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
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}
bool LTexture::loadFromRenderedText(string textureText, SDL_Color textColor) {
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL) {
		cout << "unabe to render text :" << TTF_GetError() << endl;
	}
	else {
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL) {
			cout << "unable to create texture :" << SDL_GetError() << endl;
		}
		else {
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}
void LTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render(SDL_Rect renderQuad) {
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}
int LTexture::getWidth() {
	return mWidth;
}
int LTexture::getHeight() {
	return mHeight;
}
bool loadgMedia() {
	bool success = true;
	//load textures
	if (!gFooTexture.loadFromFile("../texture image/np.png")) {
		cout << "failde to load foo" << endl;
		success = false;
	}
	if (!gBackgroundTexture.loadFromFile("../texture image/road.png")) {
		cout << "faild to load bachground texture\n";
		success = false;
	}
	if (!gTreeTexture.loadFromFile("../texture image/tree.png")) {
		cout << "faild to load bachground texture\n";
		success = false;
	}
	if (!gSunTexture.loadFromFile("../texture image/sun.png")) {
		cout << "faild to load bachground texture\n";
		success = false;
	}
	if (!gCoinTexture.loadFromFile("../texture image/coin.png")) {
		cout << "faild to load bachground texture\n";
		success = false;
	}
	if (!gMonsterTexture.loadFromFile("../texture image/monster.png")) {
		cout << "faild to load bachground texture\n";
		success = false;
	}

	// load fonsts
	gFont = TTF_OpenFont("../ttf files/OpenSans-Bold.ttf", 28);
	if (gFont == NULL) {
		cout << "faild to load font :" << TTF_GetError() << endl;
		success = false;
	}
	else {
		if (!gTextTexture.loadFromRenderedText("SCORE :0", textColor)) //hhjdjhdgjfgggggggggggggggggggggggggggggggggg
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}


	//load music
	gMusic = Mix_LoadMUS("../sounds/0.mp3");
	if (gMusic == NULL) {//sggggggggggggggggsgssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssg
		cout << "failsed to load snd :" << Mix_GetError() << endl;
		success = false;
	}
	gScratch = Mix_LoadWAV("../sounds/1.wav");
	if (gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gHigh = Mix_LoadWAV("../sounds/2.wav");
	if (gHigh == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gMedium = Mix_LoadWAV("../sounds/coin.wav");
	if (gMedium == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gLow = Mix_LoadWAV("../sounds/loss.wav");
	if (gLow == NULL)
	{
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}
void close() {

	//texture
	gFooTexture.free();
	gBackgroundTexture.free();
	gSunTexture.free();
	gTreeTexture.free();
	gTextTexture.free();

	//text font and time
	TTF_CloseFont(gFont);
	gFont = NULL;


	//sounds
	Mix_FreeChunk(gScratch);
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	

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
