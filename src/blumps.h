 /***************************************************************************
  *   Copyright (C) 2010 by Travis Thompson                                 *
  *   travisat@gmail.com                                                    *
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

#include "SDL.h"
#include "SDL_opengl.h"

#define WIDTH 1024 
#define HEIGHT 512
#define BPP 4
#define DEPTH 32

#define NUMBER_LEVELS 10
#define FONT "DroidSans.ttf"

typedef struct{
	int x;
	int x2;
	int y;
	int y2;
} S_rectangle;

typedef struct{
	int x;
	int y;
} S_vector;
 
typedef struct{
	S_rectangle area;
	GLuint texture;
	GLuint mask;
	GLuint still;
	GLuint left;
	GLuint right;
	GLuint dead;
} S_image;
 
typedef struct{
	S_image image;
	S_vector vec;
	int isjumping;
} S_blumpy;

typedef struct{
	S_image image;
	S_vector vec;
	int donttouch;
} S_block;

typedef struct{
	S_blumpy blumpy;
	S_image exit;
	int numBlocks;
	S_image back;
	S_image paused;
	const char *text;
	S_block *block;
} S_level;

typedef struct{
	S_image imagesel;
	int selection;
	S_image image;
} S_menu;

typedef struct{
	S_level level;
	S_menu menu;
	SDL_Surface *screen;
} S_data;

