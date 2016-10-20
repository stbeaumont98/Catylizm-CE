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

gfx_image_t *Asteroid, *Coin, *Fuel, *Period, *Colon, *SpaceCat[2], *Mouse[2], *Star[2], *Flame[2], *SpaceCatHead[2], *Numbers[10], *Alphabet[26];



uint8_t* SpaceCat_compressed[2] = {
	SpaceCat_data_compressed,
	SpaceCatFlipped_data_compressed
};

uint8_t* Mouse_compressed[2] = {
	Mouse1_data_compressed,
	Mouse2_data_compressed
};

uint8_t* Star_compressed[2] = {
	Star1_data_compressed,
	Star2_data_compressed
};

uint8_t* Flame_compressed[2] = {
	Flame1_data_compressed,
	Flame2_data_compressed
};

uint8_t* SpaceCatHead_compressed[2] = {
	SpaceCatHead_data_compressed,
	SpaceCatHead1_data_compressed
};

uint8_t* Numbers_compressed[10] = {
	font0_data_compressed,
	font1_data_compressed,
	font2_data_compressed,
	font3_data_compressed,
	font4_data_compressed,
	font5_data_compressed,
	font6_data_compressed,
	font7_data_compressed,
	font8_data_compressed,
	font9_data_compressed
};

uint8_t* Alphabet_compressed[26] = {
	A_data_compressed,
	B_data_compressed,
	C_data_compressed,
	D_data_compressed,
	E_data_compressed,
	F_data_compressed,
	G_data_compressed,
	H_data_compressed,
	I_data_compressed,
	J_data_compressed,
	K_data_compressed,
	L_data_compressed,
	M_data_compressed,
	N_data_compressed,
	O_data_compressed,
	P_data_compressed,
	Q_data_compressed,
	R_data_compressed,
	S_data_compressed,
	T_data_compressed,
	U_data_compressed,
	V_data_compressed,
	W_data_compressed,
	X_data_compressed,
	Y_data_compressed,
	Z_data_compressed
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
		gfx_ScaledTransparentSprite_NoClip(SpaceCatHead[0], Head1X, Head1Y, 2, 2);
		gfx_ScaledTransparentSprite_NoClip(SpaceCatHead[1], Head2X, Head2Y, 2, 2);
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
		gfx_ScaledTransparentSprite_NoClip(SpaceCat[RL], CatX, CatY, 2, 2);
		drawBorder();
		gfx_SwapDraw();
	}
	gfx_FillScreen(0x26);
	StarFunctions();
	ObjectFunctions();
	gfx_ScaledTransparentSprite_NoClip(SpaceCat[RL], CatX, CatY, 2, 2);
	drawBorder();
	while(GameOver == 1 && kb_ScanGroup(kb_group_6) != kb_Clear){
		oldTime = time;
		time = rtc_Time();
		oneSecond = time - oldTime;
		gfx_FillScreen(0x26);
		StarFunctions();
		ObjectFunctions();
		gfx_ScaledTransparentSprite_NoClip(SpaceCat[RL], CatX, CatY, 2, 2);
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

void decompressSprites(){
	int i;
	
	malloc(0);
	
	Asteroid = gfx_AllocSprite( 64, 64, malloc );
	Coin = gfx_AllocSprite( 16, 34, malloc );
	Fuel = gfx_AllocSprite( 28, 20, malloc );
	Period = gfx_AllocSprite( 8, 9, malloc );
	Colon = gfx_AllocSprite( 8, 9, malloc );
	
	for(i = 0; i < 2; i++){
		SpaceCat[i] = gfx_AllocSprite( 22, 35, malloc );
		Flame[i] = gfx_AllocSprite( 5, 5, malloc );
		Star[i] = gfx_AllocSprite( 6, 6, malloc );
		SpaceCatHead[i] = gfx_AllocSprite( 17, 17, malloc );
		Mouse[i] = gfx_AllocSprite( 54, 42, malloc );
	}
	
	for(i = 0; i < 26; i++)
		Alphabet[i] = gfx_AllocSprite( 8, 9, malloc );
	
	for(i = 0; i < 10; i++)
		Numbers[i] = gfx_AllocSprite( 8, 9, malloc );
	
	
	gfx_LZDecompressSprite( Asteroid_data_compressed, Asteroid );
	gfx_LZDecompressSprite( Coin_data_compressed, Coin );
	gfx_LZDecompressSprite( Fuel_data_compressed, Fuel );
	gfx_LZDecompressSprite( Period_data_compressed, Period );
	gfx_LZDecompressSprite( Colon_data_compressed, Colon );
	
	for(i = 0; i < 2; i++){
		gfx_LZDecompressSprite( SpaceCat_compressed[i], SpaceCat[i] );
		gfx_LZDecompressSprite( Flame_compressed[i], Flame[i] );
		gfx_LZDecompressSprite( Star_compressed[i], Star[i] );
		gfx_LZDecompressSprite( SpaceCatHead_compressed[i], SpaceCatHead[i] );
		gfx_LZDecompressSprite( Mouse_compressed[i], Mouse[i] );
	}
	
	for(i = 0; i < 26; i++)
		gfx_LZDecompressSprite( Alphabet_compressed[i], Alphabet[i] );
	
	for(i = 0; i < 10; i++)
		gfx_LZDecompressSprite( Numbers_compressed[i], Numbers[i] );
	
}

void freeSprites(){
	int i;
	
	free(Asteroid);
	free(Coin);
	free(Fuel);
	free(Period);
	free(Colon);
	
	for(i = 0; i < 2; i++){
		free(SpaceCat[i]);
		free(Flame[i]);
		free(Star[i]);
		free(SpaceCatHead[i]);
		free(Mouse[i]);
	}
	
	for(i = 0; i < 26; i++)
		free(Alphabet[i]);
	
	for(i = 0; i < 10; i++)
		free(Numbers[i]);
}

int main(void) {
	gfx_Begin(gfx_8bpp);
	gfx_SetPalette(gfx_group_1_pal, sizeof(gfx_group_1_pal), 0);
	gfx_SetDrawBuffer();
	decompressSprites();
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
	freeSprites();
	gfx_End();
	pgrm_CleanUp();
	return 0;
}