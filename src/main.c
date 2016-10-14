#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>

#include "gfx\gfx_group_1.h"

/* Function prototypes */
void ResetVars(void);
void MainMenu(void);
void Instruction(void);
void Game(void);

int i, j;
int oldTime, time, oneSecond, alternator = 0;
int RL = 0;
int StarX[15];
int StarY[15];
int StarState[15];
int CatX = 138;
int CatY = 170;
float FuelBar = 200, HealthBar = 200;
int ObjectX[2], ObjectY[2], ObjectW[2], ObjectH[2], rndObject;
int Objects[2];
int Coins = 0;
char ScoreBuf[10];
int GameOver = 1;
int Menu = 1;
int Instructions = 0;

gfx_image_t *Asteroid;
gfx_image_t *Coin;
gfx_image_t *Flame1;
gfx_image_t *Flame2;
gfx_image_t *Fuel;
gfx_image_t *Mouse1;
gfx_image_t *Mouse2;
gfx_image_t *SpaceCat;
gfx_image_t *SpaceCatFlipped;
gfx_image_t *SpaceCatHead;
gfx_image_t *SpaceCatHead1;
gfx_image_t *Star1;
gfx_image_t *Star2;
gfx_image_t *font0;
gfx_image_t *font1;
gfx_image_t *font2;
gfx_image_t *font3;
gfx_image_t *font4;
gfx_image_t *font5;
gfx_image_t *font6;
gfx_image_t *font7;
gfx_image_t *font8;
gfx_image_t *font9;
gfx_image_t *A;
gfx_image_t *B;
gfx_image_t *C;
gfx_image_t *D;
gfx_image_t *E;
gfx_image_t *F;
gfx_image_t *G;
gfx_image_t *H;
gfx_image_t *I;
gfx_image_t *J;
gfx_image_t *K;
gfx_image_t *L;
gfx_image_t *M;
gfx_image_t *N;
gfx_image_t *O;
gfx_image_t *P;
gfx_image_t *Q;
gfx_image_t *R;
gfx_image_t *S;
gfx_image_t *T;
gfx_image_t *U;
gfx_image_t *V;
gfx_image_t *W;
gfx_image_t *X;
gfx_image_t *Y;
gfx_image_t *Z;
gfx_image_t *Period;
gfx_image_t *Colon;

int main(void) {
	gfx_Begin(gfx_8bpp);
	gfx_SetPalette(gfx_group_1_pal, sizeof(gfx_group_1_pal), 0);
	malloc(0);

	Asteroid = gfx_AllocSprite( 64, 64, malloc );
	Coin = gfx_AllocSprite( 16, 34, malloc );
	Flame1 = gfx_AllocSprite( 5, 5, malloc );
	Flame2 = gfx_AllocSprite( 5, 5, malloc );
	Fuel = gfx_AllocSprite( 28, 20, malloc );
	Mouse1 = gfx_AllocSprite( 54, 42, malloc );
	Mouse2 = gfx_AllocSprite( 54, 42, malloc );
	SpaceCat = gfx_AllocSprite( 22, 35, malloc );
	SpaceCatFlipped = gfx_AllocSprite( 22, 35, malloc );
	SpaceCatHead = gfx_AllocSprite( 17, 17, malloc );
	SpaceCatHead1 = gfx_AllocSprite( 17, 17, malloc );
	Star1 = gfx_AllocSprite( 6, 6, malloc );
	Star2 = gfx_AllocSprite( 6, 6, malloc );
	font0 = gfx_AllocSprite( 8, 9, malloc );
	font1 = gfx_AllocSprite( 8, 9, malloc );
	font2 = gfx_AllocSprite( 8, 9, malloc );
	font3 = gfx_AllocSprite( 8, 9, malloc );
	font4 = gfx_AllocSprite( 8, 9, malloc );
	font5 = gfx_AllocSprite( 8, 9, malloc );
	font6 = gfx_AllocSprite( 8, 9, malloc );
	font7 = gfx_AllocSprite( 8, 9, malloc );
	font8 = gfx_AllocSprite( 8, 9, malloc );
	font9 = gfx_AllocSprite( 8, 9, malloc );
	A = gfx_AllocSprite( 8, 9, malloc );
	B = gfx_AllocSprite( 8, 9, malloc );
	C = gfx_AllocSprite( 8, 9, malloc );
	D = gfx_AllocSprite( 8, 9, malloc );
	E = gfx_AllocSprite( 8, 9, malloc );
	F = gfx_AllocSprite( 8, 9, malloc );
	G = gfx_AllocSprite( 8, 9, malloc );
	H = gfx_AllocSprite( 8, 9, malloc );
	I = gfx_AllocSprite( 8, 9, malloc );
	J = gfx_AllocSprite( 8, 9, malloc );
	K = gfx_AllocSprite( 8, 9, malloc );
	L = gfx_AllocSprite( 8, 9, malloc );
	M = gfx_AllocSprite( 8, 9, malloc );
	N = gfx_AllocSprite( 8, 9, malloc );
	O = gfx_AllocSprite( 8, 9, malloc );
	P = gfx_AllocSprite( 8, 9, malloc );
	Q = gfx_AllocSprite( 8, 9, malloc );
	R = gfx_AllocSprite( 8, 9, malloc );
	S = gfx_AllocSprite( 8, 9, malloc );
	T = gfx_AllocSprite( 8, 9, malloc );
	U = gfx_AllocSprite( 8, 9, malloc );
	V = gfx_AllocSprite( 8, 9, malloc );
	W = gfx_AllocSprite( 8, 9, malloc );
	X = gfx_AllocSprite( 8, 9, malloc );
	Y = gfx_AllocSprite( 8, 9, malloc );
	Z = gfx_AllocSprite( 8, 9, malloc );
	Period = gfx_AllocSprite( 8, 9, malloc );
	Colon = gfx_AllocSprite( 8, 9, malloc );

	gfx_LZDecompressSprite( Asteroid_data_compressed, Asteroid );
	gfx_LZDecompressSprite( Coin_data_compressed, Coin );
	gfx_LZDecompressSprite( Flame1_data_compressed, Flame1 );
	gfx_LZDecompressSprite( Flame2_data_compressed, Flame2 );
	gfx_LZDecompressSprite( Fuel_data_compressed, Fuel );
	gfx_LZDecompressSprite( Mouse1_data_compressed, Mouse1 );
	gfx_LZDecompressSprite( Mouse2_data_compressed, Mouse2 );
	gfx_LZDecompressSprite( SpaceCat_data_compressed, SpaceCat );
	gfx_LZDecompressSprite( SpaceCatFlipped_data_compressed, SpaceCatFlipped );
	gfx_LZDecompressSprite( SpaceCatHead_data_compressed, SpaceCatHead );
	gfx_LZDecompressSprite( SpaceCatHead1_data_compressed, SpaceCatHead1 );
	gfx_LZDecompressSprite( Star1_data_compressed, Star1 );
	gfx_LZDecompressSprite( Star2_data_compressed, Star2 );
	gfx_LZDecompressSprite( font0_data_compressed, font0 );
	gfx_LZDecompressSprite( font1_data_compressed, font1 );
	gfx_LZDecompressSprite( font2_data_compressed, font2 );
	gfx_LZDecompressSprite( font3_data_compressed, font3 );
	gfx_LZDecompressSprite( font4_data_compressed, font4 );
	gfx_LZDecompressSprite( font5_data_compressed, font5 );
	gfx_LZDecompressSprite( font6_data_compressed, font6 );
	gfx_LZDecompressSprite( font7_data_compressed, font7 );
	gfx_LZDecompressSprite( font8_data_compressed, font8 );
	gfx_LZDecompressSprite( font9_data_compressed, font9 );
	gfx_LZDecompressSprite( A_data_compressed, A );
	gfx_LZDecompressSprite( B_data_compressed, B );
	gfx_LZDecompressSprite( C_data_compressed, C );
	gfx_LZDecompressSprite( D_data_compressed, D );
	gfx_LZDecompressSprite( E_data_compressed, E );
	gfx_LZDecompressSprite( F_data_compressed, F );
	gfx_LZDecompressSprite( G_data_compressed, G );
	gfx_LZDecompressSprite( H_data_compressed, H );
	gfx_LZDecompressSprite( I_data_compressed, I );
	gfx_LZDecompressSprite( J_data_compressed, J );
	gfx_LZDecompressSprite( K_data_compressed, K );
	gfx_LZDecompressSprite( L_data_compressed, L );
	gfx_LZDecompressSprite( M_data_compressed, M );
	gfx_LZDecompressSprite( N_data_compressed, N );
	gfx_LZDecompressSprite( O_data_compressed, O );
	gfx_LZDecompressSprite( P_data_compressed, P );
	gfx_LZDecompressSprite( Q_data_compressed, Q );
	gfx_LZDecompressSprite( R_data_compressed, R );
	gfx_LZDecompressSprite( S_data_compressed, S );
	gfx_LZDecompressSprite( T_data_compressed, T );
	gfx_LZDecompressSprite( U_data_compressed, U );
	gfx_LZDecompressSprite( V_data_compressed, V );
	gfx_LZDecompressSprite( W_data_compressed, W );
	gfx_LZDecompressSprite( X_data_compressed, X );
	gfx_LZDecompressSprite( Y_data_compressed, Y );
	gfx_LZDecompressSprite( Z_data_compressed, Z );
	
	gfx_SetDrawBuffer();
	ResetVars();
	while(Menu == 1 || Instructions == 1 || GameOver == 0){
		oldTime = time;
		time = rtc_Time();
		oneSecond = time - oldTime;
		MainMenu();
		Menu = 0;
		Instruction();
		Instructions = 0;
		if(GameOver == 0)
			Game();
	}
	gfx_End();
	pgrm_CleanUp();
	return 0;
}

gfx_image_t* SpaceCat0[2] = {
	SpaceCat,
	SpaceCatFlipped
};

gfx_image_t* Mouse[2] = {
	Mouse1,
	Mouse2
};

gfx_image_t* Star[2] = {
	Star1,
	Star2
};

gfx_image_t* Flame[2] = {
	Flame1,
	Flame2
};

gfx_image_t* SpaceCatHead0[2] = {
	SpaceCatHead,
	SpaceCatHead1
};

gfx_image_t* Numbers[10] = {
	font0,
	font1,
	font2,
	font3,
	font4,
	font5,
	font6,
	font7,
	font8,
	font9
};

gfx_image_t* Alphabet[26] = {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z
};

void PrintCustomFontH(int x, int y, char *Msg, int fontsize){
	int i, j, k = 0;
	char Upper[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char Num[10] = "0123456789";
	for(j = 0; j < strlen(Msg); j++){
		for(i = 0; i < 26; i++){
			if(Msg[j] == Upper[i]){
				gfx_ScaledTransparentSprite_NoClip(Alphabet[i], x + k * (7*fontsize), y, fontsize, fontsize);
				k++;
			}
		}
		for(i = 0; i < 10; i++){
			if(Msg[j] == Num[i]){
				gfx_ScaledTransparentSprite_NoClip(Numbers[i], x + k * (7*fontsize), y, fontsize, fontsize);
				k++;
			}
		}
		if(Msg[j] == ':'){
			gfx_ScaledTransparentSprite_NoClip(Colon, x + k * (7*fontsize), y, fontsize, fontsize);
			k++;
		}
		if(Msg[j] == '.'){
			gfx_ScaledTransparentSprite_NoClip(Period, x + k * (7*fontsize), y, fontsize, fontsize);
			k++;
		}
		if(Msg[j] == ' '){
			k++;
		}
	}
}

void PrintCustomFontV(int x, int y, char *Msg, int fontsize){
	int i, j, k = 0;
	char Upper[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char Num[10] = "0123456789";
	for(j = 0; j < strlen(Msg); j++){
		for(i = 0; i < 26; i++){
			if(Msg[j] == Upper[i]){
				gfx_ScaledTransparentSprite_NoClip(Alphabet[i], x, y + k * (7*fontsize), fontsize, fontsize);
				k++;
			}
		}
		for(i = 0; i < 10; i++){
			if(Msg[j] == Num[i]){
				gfx_ScaledTransparentSprite_NoClip(Numbers[i], x, y + k * (7*fontsize), fontsize, fontsize);
				k++;
			}
		}
		if(Msg[j] == ':'){
			gfx_ScaledTransparentSprite_NoClip(Colon, x, y + k * (7*fontsize), fontsize, fontsize);
			k++;
		}
		if(Msg[j] == '.'){
			gfx_ScaledTransparentSprite_NoClip(Period, x, y + k * (7*fontsize), fontsize, fontsize);
			k++;
		}
		if(Msg[j] == ' '){
			k++;
		}
	}
}



void ResetVars(){
	srand((unsigned) rtc_Time());
	Coins = 0;
	FuelBar = 200;
	HealthBar = 200;
	for(i = 0; i < 15; i++){
		StarX[i] = rand() % 320;
		StarY[i] = rand() % 240;
		StarState[i] = rand() % 2;
	}
	rndObject = rand() % 100;
	for(i = 0; i < 2; i++){
		if(rndObject >= 0 && rndObject < 25){
			Objects[i] = 1;						//Coin
			ObjectW[i] = 16;
			ObjectH[i] = 34;
		}
		if(rndObject >= 25 && rndObject < 50){
			Objects[i] = 2;						//Fuel
			ObjectW[i] = 28;
			ObjectH[i] = 20;
		}
		if(rndObject >= 50 && rndObject < 90){
			Objects[i] = 3;						//Asteroid
			ObjectW[i] = 64;
			ObjectH[i] = 64;
		}
		if(rndObject >= 90 && rndObject < 100){
			Objects[i] = 4;						//Mouse
			ObjectW[i] = 54;
			ObjectH[i] = 42;
		}
		ObjectX[i] = (rand() % 312) + 36;
		ObjectY[i] = -500 + (250 * i);
	}
	GameOver = 0;
	Menu = 1;
	Instructions = 0;
}

void drawBorder(){					//Draw fuel bar, health bar, and the score
	gfx_SetColor(0x11);
	gfx_FillRectangle_NoClip(0, 0, 36, 240);
	gfx_SetColor(0x05);
	gfx_VertLine_NoClip(35, 0, 240);
	gfx_SetColor(0x07);
	gfx_VertLine_NoClip(36, 0, 240);
	PrintCustomFontV(10, 10, "FUEL", 2);
	gfx_SetColor(0x07);
	gfx_FillRectangle_NoClip(11, 71, 12, 134);
	if(FuelBar > 0){
		gfx_SetColor(0x0E);
		gfx_FillRectangle_NoClip(12, 72, 10, (int)(FuelBar*0.66));
	}
	gfx_SetColor(0x11);
	gfx_FillRectangle_NoClip(284, 0, 36, 240);
	gfx_SetColor(0x05);
	gfx_VertLine_NoClip(285, 0, 240);
	gfx_SetColor(0x07);
	gfx_VertLine_NoClip(284, 0, 240);
	PrintCustomFontV(294, 10, "HEALTH", 2);
	gfx_SetColor(0x07);
	gfx_FillRectangle_NoClip(295, 100, 12, 106);
	if(HealthBar > 0){
		gfx_SetColor(0x00);
		gfx_FillRectangle_NoClip(296, 101, 10, (int)(HealthBar*0.52));
	}
	PrintCustomFontH(38, 222, "SCORE:", 2);
	sprintf(ScoreBuf, "%d", Coins);
	PrintCustomFontH(120, 222, ScoreBuf, 2);
}

void StarFunctions(){					//Draw stars
	for(i = 0; i < 15; i++){
		if(oneSecond == 1){
			alternator = 1 - alternator;
			StarState[i] = 1 - StarState[i];
		}
		gfx_TransparentSprite(Star[StarState[i]], StarX[i], StarY[i]);
		if(FuelBar > 0){
			gfx_ScaledTransparentSprite_NoClip(Flame[alternator], CatX + ((RL == 0) ? 2 : 32), CatY + 60, 2, 2);
			StarY[i]+=12;
			if(kb_ScanGroup(kb_group_7) == kb_Left) {
				RL = 1;
				StarX[i]+=4;
			} else if(kb_ScanGroup(kb_group_7) == kb_Right) {
				RL = 0;
				StarX[i]-=4;
			}
			if(StarY[i] > 240){
				StarX[i] = rand() % 320;
				StarY[i] = -6;
			}
			FuelBar-=.0625;
		}
	}
}

void ObjectFunctions(){					//Draw objects and their functions
	for(i = 0; i < 2; i++){
		if(Objects[i] != 0){
			if(FuelBar > 0){
				if(kb_ScanGroup(kb_group_7) == kb_Left) {
					ObjectX[i]+=4;
				} else if(kb_ScanGroup(kb_group_7) == kb_Right) {
					ObjectX[i]-=4;
				}
				if(ObjectY[i] < 216)
					ObjectY[i]+=12;
			}
			if(ObjectY[i] >= 216){
				ObjectY[i] = -500;
				ObjectX[i] = (rand() % 320);
				rndObject = rand() % 100;
				if(rndObject >= 0 && rndObject < 15){
					Objects[i] = 1;						//Coin
					ObjectW[i] = 16;
					ObjectH[i] = 34;
				}
				if(rndObject >= 15 && rndObject < 50){
					Objects[i] = 2;						//Fuel
					ObjectW[i] = 28;
					ObjectH[i] = 20;
				}
				if(rndObject >= 50 && rndObject < 90){
					Objects[i] = 3;						//Asteroid
					ObjectW[i] = 64;
					ObjectH[i] = 64;
				}
				if(rndObject >= 90 && rndObject < 100){
					Objects[i] = 4;						//Mouse
					ObjectW[i] = 54;
					ObjectH[i] = 42;
				}
			}
			if ((CatX < ObjectX[i] + ObjectW[i]) && (CatX + 44 > ObjectX[i]) && (CatY < ObjectY[i] + ObjectH[i]) && (70 + CatY > ObjectY[i])) {
				switch(Objects[i]){
				case 1:
					Coins++;
					break;
				case 2:
					FuelBar += 50;
					break;
				case 3:
					HealthBar -= 50;
					break;
				case 4:
					Coins += 5;
					break;
				}
				ObjectY[i] = -500 + (250 * i);
				ObjectX[i] = (rand() % 320);
				rndObject = rand() % 100;
				if(rndObject >= 0 && rndObject < 15){
					Objects[i] = 1;						//Coin
					ObjectW[i] = 16;
					ObjectH[i] = 34;
				}
				if(rndObject >= 15 && rndObject < 50){
					Objects[i] = 2;						//Fuel
					ObjectW[i] = 28;
					ObjectH[i] = 20;
				}
				if(rndObject >= 50 && rndObject < 90){
					Objects[i] = 3;						//Asteroid
					ObjectW[i] = 64;
					ObjectH[i] = 64;
				}
				if(rndObject >= 90 && rndObject < 100){
					Objects[i] = 4;						//Mouse
					ObjectW[i] = 54;
					ObjectH[i] = 42;
				}
			}
			if(Objects[i] == 1){
				gfx_TransparentSprite(Coin, ObjectX[i], (ObjectY[i] + (i * 20)));
			}
			if(Objects[i] == 2){
				gfx_TransparentSprite(Fuel, ObjectX[i], (ObjectY[i] + (i * 20)));
			}
			if(Objects[i] == 3){
				gfx_TransparentSprite(Asteroid, ObjectX[i], (ObjectY[i] + (i * 20)));
			}
			if(Objects[i] == 4){
				gfx_TransparentSprite(Mouse[alternator], ObjectX[i], (ObjectY[i] + (i * 20)));
			}
		}
	}
	if(FuelBar > 200)
		FuelBar = 200;
}

void MainMenu(){					//Main menu screen
	int Head1X = 99, Head1Y = 75, Head2X = 250, Head2Y = 75, Option = 0;
	GameOver = 1;
	while(Menu && kb_ScanGroup(kb_group_6) != kb_Clear){
		gfx_FillScreen(0x26);
		oldTime = time;
		time = rtc_Time();
		oneSecond = time - oldTime;
		for(i = 0; i < 15; i++){
			if(oneSecond == 1){
				alternator = 1 - alternator;
				StarState[i] = 1 - StarState[i];
			}
			gfx_TransparentSprite(Star[StarState[i]], StarX[i], StarY[i]);
		}
		if(kb_ScanGroup(kb_group_7) == kb_Up || kb_ScanGroup(kb_group_7) == kb_Down)
			Option = 1 - Option;
		if(Option == 0){
			Head1X = 67;
			Head1Y = 75;
			Head2X = 218;
			Head2Y = 75;
		} else if(Option == 1){
			Head1X = 6;
			Head1Y = 102;
			Head2X = 280;
			Head2Y = 102;
		}
		PrintCustomFontH(15, 0, "CATYLIZM", 5);
		PrintCustomFontH(104, 84, "START", 3);
		PrintCustomFontH(43, 111, "HOW TO PLAY", 3);	
		PrintCustomFontH(25, 198, "PRESS CLEAR TO QUIT", 2);
		gfx_ScaledTransparentSprite_NoClip(SpaceCatHead0[0], Head1X, Head1Y, 2, 2);
		gfx_ScaledTransparentSprite_NoClip(SpaceCatHead0[1], Head2X, Head2Y, 2, 2);
		if(kb_ScanGroup(kb_group_1) == kb_2nd || kb_ScanGroup(kb_group_6) == kb_Enter){
			if(Option == 0){
				Menu = 0;
				GameOver = 0;
			} else if(Option == 1){
				Menu = 0;
				Instructions = 1;
			}
		}
		gfx_SwapDraw();
	}
}

void Instruction(){				//Instruction screen
		while(Instructions && kb_ScanGroup(kb_group_6) != kb_Clear){
			gfx_FillScreen(0x26);
			oldTime = time;
			time = rtc_Time();
			oneSecond = time - oldTime;
			for(i = 0; i < 15; i++){
				if(oneSecond == 1){
					alternator = 1 - alternator;
					StarState[i] = 1 - StarState[i];
				}
				gfx_TransparentSprite(Star[StarState[i]], StarX[i], StarY[i]);
			}
			PrintCustomFontH(15, 0, "CATYLIZM", 5);
			PrintCustomFontH(4, 64, "USE THE LEFT AND RIGHT", 2);
			PrintCustomFontH(19, 84, "ARROWS TO MOVE SPACE", 2);
			PrintCustomFontH(0, 104, "CAT CARL THROUGH SPACE.", 2);
			PrintCustomFontH(4, 124, "COLLECT COINS AND MICE", 2);
			PrintCustomFontH(4, 144, "TO SCORE POINTS. AVOID", 2);
			PrintCustomFontH(4, 164, "ASTEROIDS AND DONT RUN", 2);
			PrintCustomFontH(82, 184, "OUT OF FUEL", 2);
			PrintCustomFontH(91, 204, "GOOD LUCK.", 2);
			gfx_SwapDraw();
			if(kb_ScanGroup(kb_group_2) == kb_Alpha){
				Instructions = 0;
				Menu = 1;
			}
	}
}

void Game(){
	while(GameOver == 0 && kb_ScanGroup(kb_group_6) != kb_Clear){
		oldTime = time;
		time = rtc_Time();
		oneSecond = time - oldTime;
		gfx_FillScreen(0x26);
		StarFunctions();
		ObjectFunctions();
		if(FuelBar <= 0){
			FuelBar = 0;
			GameOver = 1;
		}
		if(HealthBar <= 0){
			HealthBar = 0;
			GameOver = 1;
		}
		gfx_ScaledTransparentSprite_NoClip(SpaceCat0[RL], CatX, CatY, 2, 2);
		drawBorder();
		gfx_SwapDraw();
	}
	gfx_FillScreen(0x26);
	StarFunctions();
	ObjectFunctions();
	gfx_ScaledTransparentSprite_NoClip(SpaceCat0[RL], CatX, CatY, 2, 2);
	drawBorder();
	while(GameOver == 1 && kb_ScanGroup(kb_group_6) != kb_Clear){
		oldTime = time;
		time = rtc_Time();
		oneSecond = time - oldTime;
		gfx_FillScreen(0x26);
		StarFunctions();
		ObjectFunctions();
		gfx_ScaledTransparentSprite_NoClip(SpaceCat0[RL], CatX, CatY, 2, 2);
		drawBorder();
		PrintCustomFontH(0, 89, "GAME OVER", 5);
		PrintCustomFontH(55, 129, "PRESS ALPHA FOR", 2);
		PrintCustomFontH(96, 149, "MAIN MENU", 2);
		if(kb_ScanGroup(kb_group_2) == kb_Alpha){
			ResetVars();
		}
		gfx_SwapDraw();
	}
}
