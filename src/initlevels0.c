/***************************************************************************
 *   Copyright (C) 2010 by Travis Thompson                                 *
 *   travisat@gmail.com			                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#include "blumps.h"
#include "draw.h"
#define BACK_PATH "images/levelset1/back.png"
#define BLUMPY_STILL "images/levelset1/blumpy.png"
#define BLUMPY_LEFT "images/levelset1/blumpy_left.png"
#define BLUMPY_RIGHT "images/levelset1/blumpy_right.png"
#define BLUMPY_DEAD "images/levelset1/blumpy_dead.png"
#define BLUMPY_MASK "images/levelset1/bmask.png"
#define BLOCK_PATH "images/levelset1/block.png"
#define WALL_LEFT "images/levelset1/wall_left.png"
#define WALL_RIGHT "images/levelset1/wall_right.png"
#define WALL_TOP  "images/levelset1/wall_top.png"
#define WALL_BOTTOM "images/levelset1/wall_bottom.png"
#define WALL_WATER "images/levelset1/wall_water.png"
#define EXIT_PATH "images/levelset1/exit.png"
#define PAUSE_PATH "images/levelset1/pause.png"

void initLevel00(S_level *level){
	level->text = "Level 00";

	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT); 
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 7;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 350;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 382;
	level->block[0].vec.x = 2;
	level->block[0].vec.y = 0;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 0;
	level->block[1].image.area.y = HEIGHT - 85;
	level->block[1].image.area.x2 = 256;
	level->block[1].image.area.y2 = HEIGHT - 53;
	level->block[1].vec.x = 0;
	level->block[1].vec.y = 0;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(WALL_BOTTOM);

	level->block[2].image.area.x = 0;
	level->block[2].image.area.y = 0;
	level->block[2].image.area.x2 = WIDTH;
	level->block[2].image.area.y2 = 4;
	level->block[2].vec.x = 0;
	level->block[2].vec.y = 0;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(WALL_TOP);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = 4;
	level->block[3].image.area.x2 = 4;
	level->block[3].image.area.y2 = HEIGHT - 85;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_LEFT);
	 
	level->block[4].image.area.x = WIDTH - 4;
	level->block[4].image.area.y = 4;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = HEIGHT;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_RIGHT);

	level->block[5].image.area.x = WIDTH - 153;
	level->block[5].image.area.y = 382;
	level->block[5].image.area.x2 = WIDTH - 25;
	level->block[5].image.area.y2 = 414;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(BLOCK_PATH);

	level->block[6].image.area.x = 256;
	level->block[6].image.area.y = HEIGHT - 32;
	level->block[6].image.area.x2 = WIDTH - 32;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 1;
	level->block[6].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel01(S_level *level){
	level->text = "Level 01";

	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 9;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 300;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 332;
	level->block[0].vec.x = 0;
	level->block[0].vec.y = 2;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 400;
	level->block[1].image.area.y = 300;
	level->block[1].image.area.x2 = 528;
	level->block[1].image.area.y2 = 332;
	level->block[1].vec.x = 0;
	level->block[1].vec.y = 2;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 0;
	level->block[2].vec.y = 2;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);

	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);

	level->block[7].image.area.x = WIDTH - 153;
	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);

	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel02(S_level *level){
	level->text = "Level 02";
	
	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 9;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 300;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 332;
	level->block[0].vec.x = 2;
	level->block[0].vec.y = 2;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 400;
	level->block[1].image.area.y = 300;
	level->block[1].image.area.x2 = 528;
	level->block[1].image.area.y2 = 332;
	level->block[1].vec.x = 0;
	level->block[1].vec.y = 2;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 0;
	level->block[2].vec.y = 2;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);

	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);

	level->block[7].image.area.x = WIDTH - 153;
	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);

	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel03(S_level *level){
	level->text = "Level 03";

	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 9;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 300;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 332;
	level->block[0].vec.x = 0;
	level->block[0].vec.y = 2;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 400;
	level->block[1].image.area.y = 100;
	level->block[1].image.area.x2 = 528;
	level->block[1].image.area.y2 = 132;
	level->block[1].vec.x = 2;
	level->block[1].vec.y = 0;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 0;
	level->block[2].vec.y = 2;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);

	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);
	level->block[7].image.area.x = WIDTH - 153;

	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);

	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel04(S_level *level){
	level->text = "Level 04";
	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 9;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 300;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 332;
	level->block[0].vec.x = 2;
	level->block[0].vec.y = 2;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 400;
	level->block[1].image.area.y = 300;
	level->block[1].image.area.x2 = 528;
	level->block[1].image.area.y2 = 332;
	level->block[1].vec.x = -2;
	level->block[1].vec.y = 2;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 4;
	level->block[2].vec.y = 2;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);

	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);

	level->block[7].image.area.x = WIDTH - 153;
	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel05(S_level *level){
	level->text = "Level 05";
	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 9;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 300;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 332;
	level->block[0].vec.x = 0;
	level->block[0].vec.y = 2;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 400;
	level->block[1].image.area.y = 300;
	level->block[1].image.area.x2 = 528;
	level->block[1].image.area.y2 = 332;
	level->block[1].vec.x = 2;
	level->block[1].vec.y = 0;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 2;
	level->block[2].vec.y = 0;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);
	
	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);

	level->block[7].image.area.x = WIDTH - 153;
	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);

	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel06(S_level *level){
	level->text = "Level 06";
	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 9;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 300;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 332;
	level->block[0].vec.x = 2;
	level->block[0].vec.y = 2;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 400;
	level->block[1].image.area.y = 300;
	level->block[1].image.area.x2 = 528;
	level->block[1].image.area.y2 = 332;
	level->block[1].vec.x = 2;
	level->block[1].vec.y = 1;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 2;
	level->block[2].vec.y = 3;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);

	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);

	level->block[7].image.area.x = WIDTH - 153;
	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);

	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel07(S_level *level){
	level->text = "Level 07";
	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 9;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 300;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 332;
	level->block[0].vec.x = 0;
	level->block[0].vec.y = 2;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 400;
	level->block[1].image.area.y = 300;
	level->block[1].image.area.x2 = 528;
	level->block[1].image.area.y2 = 332;
	level->block[1].vec.x = 0;
	level->block[1].vec.y = 0;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 2;
	level->block[2].vec.y = 0;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);

	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);

	level->block[7].image.area.x = WIDTH - 153;
	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);

	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel08(S_level *level){
	level->text = "Level 08";
	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 9;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 100;
	level->block[0].image.area.y = 300;
	level->block[0].image.area.x2 = 228;
	level->block[0].image.area.y2 = 332;
	level->block[0].vec.x = 4;
	level->block[0].vec.y = 0;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 400;
	level->block[1].image.area.y = 300;
	level->block[1].image.area.x2 = 528;
	level->block[1].image.area.y2 = 332;
	level->block[1].vec.x = 4;
	level->block[1].vec.y = 3;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 2;
	level->block[2].vec.y = 3;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);

	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);

	level->block[7].image.area.x = WIDTH - 153;
	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);

	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

void initLevel09(S_level *level){
	level->text = "Level 08";
	level->blumpy.image.area.x=40; 
	level->blumpy.image.area.y=300;
	level->blumpy.image.area.x2 = 72;
	level->blumpy.image.area.y2 = 332;
	level->blumpy.vec.x = 0;
	level->blumpy.vec.y = 6;
	level->blumpy.isjumping = 0;
	level->blumpy.image.still = loadTexture(BLUMPY_STILL);
	level->blumpy.image.left = loadTexture(BLUMPY_LEFT);
	level->blumpy.image.right = loadTexture(BLUMPY_RIGHT);
	level->blumpy.image.dead = loadTexture(BLUMPY_DEAD);
	level->blumpy.image.mask = loadTexture(BLUMPY_MASK);
	level->blumpy.image.texture =level->blumpy.image.still;

	level->exit.area.x = 952;
	level->exit.area.x2 = 984;
	level->exit.area.y = 350;
	level->exit.area.y2 = 382;
	level->exit.texture = loadTexture(EXIT_PATH);

	level->paused.area.x = 256;
	level->paused.area.x2 = 768;
	level->paused.area.y = 128;
	level->paused.area.y2 = 384;
	level->paused.texture = loadTexture(PAUSE_PATH);

	level->numBlocks = 10;
	level->block = malloc(sizeof(S_block) *  level->numBlocks);

	level->block[0].image.area.x = 256;
	level->block[0].image.area.y = 100;
	level->block[0].image.area.x2 = 386;
	level->block[0].image.area.y2 = 132;
	level->block[0].vec.x = 0;
	level->block[0].vec.y = 2;
	level->block[0].donttouch = 0;
	level->block[0].image.texture = loadTexture(BLOCK_PATH);

	level->block[1].image.area.x = 256;
	level->block[1].image.area.y = 400;
	level->block[1].image.area.x2 = 386;
	level->block[1].image.area.y2 = 432;
	level->block[1].vec.x = 0;
	level->block[1].vec.y = -2;
	level->block[1].donttouch = 0;
	level->block[1].image.texture = loadTexture(BLOCK_PATH);
	
	level->block[2].image.area.x = 630;
	level->block[2].image.area.y = 100;
	level->block[2].image.area.x2 = 758;
	level->block[2].image.area.y2 = 132;
	level->block[2].vec.x = 2;
	level->block[2].vec.y = 0;
	level->block[2].donttouch = 0;
	level->block[2].image.texture = loadTexture(BLOCK_PATH);

	level->block[9].image.area.x = 386;
	level->block[9].image.area.y = 100;
	level->block[9].image.area.x2 = 514;
	level->block[9].image.area.y2 = 132;
	level->block[9].vec.x = 0;
	level->block[9].vec.y = 0;
	level->block[9].donttouch = 0;
	level->block[9].image.texture = loadTexture(BLOCK_PATH);

	level->block[3].image.area.x = 0;
	level->block[3].image.area.y = HEIGHT - 85;
	level->block[3].image.area.x2 = 256;
	level->block[3].image.area.y2 = HEIGHT - 53;
	level->block[3].vec.x = 0;
	level->block[3].vec.y = 0;
	level->block[3].donttouch = 0;
	level->block[3].image.texture = loadTexture(WALL_BOTTOM);

	level->block[4].image.area.x = 0;
	level->block[4].image.area.y = 0;
	level->block[4].image.area.x2 = WIDTH;
	level->block[4].image.area.y2 = 4;
	level->block[4].vec.x = 0;
	level->block[4].vec.y = 0;
	level->block[4].donttouch = 0;
	level->block[4].image.texture = loadTexture(WALL_TOP);

	level->block[5].image.area.x = 0;
	level->block[5].image.area.y = 4;
	level->block[5].image.area.x2 = 4;
	level->block[5].image.area.y2 = HEIGHT - 85;
	level->block[5].vec.x = 0;
	level->block[5].vec.y = 0;
	level->block[5].donttouch = 0;
	level->block[5].image.texture = loadTexture(WALL_LEFT);

	level->block[6].image.area.x = WIDTH - 4;
	level->block[6].image.area.y = 4;
	level->block[6].image.area.x2 = WIDTH;
	level->block[6].image.area.y2 = HEIGHT;
	level->block[6].vec.x = 0;
	level->block[6].vec.y = 0;
	level->block[6].donttouch = 0;
	level->block[6].image.texture = loadTexture(WALL_RIGHT);

	level->block[7].image.area.x = WIDTH - 153;
	level->block[7].image.area.y = 382;
	level->block[7].image.area.x2 = WIDTH - 25;
	level->block[7].image.area.y2 = 414;
	level->block[7].vec.x = 0;
	level->block[7].vec.y = 0;
	level->block[7].donttouch = 0;
	level->block[7].image.texture = loadTexture(BLOCK_PATH);

	level->block[8].image.area.x = 256;
	level->block[8].image.area.y = HEIGHT - 32;
	level->block[8].image.area.x2 = WIDTH - 32;
	level->block[8].image.area.y2 = HEIGHT;
	level->block[8].vec.x = 0;
	level->block[8].vec.y = 0;
	level->block[8].donttouch = 1;
	level->block[8].image.texture = loadTexture(WALL_WATER);

	level->back.area.x = 0;
	level->back.area.y = 0;
	level->back.area.x2 = WIDTH;
	level->back.area.y2 = HEIGHT;
	level->back.texture = loadTexture(BACK_PATH);
	return;
}

