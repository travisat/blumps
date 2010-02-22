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
#include "font.h"
#include "FTGL/ftgl.h"

void setupOpengl() {
	glClearColor(0,0,0,0);
	glEnable(GL_TEXTURE_2D);
	glViewport(0,0,WIDTH,HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLuint loadTexture(SDL_Surface* surface){
	GLuint texture;
	GLenum texture_format;
	GLint nOfColors;


	if ((surface->w & (surface->w - 1)) != 0 ) {
		printf("warning: width isn't power of 2\n");
	}
	if ((surface->h & (surface->h - 1)) != 0 ) {
		printf("warning: height isn't power of 2\n");
	}

	nOfColors = surface->format->BytesPerPixel;
	if (nOfColors==4){
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} else if (nOfColors == 3){
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	}

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0, texture_format, GL_UNSIGNED_BYTE, surface->pixels );

	return texture;
}

void drawTexture(S_image *image){
	GLuint texture = loadTexture(image->surface);
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS);
		glTexCoord2i(0,0);
		glVertex3f(image->area.x,image->area.y, 0);
		glTexCoord2i(1,0);
		glVertex3f(image->area.x2,image->area.y,0);
		glTexCoord2i(1,1);
		glVertex3f(image->area.x2,image->area.y2,0);
		glTexCoord2i(0,1);
		glVertex3f(image->area.x,image->area.y2,0);
	glEnd();
	glDeleteTextures(1, &texture);
}

void drawText(char *text, int x, int y, int pixelsize){
	FTGLfont *font = ftglCreatePixmapFont(FONT);
	if (!font)
		printf("font load error\n");
	ftglSetFontFaceSize(font, pixelsize, 0);
	glRasterPos2f(x, y);
	glPixelTransferf(GL_RED_BIAS, -1);
	glPixelTransferf(GL_GREEN_BIAS, -1);
	glPixelTransferf(GL_BLUE_BIAS, -1);
	ftglRenderFont(font, text, FTGL_RENDER_ALL);
	glPixelTransferf(GL_RED_BIAS, 0);
	glPixelTransferf(GL_GREEN_BIAS, 0);
	glPixelTransferf(GL_BLUE_BIAS, 0);
	ftglDestroyFont(font);
	return;
}

void drawMenu(S_menu *menu) {
	drawTexture(&(menu->image));
	drawTexture(&(menu->imagesel));
	SDL_GL_SwapBuffers();
}

void drawPause(S_level *level){
	drawTexture(&(level->paused));
	drawText("Paused", 446, 240, 40);
	drawText("Press Enter to Continue",407,290,20);
	SDL_GL_SwapBuffers();
}

void drawScreen(S_level* level){ 
	int i;
	drawTexture(&(level->back));
	drawTexture(&(level->exit));
	for (i=0;i<level->numBlocks;i++){
		drawTexture(&(level->block[i].image));	
	}
	drawTexture(&(level->blumpy.image));
	SDL_GL_SwapBuffers();
}
