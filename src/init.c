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
#include "load_level.h"

#define MENU_PATH "images/menu/menu.png"
#define SELECT_PATH "images/menu/selection.png"

void initLevel(S_level *level, int choice){
	char level_select[30];
	sprintf(level_select,"src/level_set_1/level_%d.cfg",choice);
	load_level_config(level,level_select);
	return;
}

void initMenu(S_menu *menu) {
	menu->image.area.x = 0;
	menu->image.area.y = 0;
	menu->image.area.x2 = WIDTH;
	menu->image.area.y2 = HEIGHT;
	menu->image.texture = loadTexture(MENU_PATH);

	menu->selection = 1;
	menu->imagesel.area.x = 24;
	menu->imagesel.area.x2 = 280;
	menu->imagesel.area.y = 310;
	menu->imagesel.area.y2 = 326;
	menu->imagesel.texture = loadTexture(SELECT_PATH);
	return;
}

int initGame (S_data *game) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	game->screen = SDL_SetVideoMode(WIDTH,HEIGHT,DEPTH, SDL_OPENGL|SDL_GL_DOUBLEBUFFER);
	if (!game->screen) {
		printf("Error Loading\n");
		return 1;
	}
	setupOpengl();
	return 0;
}
