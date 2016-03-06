#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <CatSprites.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphc.h>
#include <keypadc.h>


void PrintCustomFontH(int x, int y, char *Msg, int fontsize){
	int i, j, k = 0;
	char Upper[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char Num[10] = "0123456789";
	for(j = 0; j < strlen(Msg); j++){
		for(i = 0; i < 26; i++){
			if(Msg[j] == Upper[i]){
				gc_NoClipDrawScaledTransparentSprite(Alphabet[i], x + k * (7*fontsize), y, 8, 9, fontsize, fontsize);
				k++;
			}
		}
		for(i = 0; i < 10; i++){
			if(Msg[j] == Num[i]){
				gc_NoClipDrawScaledTransparentSprite(Numbers[i], x + k * (7*fontsize), y, 8, 9, fontsize, fontsize);
				k++;
			}
		}
		if(Msg[j] == ':'){
			gc_NoClipDrawScaledTransparentSprite(Colon, x + k * (7*fontsize), y, 8, 9, fontsize, fontsize);
			k++;
		}
		if(Msg[j] == '.'){
			gc_NoClipDrawScaledTransparentSprite(Period, x + k * (7*fontsize), y, 8, 9, fontsize, fontsize);
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
				gc_NoClipDrawScaledTransparentSprite(Alphabet[i], x, y + k * (7*fontsize), 8, 9, fontsize, fontsize);
				k++;
			}
		}
		for(i = 0; i < 10; i++){
			if(Msg[j] == Num[i]){
				gc_NoClipDrawScaledTransparentSprite(Numbers[i], x, y + k * (7*fontsize), 8, 9, fontsize, fontsize);
				k++;
			}
		}
		if(Msg[j] == ':'){
			gc_NoClipDrawScaledTransparentSprite(Colon, x, y + k * (7*fontsize), 8, 9, fontsize, fontsize);
			k++;
		}
		if(Msg[j] == '.'){
			gc_NoClipDrawScaledTransparentSprite(Period, x, y + k * (7*fontsize), 8, 9, fontsize, fontsize);
			k++;
		}
		if(Msg[j] == ' '){
			k++;
		}
	}
}


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

void ResetVars(){
	srand((unsigned) rtc_GetSeconds());
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
	gc_SetColorIndex(0x0A);
	gc_NoClipRectangle(0, 0, 36, 240);
	gc_SetColorIndex(0x26);
	gc_NoClipLine(35, 0, 35, 240);
	gc_SetColorIndex(0x00);
	gc_NoClipLine(36, 0, 36, 240);
	PrintCustomFontV(10, 10, "FUEL", 2);
	gc_SetColorIndex(0x00);
	gc_NoClipRectangle(11, 71, 12, 134);
	if(FuelBar > 0){
		gc_SetColorIndex(0x20);
		gc_NoClipRectangle(12, 72, 10, (int)(FuelBar*0.66));
	}
	gc_SetColorIndex(0x0A);
	gc_NoClipRectangle(284, 0, 36, 240);
	gc_SetColorIndex(0x26);
	gc_NoClipLine(285, 0, 285, 240);
	gc_SetColorIndex(0x00);
	gc_NoClipLine(284, 0, 284, 240);
	PrintCustomFontV(294, 10, "HEALTH", 2);
	gc_SetColorIndex(0x00);
	gc_NoClipRectangle(295, 100, 12, 106);
	if(HealthBar > 0){
		gc_SetColorIndex(0x02);
		gc_NoClipRectangle(296, 101, 10, (int)(HealthBar*0.52));
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
		gc_NoClipDrawScaledTransparentSprite(Star[StarState[i]], StarX[i], StarY[i], 3, 3, 2, 2);
		if(FuelBar > 0){
			gc_NoClipDrawScaledTransparentSprite(Flame[alternator], CatX + ((RL == 0) ? 2 : 32), CatY + 60, 5, 5, 2, 2);
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
				gc_NoClipDrawScaledTransparentSprite(Coin, ObjectX[i], (ObjectY[i] + (i * 20)), 8, 17, 2, 2);
			}
			if(Objects[i] == 2){
				gc_NoClipDrawScaledTransparentSprite(Fuel, ObjectX[i], (ObjectY[i] + (i * 20)), 14, 10, 2, 2);
			}
			if(Objects[i] == 3){
				gc_NoClipDrawScaledTransparentSprite(Asteroid, ObjectX[i], (ObjectY[i] + (i * 20)), 32, 32, 2, 2);
			}
			if(Objects[i] == 4){
				gc_NoClipDrawScaledTransparentSprite(Mouse[alternator], ObjectX[i], (ObjectY[i] + (i * 20)), 27, 21, 2, 2);
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
		gc_FillScrn(0x03);
		oldTime = time;
		time = rtc_GetSeconds();
		oneSecond = time - oldTime;
		for(i = 0; i < 15; i++){
			if(oneSecond == 1){
				alternator = 1 - alternator;
				StarState[i] = 1 - StarState[i];
			}
			gc_NoClipDrawScaledTransparentSprite(Star[StarState[i]], StarX[i], StarY[i], 3, 3, 2, 2);
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
		gc_NoClipDrawScaledTransparentSprite(SpaceCatHead[0], Head1X, Head1Y, 17, 17, 2, 2);
		gc_NoClipDrawScaledTransparentSprite(SpaceCatHead[1], Head2X, Head2Y, 17, 17, 2, 2);
		if(kb_ScanGroup(kb_group_1) == kb_2nd || kb_ScanGroup(kb_group_6) == kb_Enter){
			if(Option == 0){
				Menu = 0;
				GameOver = 0;
			} else if(Option == 1){
				Menu = 0;
				Instructions = 1;
			}
		}
		gc_SwapDraw();
	}
}

void Instruction(){				//Instruction screen
		while(Instructions && kb_ScanGroup(kb_group_6) != kb_Clear){
			gc_FillScrn(0x03);
			oldTime = time;
			time = rtc_GetSeconds();
			oneSecond = time - oldTime;
			for(i = 0; i < 15; i++){
				if(oneSecond == 1){
					alternator = 1 - alternator;
					StarState[i] = 1 - StarState[i];
				}
				gc_NoClipDrawScaledTransparentSprite(Star[StarState[i]], StarX[i], StarY[i], 3, 3, 2, 2);
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
			gc_SwapDraw();
			if(kb_ScanGroup(kb_group_2) == kb_Alpha){
				Instructions = 0;
				Menu = 1;
			}
	}
}

void Game(){
	while(GameOver == 0 && kb_ScanGroup(kb_group_6) != kb_Clear){
		oldTime = time;
		time = rtc_GetSeconds();
		oneSecond = time - oldTime;
		gc_FillScrn(0x03);
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
		gc_NoClipDrawScaledTransparentSprite(SpaceCat[RL], CatX, CatY, 22, 35, 2, 2);
		drawBorder();
		gc_SwapDraw();
	}
	gc_FillScrn(0x03);
	StarFunctions();
	ObjectFunctions();
	gc_NoClipDrawScaledTransparentSprite(SpaceCat[RL], CatX, CatY, 22, 35, 2, 2);
	drawBorder();
	while(GameOver == 1 && kb_ScanGroup(kb_group_6) != kb_Clear){
		PrintCustomFontH(0, 89, "GAME OVER", 5);
		PrintCustomFontH(55, 129, "PRESS ALPHA FOR", 2);
		PrintCustomFontH(96, 149, "MAIN MENU", 2);
		if(kb_ScanGroup(kb_group_2) == kb_Alpha){
			ResetVars();
		}
		gc_SwapDraw();
	}
}

int main(void) {
	gc_InitGraph();
	gc_SetPalette(CatPalette, sizeof(CatPalette));
	gc_DrawBuffer();
	ResetVars();
	while(Menu == 1 || Instructions == 1 || GameOver == 0){
		oldTime = time;
		time = rtc_GetSeconds();
		oneSecond = time - oldTime;
		MainMenu();
		Menu = 0;
		Instruction();
		Instructions = 0;
		if(GameOver == 0)
			Game();
	}
	gc_CloseGraph();
	pgrm_CleanUp();
	return 0;
}
