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

int pauseGame(S_level *level) {
	SDL_Event event;
	int action = 0;
	int selection = 1;
	while (1) {
		drawPause(level, selection);
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_UP) {
					selection--;
					if (selection < 1)
						selection = 2;
				}
				if (event.key.keysym.sym == SDLK_DOWN){
					selection++;
					if (selection > 2)
						selection = 1;
				}
				if (event.key.keysym.sym == SDLK_RETURN) {
					action = selection;
				}
				break;
			case SDL_QUIT:
				return 1;
		}
		if (action == 1)
			return 0;
		if (action == 2)
			return 1;
	}
	return 0;
}
