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
#include "keypress.h"

void drawDeath(S_level *level, GLfloat roll) {
	glRotatef(roll * 360, 0, 1, 0);
	drawScreen(level);
	SDL_GL_SwapBuffers();
}

void deathLoop(S_level *level) {
	GLfloat roll = 0;
	SDL_Event event;
	while (1) {
		drawDeath(level, roll);
		drawText("You Died", 100,200,100);
		SDL_GL_SwapBuffers();
		roll += .01;
		if (roll > 1)
			roll = 1;
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_ESCAPE){
						return;
				}
				break;
			case SDL_QUIT:
				SDL_Quit();
				exit(1);
		}
	}
}
