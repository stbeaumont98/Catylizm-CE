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

#include "gfx\gfx.h"
#include "gfx\font.h"

#define COLOR_RED 0x00
#define COLOR_BLACK 0x01
#define COLOR_WHITE 0x02
#define COLOR_GRAY 0x03
#define COLOR_DARK_GRAY 0x04
#define COLOR_GREEN 0x05

#define OBJECT_BIG_ASTEROID 0
#define OBJECT_SMALL_ASTEROID 1
#define OBJECT_FUEL_CELL 2
#define OBJECT_GOLD_NUGGET 3
#define OBJECT_SPACE_MOUSE 4

#define BIG_ASTEROID_WIDTH 32
#define BIG_ASTEROID_HEIGHT 32
#define SMALL_ASTEROID_WIDTH 22
#define SMALL_ASTEROID_HEIGHT 22
#define FUEL_CELL_WIDTH 14
#define FUEL_CELL_HEIGHT 10
#define GOLD_NUGGET_WIDTH 16
#define GOLD_NUGGET_HEIGHT 16
#define SPACE_MOUSE_WIDTH 52
#define SPACE_MOUSE_HEIGHT 30

struct Star {
	uint16_t x;
	uint8_t y;
	uint8_t state;
	uint8_t scale;
};

struct Object {
	uint8_t type;
	uint16_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
	bool alive;
};

struct Player {
	uint16_t x;
	uint8_t y;
	float health;
	float fuel;
	uint8_t score;
};

/* Function prototypes */
void draw_text(char* text, uint8_t color, uint16_t x, uint8_t y, int scale);
void draw_int(int i, uint8_t color, uint16_t x, uint8_t y, int scale);
void draw_text_v(char* text, uint8_t color, uint16_t x, uint8_t y, int scale);
void init_object(struct Object *o);
void init_game();
void draw_game_border();
void draw_star(struct Star s);
void draw_object(struct Object o);

// Global variables
struct Star stars[30];
struct Player p = { 138, 170, 200, 200, 0 };
struct Object object;
bool game_over = true;
bool in_menu = true;
bool in_instructions = false;

int main(void) {
	int i;
	int old_time, time, one_second, alternator = 0;
	int right_or_left = 0;
	bool can_press = false;
	int menu_option = 0;

	int object_countdown = 0;

	gfx_Begin(gfx_8bpp);
	gfx_SetPalette(palette, sizeof(palette), 0);
	gfx_SetDrawBuffer();

	/* Set up the font */
    gfx_SetFontData(font);
    gfx_SetFontSpacing(font_spacing);
	gfx_SetFontHeight(6);

	gfx_SetTransparentColor(COLOR_RED);

	init_game();
	while (!(kb_Data[6] & kb_Clear)) {
		kb_Scan();
		old_time = time;
		time = rtc_Time();
		one_second = time - old_time;
		gfx_FillScreen(COLOR_BLACK);

		for (i = 0; i < 30; i++) {
			if (one_second)
				stars[i].state = 1 - stars[i].state;
			draw_star(stars[i]);
		}

		if (in_menu) {
			int left_head_x = 82, left_head_y = 74, right_head_x = 204, right_head_y = 74;
			if (can_press && (kb_Data[7] & kb_Up || kb_Data[7] & kb_Down)) {
				menu_option = 1 - menu_option;
				can_press = false;
			}
			if (menu_option == 0) {
				left_head_x = 77;
				left_head_y = 70;
				right_head_x = 209;
				right_head_y = 70;
			} else if (menu_option == 1) {
				left_head_x = 32;
				left_head_y = 95;
				right_head_x = 254;
				right_head_y = 95;
			}
			draw_text("CATYLIZM", COLOR_WHITE, 60, 15, 5);
			draw_text("START", COLOR_WHITE, 121, 84, 3);
			draw_text("HOW TO PLAY", COLOR_WHITE, 76, 111, 3);	
			draw_text("PRESS CLEAR TO QUIT", COLOR_WHITE, 65, 198, 2);
			gfx_ScaledTransparentSprite_NoClip(cat_head, left_head_x, left_head_y, 2, 2);
			gfx_sprite_t *cat_head2 = gfx_MallocSprite(17, 17);
			gfx_FlipSpriteY(cat_head, cat_head2);
			gfx_ScaledTransparentSprite_NoClip(cat_head2, right_head_x, right_head_y, 2, 2);
			free(cat_head2);
			if (can_press && (kb_Data[1] & kb_2nd || kb_Data[6] & kb_Enter)) {
				if (menu_option == 0) {
					in_menu = false;
					game_over = false;
				} else if (menu_option == 1) {
					in_menu = false;
					in_instructions = true;
				}
				can_press = false;
			}
		} else if (in_instructions) {
			draw_text("CATYLIZM", COLOR_WHITE, 60, 15, 5);
			draw_text("Use the left and right", COLOR_WHITE, 58, 64, 2);
			draw_text("arrows to move space", COLOR_WHITE, 62, 84, 2);
			draw_text("cat Carl through space.", COLOR_WHITE, 51, 104, 2);
			draw_text("Collect coins and mice", COLOR_WHITE, 58, 124, 2);
			draw_text("to score points. Avoid", COLOR_WHITE, 63, 144, 2);
			draw_text("asteroids and don't run", COLOR_WHITE, 56, 164, 2);
			draw_text("out of fuel.", COLOR_WHITE, 110, 184, 2);
			draw_text("Good luck.", COLOR_WHITE, 113, 204, 2);
			if (can_press && (kb_Data[2] & kb_Alpha || kb_Data[1] & kb_2nd || kb_Data[6] & kb_Enter)) {
				in_instructions = false;
				in_menu = true;
				can_press = false;
			}
		} else {
			if (one_second) {
				alternator = 1 - alternator;
				object_countdown--;
			}

			for (i = 0; i < 30; i++) {
				if (stars[i].y < 240)
					stars[i].y += 8;
				else {
					stars[i].x = rand() % 320;
					stars[i].y = 0;
				}
			}

			if ((p.x < object.x + object.width) && (p.x + 40 > object.x) && (p.y < object.y + object.height) && (70 + p.y > object.y) && object.alive) {
				switch (object.type) {
					case OBJECT_GOLD_NUGGET:
						p.score++;
						break;
					case OBJECT_FUEL_CELL:
						p.fuel += 50;
						break;
					case OBJECT_BIG_ASTEROID:
						p.health -= 25;
						break;
					case OBJECT_SMALL_ASTEROID:
						p.health -= 10;
						break;
					case OBJECT_SPACE_MOUSE:
						p.score += 5;
						break;
				}
				object.alive = false;
				object_countdown = rand() % 3 + 3;
			}
			if (object.y < (240 - object.height) && object.x < (320 - object.width) && object.x > 0 && object.alive) {
				draw_object(object);
				object.y += 4;
			}
			if (object_countdown == 0) {
				init_object(&object);
				object_countdown = rand() % 3 + 3;
			}

			if (p.fuel > 0) {
				if (kb_Data[7] & kb_Left) {
						right_or_left = 1;
						for (i = 0; i < 30; i++)
							stars[i].x += 4;
						object.x += 2;
				} else if (kb_Data[7] & kb_Right) {
						right_or_left = 0;
						for (i = 0; i < 30; i++)
							stars[i].x -= 4;
						object.x -= 2;
				}
				p.fuel -= .25;
			}
			if (p.fuel > 200)
				p.fuel = 200;
			if (p.fuel <= 0) {
				p.fuel = 0;
				game_over = true;
			}
			if (p.health <= 0) {
				p.health = 0;
				game_over = true;
			}
			gfx_sprite_t *flipped_cat = gfx_MallocSprite(20, 35);
			gfx_FlipSpriteY(cat, flipped_cat);
			gfx_ScaledTransparentSprite_NoClip((right_or_left ? flipped_cat : cat), p.x, p.y, 2, 2);
			free(flipped_cat);
			//gfx_ScaledTransparentSprite_NoClip(Flame[alternator], p.x + ((right_or_left == 0) ? 0 : 30), p.y + 60, 2, 2);
			draw_game_border();
			if (game_over) {
				draw_text("GAME OVER", COLOR_WHITE, 47, 89, 5);
				draw_text("PRESS ALPHA FOR", COLOR_WHITE, 86, 129, 2);
				draw_text("MAIN MENU", COLOR_WHITE, 115, 149, 2);
				if (kb_Data[2] & kb_Alpha) {
					init_game();
				}
			}
		}
		if (!kb_AnyKey())
			can_press = true;
		gfx_SwapDraw();
	}

	gfx_End();
	pgrm_CleanUp();
	return 0;
}

void draw_text(char* text, uint8_t color, uint16_t x, uint8_t y, int scale) {
	gfx_SetTextFGColor(color);
    gfx_SetTextBGColor(COLOR_RED);
    gfx_SetTextTransparentColor(COLOR_RED);
    gfx_SetTextXY(x, y);
	gfx_SetTextScale(scale, scale);
	gfx_PrintString(text);
}

void draw_int(int i, uint8_t color, uint16_t x, uint8_t y, int scale) {
	gfx_SetTextFGColor(color);
    gfx_SetTextBGColor(COLOR_RED);
    gfx_SetTextTransparentColor(COLOR_RED);
    gfx_SetTextXY(x, y);
	gfx_SetTextScale(scale, scale);
	gfx_PrintInt(i, 1);
}

void draw_text_v(char *text, uint8_t color, uint16_t x, uint8_t y, int scale) {
	uint8_t i;
	
	gfx_SetTextFGColor(color);
    gfx_SetTextBGColor(COLOR_RED);
    gfx_SetTextTransparentColor(COLOR_RED);
	gfx_SetTextScale(scale, scale);

	for (i = 0; i < strlen(text); i++) {
		gfx_SetTextXY(x, y + (i * 6 * scale));
		gfx_PrintChar(text[i]);
	}
}

void init_object(struct Object *o) {
	o->alive = true;
	o->type = rand() % 5;
	switch (o->type) {
		case OBJECT_BIG_ASTEROID:
			o->width = BIG_ASTEROID_WIDTH;
			o->height = BIG_ASTEROID_HEIGHT;
			break;
		case OBJECT_SMALL_ASTEROID:
			o->width = SMALL_ASTEROID_WIDTH;
			o->height = SMALL_ASTEROID_HEIGHT;
			break;
		case OBJECT_FUEL_CELL:
			o->width = FUEL_CELL_WIDTH;
			o->height = FUEL_CELL_HEIGHT;
			break;
		case OBJECT_GOLD_NUGGET:
			o->width = GOLD_NUGGET_WIDTH;
			o->height = GOLD_NUGGET_HEIGHT;
			break;
		case OBJECT_SPACE_MOUSE:
			o->width = SPACE_MOUSE_WIDTH;
			o->height = SPACE_MOUSE_HEIGHT;
			break;
		default:
			break;
	}
	o->x = rand() % (320 - o->width);
	o->y = 0;
}

void init_game() {
	int i;
	srand((unsigned) rtc_Time());
	p.score = 0;
	p.fuel = 200;
	p.health = 200;
	for (i = 0; i < 30; i++)
	{
		stars[i].x = rand() % 320;
		stars[i].y = rand() % 240;
		stars[i].state = rand() % 2;
		stars[i].scale = rand() % 2 + 1;
	}
	init_object(&object);
	game_over = true;
	in_menu = true;
	in_instructions = false;
}

void draw_game_border() {					//Draw fuel bar, health bar, and the p.score
	gfx_SetColor(COLOR_GRAY);
	gfx_FillRectangle_NoClip(0, 0, 36, 240);
	gfx_SetColor(COLOR_WHITE);
	gfx_VertLine_NoClip(35, 0, 240);
	gfx_SetColor(COLOR_DARK_GRAY);
	gfx_VertLine_NoClip(36, 0, 240);
	draw_text_v("FUEL", COLOR_BLACK, 13, 10, 2);
	gfx_SetColor(COLOR_BLACK);
	gfx_FillRectangle_NoClip(11, 71, 12, 134);
	if (p.fuel > 0) {
		gfx_SetColor(COLOR_GREEN);
		gfx_FillRectangle_NoClip(12, 72, 10, (int)(p.fuel*0.66));
	}
	gfx_SetColor(COLOR_GRAY);
	gfx_FillRectangle_NoClip(284, 0, 36, 240);
	gfx_SetColor(COLOR_WHITE);
	gfx_VertLine_NoClip(285, 0, 240);
	gfx_SetColor(COLOR_DARK_GRAY);
	gfx_VertLine_NoClip(284, 0, 240);
	draw_text_v("HEALTH", COLOR_BLACK, 297, 10, 2);
	gfx_SetColor(COLOR_BLACK);
	gfx_FillRectangle_NoClip(295, 100, 12, 106);
	if (p.health > 0) {
		gfx_SetColor(COLOR_RED);
		gfx_FillRectangle_NoClip(296, 101, 10, (int)(p.health*0.52));
	}
	draw_text("SCORE:", COLOR_WHITE, 38, 222, 2);
	draw_int(p.score, COLOR_WHITE, 96, 222, 2);
}

/* draw_star()
 * Draws a star
 *
 * Parameters:
 * 		s: Conatains the star's x and y coordinates, its state, and its scale
 */
void draw_star(struct Star s) {
	gfx_SetColor(COLOR_WHITE);
	if (s.state == 1) {
		gfx_FillRectangle(s.x + s.scale, s.y + s.scale, s.scale, s.scale);
	} else {
		gfx_FillRectangle(s.x, s.y + s.scale, s.scale, s.scale);
		gfx_FillRectangle(s.x + s.scale, s.y, s.scale, s.scale);
		gfx_FillRectangle(s.x + s.scale, s.y + s.scale * 2, s.scale, s.scale);
		gfx_FillRectangle(s.x + s.scale * 2, s.y + s.scale, s.scale, s.scale);
	}
}

/* draw_object()
 * Draws an object
 *
 * Parameters:
 * 		o: Contains the object's x and y coordinates, its width, height, and type
 */
void draw_object(struct Object o) {
	switch (o.type) {
		case OBJECT_BIG_ASTEROID:
			gfx_ScaledTransparentSprite_NoClip(big_asteroid, o.x, o.y, 3, 3);
			break;
		case OBJECT_SMALL_ASTEROID:
			gfx_ScaledTransparentSprite_NoClip(small_asteroid, o.x, o.y, 3, 3);
			break;
		case OBJECT_FUEL_CELL:
			gfx_ScaledTransparentSprite_NoClip(fuel_cell, o.x, o.y, 2, 2);
			break;
		case OBJECT_GOLD_NUGGET:
			gfx_ScaledTransparentSprite_NoClip(gold_nugget, o.x, o.y, 2, 2);
			break;
		case OBJECT_SPACE_MOUSE:
			gfx_ScaledTransparentSprite_NoClip(full_mouse, o.x, o.y, 2, 2);
			break;
		
		default:
			break;
	}
}