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
#include "pause.h"

int keyPress(S_level *level, SDL_Event *event, Uint8 *keystate) {
	SDL_PollEvent(event);
	if (event->type == SDL_QUIT) return 1;
	
	SDL_PumpEvents();
	if (keystate[SDLK_LEFT]) {
		level->blumpy.vec.x -= 2 ;
		if (level->blumpy.vec.x < -6)
			level->blumpy.vec.x = -6;
	}
	if (!keystate[SDLK_LEFT]) {
		if (level->blumpy.vec.x < 0)
			level->blumpy.vec.x++;
	}
	if (keystate[SDLK_RIGHT]) {
		level->blumpy.vec.x += 4;
		if (level->blumpy.vec.x > 6)
			level->blumpy.vec.x = 6;
	}
	if (!keystate[SDLK_RIGHT]) {
		if (level->blumpy.vec.x > 0)
			level->blumpy.vec.x--;
	}
	if (keystate[SDLK_UP]) {
		if (!level->blumpy.isjumping) {
			level->blumpy.vec.y =  -16;
			level->blumpy.isjumping = 1;
		}
	}
	if (keystate[SDLK_p] || keystate[SDLK_PAUSE] || keystate[SDLK_ESCAPE]) {
		if (pauseGame(level))
			return 1;
	}
	 
	return 0;
}
