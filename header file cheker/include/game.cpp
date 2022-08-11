#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<sstream>
#include<string>

using namespace std;


class game {
public:
	game();
	~game();
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
Mix_Chunk* shotMusic = NULL;
Mix_Chunk* goleMusic = NULL;
Mix_Chunk* coinMusic = NULL;


//time 
string fotime1 = "Time=";
string fotime2 = " : ";
game gTimeTextTexture; 
stringstream timeText;
Uint32 startTime = 0;

//x and y for hole 
int hx = 1000, hy = 100;


//For Sdl
SDL_Rect bsAndl = { 100,100,20,20 };
SDL_Rect hAndl = { hx,hy,25,25 };


//For props textures
game holeTexture;


//for menu and stuff
game gTexth4;
game gTexth5;
game gTexth6;



//My functions
void gclose();
void time() {
	timeText.str("");

	if (((SDL_GetTicks() - startTime) / 60000) < 10) {
		fotime1 = "Time=0";
	}
	else {
		fotime1 = "Time=";
	}
	if ((((SDL_GetTicks() - startTime) / 1000) % 60) < 10) {
		fotime2 = " : 0";
	}
	else {
		fotime2 = " : ";
	}
	timeText << fotime1 << ((SDL_GetTicks()- startTime) / 60000) << fotime2 << ((SDL_GetTicks() - startTime) / 1000) % 60;
	if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
	{
		printf("Unable to render time texture!\n");
	}
}
void g_render() {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0xFF);
	SDL_RenderClear(gRenderer);

	sAndl = { 0,50,1400,600 };
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &sAndl);


	holeTexture.render(hAndl);

	sAndl = { 1275,0,100,50 };
	gTimeTextTexture.render(sAndl);

	gBackgroundTexture.render(bsAndl);


	sAndl = { 10,0,100,50 };
	gTexth1.render(sAndl);

	sAndl = { 650,0,100,50 };
	gTexth2.render(sAndl);

}
void line(int x,int y,int lx,int ly) {
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, x + 10, y + 10, lx, ly);
}
bool colision(int x, int y, int d,int &score,int &lives) {
	if ((x + 15 >= hx && x <= hx + 22) && (y + 15 >= hy && y <= hy + 22) && d != -1) {
		Mix_PlayChannel(-1, goleMusic, 0);
		int h = 20;
		int k = 2;
		while (h) {
			bsAndl = { hx + k,hy + k,h,h };
			time();
			g_render();
			SDL_RenderPresent(gRenderer);
			h -= 2;
			k += 1;
			SDL_Delay(100);
		}
		SDL_Delay(300);
		score+=10;
		lives = 5;
		string ScoreStr = "Score : ";
		ScoreStr += to_string(score);
		gTexth1.loadFromRenderedText(ScoreStr, textColor);
		ScoreStr = "lives : ";
		ScoreStr += to_string(lives);
		gTexth2.loadFromRenderedText(ScoreStr, textColor);
		Mix_PlayChannel(-1, coinMusic, 0);
		hx = rand()%1400;
		hy = (rand()%550)+60;
		hAndl = { hx,hy,25,25 };
		return true;
	}
	return false;
	//cout << hx << " " << hy << " " << x << " " << y << endl;
}
int chaingepos(int &x,int &y,int d,int &score,int &lives) {
	int k=2000;
	while (k) {
		switch (d)
		{
		case 1:
			y--;
			break;
		case 2:
			y++;
			break;
		case 3:
			x++;
			break;
		case 4:
			x--;
			break;
		case 5:
			x--; y--;
			break;
		case 6:
			x--; y++;
			break;
		case 7:
			x++; y++;
			break;
		case 8:
			x++; y--;
			break;

		}
		if (x >= 1400 || x<=0 || y >= 650 || y <= 50) {
			Mix_PlayChannel(-1, sMusic, 0);
			if (d <= 4) {
				if (d % 2 == 0) {
					d--;
				}
				else {
					d++;
				}
			}
			else {
				if (d < 8) {
					d++;
				}
				else {
					d = 5;
				}
			}
		}
		bsAndl = { x ,y,20,20 };
		time();
		g_render();
		SDL_RenderPresent(gRenderer);
		if (colision(x, y, d, score,lives)) {
			x = 100, y = 100;
			bsAndl = { x,y,20,20 };
			break;
		}
		k--;
	}
	return -1;
}
void changeImage(int direction,int x,int y) {
	if (direction == -1) {
		return;
	}
	/*string str = "../texture image/ball";
	str += to_string(direction);
	str += ".png";
	gBackgroundTexture.loadFromFile(str);*/
}
void life(int lives) {
	string livStr = "Life : ";
	livStr += to_string(lives);
	gTexth2.loadFromRenderedText(livStr, textColor);
	if (lives == 0) {
		g_render();
		SDL_RenderPresent(gRenderer);
		gTexth4.loadFromRenderedText("Game Over", textColor);
		SDL_Delay(500);
		sAndl = { 200,200,1000,250 };
		gTexth4.render(sAndl);
		SDL_RenderPresent(gRenderer);
		SDL_Delay(2000);
	}
}
void moveBall(int &x, int &y, int &score) {
	bool flage = true;
	while (flage) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					Mix_PlayChannel(-1, sMusic, 0);
					y -= 5;
					break;

				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					Mix_PlayChannel(-1, sMusic, 0);
					y += 5;
					break;

				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					Mix_PlayChannel(-1, sMusic, 0);
					x += 5;
					break;


				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					Mix_PlayChannel(-1, sMusic, 0);
					x -= 5;
					break;


				case SDL_SCANCODE_SPACE:
					score -= 30;		
					string ScoreStr = "Score : ";
					ScoreStr += to_string(score);
					gTexth1.loadFromRenderedText(ScoreStr, textColor);
					flage = false;
					break;
				}
			}
		}
		bsAndl = { x,y,20,20 };
		time();
		g_render();
		SDL_RenderPresent(gRenderer);
	}
}
void opneMenu(int &life) {
	bool q = true;
	while (q) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode) {

				case SDL_SCANCODE_Q:
					life = 0;
					return;

				case SDL_SCANCODE_ESCAPE:
					q = false;
					break;
				}
			}
		}
		sAndl = { 0,0,1400,650 };
		SDL_SetRenderDrawColor(gRenderer, 50, 50, 50,255);
		SDL_RenderFillRect(gRenderer, &sAndl);
		gTexth3.loadFromRenderedText("INSTRUCTION : USE ARROW KEYS TO CHANGE THE DIRECTION OF THE BALL AND ENTER TO SHOOT THE BALL.", textColorA);
		sAndl = { 100,100,1200,50 };
		gTexth3.render(sAndl);
		gTexth4.loadFromRenderedText("INSTRUCTION : You Can Use A Power Of Moving The Ball by Pressing Space Bar For -30 Points", textColorA);
		sAndl = { 100,200,1200,50 };
		gTexth4.render(sAndl);
		gTexth5.loadFromRenderedText("INSTRUCTION : Press Escap TO Countinue", textColorA);
		sAndl = { 350,300,700,50 };
		gTexth5.render(sAndl);
		gTexth6.loadFromRenderedText("INSTRUCTION : Press 'Q' To Quit The Game.", textColorA);
		sAndl = { 350,400,700,50 };
		gTexth6.render(sAndl);
		SDL_RenderPresent(gRenderer);
	}
}
int g_start() {
	startTime = SDL_GetTicks();
	int activ = 1;
	int d =  -1;
	int x = 100, y = 100;
	int lx=x+10, ly=y+10;
	bool flage = false, menu = false;
	int score = 0,lives=5;
	while (1) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				return 0;

			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					Mix_PlayChannel(-1, sMusic, 0);
					if (d == 1) {
						d = 8;
						lx = x + 20;
						ly = y;
					}
					else {
						d = 1;
						ly = y;
						lx = x + 10;
					}
					break;

				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					Mix_PlayChannel(-1, sMusic, 0);
					if (d == 2) {
						d = 6;
						lx = x;
						ly = y + 20;
					}
					else {
						d = 2;
						ly = y + 20;
						lx = x + 10;
					}
					break;

				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					Mix_PlayChannel(-1, sMusic, 0);
					if (d == 3) {
						d = 7;
						lx = x + 20;
						ly = y + 20;
					}
					else {
						d = 3;
						lx = x + 20;
						ly = y + 10;
					}
					break;


				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					Mix_PlayChannel(-1, sMusic, 0);
					if (d == 4) {
						d = 5;
						lx = x;
						ly = y;
					}
					else {
						d = 4;
						lx = x;
						ly = y + 10;
					}
					break;


				case SDL_SCANCODE_SPACE:
					if (score >= 30) {
						flage = true;
					}
					break;


				case SDL_SCANCODE_ESCAPE:
					menu = true;
					break;


				case SDL_SCANCODE_RETURN:
					if (d != -1) {
						Mix_PlayChannel(-1, shotMusic, 0);
						lives--;
						d = chaingepos(x, y, d, score, lives);
						ly = y + 10, lx = x + 10;
					}
					break;
				}
			}
		}
		
		life(lives);
		time();
		g_render();
		if (menu) {
			opneMenu(lives);
			menu = false;
		}
		if (flage) {
			moveBall(x, y, score);
			lx = x + 10; ly = y + 10;
			flage = false;
		}
		line(x, y, lx, ly);
		SDL_RenderPresent(gRenderer);
		if (lives == 0) {
			x = 100, y = 100;
			bsAndl = { 100,100,20,20 };
			gclose();
			return 3;
		}
	}
}


//Other Functions
game::game() {
	pTexture = NULL;
	pWidth = 0;
	pHeight = 0;
}
game::~game() {
	free();
}
bool game::loadFromFile(string path) {
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
bool game::loadFromRenderedText(string textureText, SDL_Color textColor) {
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
void game::free() {
	if (pTexture != NULL) {
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
		pWidth = 0;
		pHeight = 0;
	}
}
void game::render(SDL_Rect renderQuad) {
	SDL_RenderCopy(gRenderer, pTexture, NULL, &renderQuad);
}
int game::getWidth() {
	return pWidth;
}
int game::getHeight() {
	return pHeight;
}
bool loadgMedia(){
	bool success = true;
	//load textures
	if (!gBackgroundTexture.loadFromFile("../texture image/ball.png")) {
		cout << "faild to load jgjgh texture\n";
		success = false;
	}
	if (!holeTexture.loadFromFile("../texture image/hole.png")) {
		cout << "faild to load jgjgh texture\n";
		success = false;
	}


	// load fonsts
		textColor = { 129, 217, 85 };
		gTexth1.loadFromRenderedText("Score : 0", textColor);
		gTexth2.loadFromRenderedText("Lives : 5", textColor);


	//load music
	shotMusic = Mix_LoadWAV("../sounds/shotMusic.wav");
	if (shotMusic == NULL) {
		cout << "failsed to load sh snd :" << Mix_GetError() << endl;
		success = false;
	}

	coinMusic= Mix_LoadWAV("../sounds/coin.wav");
	if (coinMusic == NULL) {
		cout << "failsed to load c snd :" << Mix_GetError() << endl;
		success = false;
	}

	goleMusic = Mix_LoadWAV("../sounds/gole.mp3");
	if (goleMusic == NULL) {
		cout << "failsed to load g snd :" << Mix_GetError() << endl;
		success = false;
	}
	//Mix_Volume(-1, MIX_MAX_VOLUME);
	return success;
}
void gclose() {
	//texture
	holeTexture.free(); 
	gTimeTextTexture.free();

	//text font and time
	TTF_CloseFont(gFont);
	gFont = NULL;
	gTexth4.free();
	gTexth5.free();
	gTexth6.free();


	//sounds
	Mix_FreeChunk(shotMusic);
	Mix_FreeChunk(goleMusic);
	Mix_FreeChunk(coinMusic);
	coinMusic = NULL;
	goleMusic = NULL;
	shotMusic = NULL;
}