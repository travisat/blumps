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
#include <unistd.h>
#include "draw.h"
#include "keypress.h"
#include "movement.h"
#include "collision.h"
#include "init.h"
#include "menu.h"
#include "death.h"

void clearLevel(S_level *level){
	int i;
	for (i=0;i < level->numBlocks; i++){
		glDeleteTextures(1,&(level->block[i].image.texture));
	}
	free(level->block);
	glDeleteTextures(1, &(level->blumpy.image.right));
	glDeleteTextures(1, &(level->blumpy.image.left));
	glDeleteTextures(1, &(level->blumpy.image.still));
	glDeleteTextures(1, &(level->blumpy.image.dead));
	glDeleteTextures(1, &(level->back.texture));
	return;
}

void death(S_level *level){
	level->blumpy.image.texture = level->blumpy.image.dead;
	deathLoop(level);
	return;	
}

int gameLoop(S_level *level){
	drawScreen(level);
	SDL_Event event;
	Uint8 *keystate = SDL_GetKeyState(NULL);
	Uint32 lastFrameTime = 0.0;
	Uint32 currentTime;
	while(1) {
		currentTime = SDL_GetTicks();
		SDL_PollEvent(&event);
		if (keyPress(level,&event,keystate))
			return 1;	
		if (movement(level)){
			death(level);
			return 1;
		}
		if (finishLevel(&(level->blumpy),&(level->exit)))
			return 0;
		while ((currentTime - lastFrameTime) < 16){
			currentTime = SDL_GetTicks();
			sleep(0);
		}
		drawScreen(level);
		sleep(0);
		lastFrameTime = currentTime;
	}
}
