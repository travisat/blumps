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
#include "collision.h"

void moveBlocks(S_level *level) {
	int i,j;
	
	for (i = 0; i < level->numBlocks; i++){
		if (level->block[i].vec.x){
			level->block[i].image.area.x += level->block[i].vec.x;
			level->block[i].image.area.x2 += level->block[i].vec.x;
		}
		if (level->block[i].vec.y){
			level->block[i].image.area.y += level->block[i].vec.y;
			level->block[i].image.area.y2 += level->block[i].vec.y;
		}
	}
	for (i = 0; i < (level->numBlocks) - 1; i++){
		for (j=i+1;j < level->numBlocks; j++){
			blockCollision(&(level->block[i]),&(level->block[j]));
		}
	}
}

void moveblumpy(S_blumpy *blumpy) {
	blumpy->vec.y++;
	blumpy->image.area.x += blumpy->vec.x;
	blumpy->image.area.x2 += blumpy->vec.x;
	blumpy->image.area.y += blumpy->vec.y;
	blumpy->image.area.y2 += blumpy->vec.y;
	if (!blumpy->vec.y)
		blumpy->isjumping = 1;
	if (blumpy->vec.x > 0) 
		blumpy->image.texture = blumpy->image.right;
	if (blumpy->vec.x < 0)
		blumpy->image.texture = blumpy->image.left;
	if (blumpy->vec.x == 0)
		blumpy->image.texture = blumpy->image.still;
}

int movement(S_level *level){
	moveBlocks(level);
	moveblumpy(&(level->blumpy));
	if (spriteCollision(level)){
		return 1;
	}
	return 0;
}
