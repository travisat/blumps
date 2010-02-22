/*************************************************************************
 *  Copywrite (C) 2010 by Travis Thompson                                 *
 *	travisat@gmail.com                                                    *
 *																	      *
 *	This program is free software; you can redistribute it and/or modify  *
 *	it under the terms of the GNU General Public License as published by  *
 *	the Free Software Foundation; either version 2 of the License, or     *
 *	(at your option) any later version.                                   *
 *	                                                                      *
 *	This program is distributed in the hope that it will be useful,       *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *	GNU General Public License for more details.                          *
 *	                                                                      *
 *	You should have received a copy of the GNU General Public License     *
 *	along with this program; if not, write to the                         *
 *	Free Software Foundation, Inc.,                                       *
 *	51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 **************************************************************************/

#include "blumps.h"
#include "game.h"
#include "menu.h"
#include "init.h"

void mainLoop(S_data *game, int level) {
	if (initGame(game)) 
		return;
	initMenu(&(game->menu));
	int i;
	while (1) {
		if (menuLoop(&(game->menu)))
			return;
		for (i=level;i < NUMBER_LEVELS;i++){
			initLevel(&(game->level), i);
			if (gameLoop(&(game->level))){
				clearLevel(&(game->level));
				break;
			}
			clearLevel(&(game->level));
		}
	}
	return;
}

int main(int argc, char *argv[]){
	S_data game;
	int level = 0;
	if (argc > 1) {
		level = atoi(argv[1]);
		if (level < 0 || level > NUMBER_LEVELS)
			return 1;
	}

	mainLoop(&game, level);
	SDL_Quit();
	return 0;
}
