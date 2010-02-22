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


int spriteCollisionx2(S_blumpy *blumpy, S_block *block) {
	if ((blumpy->image.area.x2 > block->image.area.x) 
			&& (blumpy->image.area.y2 > block->image.area.y) 
			&& (blumpy->image.area.x < block->image.area.x2) 
			&& (blumpy->image.area.y < block->image.area.y2)){
		if (blumpy->image.area.x2 - blumpy->vec.x <= block->image.area.x - block->vec.x )
			return 1;
	}
	return 0;
}

int spriteCollisionx(S_blumpy *blumpy, S_block *block) {
	if ((blumpy->image.area.x2 > block->image.area.x) 
			&& (blumpy->image.area.y2 > block->image.area.y) 
			&& (blumpy->image.area.x < block->image.area.x2) 
			&& (blumpy->image.area.y < block->image.area.y2)){
		if (blumpy->image.area.x - blumpy->vec.x >= block->image.area.x2 - block->vec.x)
			return 1;
	}
	return 0;
}

int spriteCollisiony(S_blumpy *blumpy, S_block *block) {
	if ((blumpy->image.area.x2 > block->image.area.x) 
			&& (blumpy->image.area.y2 > block->image.area.y) 
			&& (blumpy->image.area.x < block->image.area.x2) 
			&& (blumpy->image.area.y < block->image.area.y2)){
		if (blumpy->image.area.y - blumpy->vec.y >= block->image.area.y2 - block->vec.y)
			return 1;
	}
	return 0;
}

int spriteCollisiony2(S_blumpy *blumpy, S_block *block) {
	if ((blumpy->image.area.x2 > block->image.area.x) 
			&& (blumpy->image.area.y2 > block->image.area.y) 
			&& (blumpy->image.area.x < block->image.area.x2) 
			&& (blumpy->image.area.y < block->image.area.y2)){
		if (blumpy->image.area.y2 - blumpy->vec.y <= block->image.area.y - block->vec.y)
			return 1;	}
	return 0;
}

int spriteCollision(S_level *level){
	int i,j;
	for (i=0;i<level->numBlocks;i++){
		if (spriteCollisionx(&(level->blumpy),&(level->block[i]))){
			level->blumpy.image.area.x2 = level->block[i].image.area.x2 + 32;
			level->blumpy.image.area.x = level->block[i].image.area.x2;
			level->blumpy.vec.x = 0;
			if (level->block[i].donttouch)
				return 1;
			for (j=0;j < level->numBlocks;j++){
				if (spriteCollisionx2(&(level->blumpy),&(level->block[j])))
					return 1;
			}
			level->blumpy.vec.x *= -1;
		}
		if (spriteCollisionx2(&(level->blumpy),&(level->block[i]))){
			level->blumpy.image.area.x = level->block[i].image.area.x - 32;
			level->blumpy.image.area.x2 = level->block[i].image.area.x;
			level->blumpy.vec.x *= -1;
			if (level->block[i].donttouch)
				return 1;
			for (j=0;j < level->numBlocks;j++){
				if (spriteCollisionx(&(level->blumpy),&(level->block[j])))
					return 1;
			}
		}
		if (spriteCollisiony(&(level->blumpy),&(level->block[i]))){
			level->blumpy.image.area.y2 = level->block[i].image.area.y2 + 32;
			level->blumpy.image.area.y = level->block[i].image.area.y2;
			level->blumpy.vec.y = level->block[i].vec.y;
			if (level->block[i].donttouch)
				return 1;
			for (j=0;j < level->numBlocks;j++){
				if (spriteCollisiony2(&(level->blumpy),&(level->block[j])))
					return 1;
			}
		}
		if (spriteCollisiony2(&(level->blumpy),&(level->block[i]))){
			level->blumpy.image.area.y = level->block[i].image.area.y - 32 ;
			level->blumpy.image.area.y2 = level->block[i].image.area.y ;
			level->blumpy.vec.y = level->block[i].vec.y;
			if (level->block[i].donttouch)
				return 1;
			for (j=0;j < level->numBlocks;j++){
				if (spriteCollisiony(&(level->blumpy),&(level->block[j])))
					return 1;
			}
			level->blumpy.isjumping = 0;
			level->blumpy.image.area.x += level->block[i].vec.x;
			level->blumpy.image.area.x2 += level->block[i].vec.x;
		}
	}
	return 0;
}

int finishLevel(S_blumpy *blumpy, S_image *exit){
	if ((blumpy->image.area.x < exit->area.x2)
			&& (blumpy->image.area.x2 > exit->area.x)
			&& (blumpy->image.area.y < exit->area.y2)
			&& (blumpy->image.area.y2 > exit->area.y))
		return 1;
	return 0;
}

void blockCollision(S_block *one, S_block *two){
	if ((one->image.area.x < two->image.area.x2) 
			&& (one->image.area.x2 > two->image.area.x) 
			&& (one->image.area.y < two->image.area.y2) 
			&& (one->image.area.y2 > two->image.area.y)) {
		if (one->image.area.x2 - one->vec.x <= two->image.area.x - two->vec.x
				|| one->image.area.x - one->vec.x >= two->image.area.x2 - two->vec.x){
			one->vec.x *= -1;
			two->vec.x *= -1;
		} else if (one->image.area.y2 - one->vec.y <= two->image.area.y - two->vec.y 
				|| one->image.area.y - one->vec.y >= two->image.area.y2 - two->vec.y){
			one->vec.y *= -1;
			two->vec.y *= -1;
		}
	}
}
