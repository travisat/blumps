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
#include "FTGL/ftgl.h"
#include "SDL_image.h"

//setupOpengl : call once before attempting to draw any opengl on screen
void setupOpengl() {
	glClearColor(0,0,0,0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glViewport(0,0,WIDTH,HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLuint loadTexture(char* path){
	GLuint texture;
	GLenum texture_format;
	GLint nOfColors;
	SDL_Surface *surface = IMG_Load(path);
	if (!surface) {
		printf("Unable to Load: %s\n", path);
		exit(1);
	}
	if ((surface->w & (surface->w - 1)) != 0 ) {
		printf("warning: width  of %s isn't power of 2\n",path);
	}
	if ((surface->h & (surface->h - 1)) != 0 ) {
		printf("warning: height of %s isn't power of 2\n", path);
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

	SDL_FreeSurface(surface);
	return texture;
}

//drawTexture: draws S_image on screen, must call SDL_GL_SwapBuffers() after call to update screen
//input: S_image *image: pointer to a S_image
//output void
void drawTexture(S_image *image){
	//bind texture to a 2d gl texture so we can work with it
	glBindTexture( GL_TEXTURE_2D,image->texture );
	//being gl routines
	glBegin( GL_QUADS);
		//top left corner
		glTexCoord2i(0,0);
		glVertex3f(image->area.x,image->area.y, 0);
		//top right corner
		glTexCoord2i(1,0);
		glVertex3f(image->area.x2,image->area.y,0);
		//bottom right corner
		glTexCoord2i(1,1);
		glVertex3f(image->area.x2,image->area.y2,0);
		//bottom left corner
		glTexCoord2i(0,1);
		glVertex3f(image->area.x,image->area.y2,0);
	glEnd();
}
void drawMask(S_image *image){
	//bind texture to a 2d gl texture so we can work with it
	glBindTexture( GL_TEXTURE_2D,image->mask );
	//being gl routines
	glBegin( GL_QUADS);
		//top left corner
		glTexCoord2i(0,0);
		glVertex3f(image->area.x,image->area.y, 0);
		//top right corner
		glTexCoord2i(1,0);
		glVertex3f(image->area.x2,image->area.y,0);
		//bottom right corner
		glTexCoord2i(1,1);
		glVertex3f(image->area.x2,image->area.y2,0);
		//bottom left corner
		glTexCoord2i(0,1);
		glVertex3f(image->area.x,image->area.y2,0);
	glEnd();
}
//drawText: draws text on screen, must call SDL_GL_SwapBuffers() after call to update screen
//input:string text = text to display
//input:int x = x position of text
//input:int y = y position of text
//input:int pixelsize = size of text
//output void: note need to add error checking
void drawText(char *text, int x, int y, int pixelsize){
	// load font into ftgl font type, currently we use a hardset FONT defined in blumps.h
	FTGLfont *font = ftglCreatePixmapFont(FONT);
	if (!font)
		printf("font load error\n");
	//set font size 0 on end signifies use default resolution
	ftglSetFontFaceSize(font, pixelsize, 0);
	//set gl position to draw font at
	glRasterPos2f(x, y);
	//set color black for text, might want to creat a font type that include text, position, size, and color
	glPixelTransferf(GL_RED_BIAS, -1);
	glPixelTransferf(GL_GREEN_BIAS, -1);
	glPixelTransferf(GL_BLUE_BIAS, -1);
	//draw font onto buffer
	ftglRenderFont(font, text, FTGL_RENDER_ALL);
	//return color back to normal so other stuff will draw correctly
	glPixelTransferf(GL_RED_BIAS, 0);
	glPixelTransferf(GL_GREEN_BIAS, 0);
	glPixelTransferf(GL_BLUE_BIAS, 0);
	//clear ftgl font to avoid memory leaks
	ftglDestroyFont(font);
	return;
}

void drawMenu(S_menu *menu) {
	drawTexture(&(menu->image));
	drawTexture(&(menu->imagesel));
	SDL_GL_SwapBuffers();
}

void drawPause(S_level *level, int selection){
	drawTexture(&(level->paused));
	drawText("Paused", 431, 240, 50);
	if (selection == 1 || selection == 0){
		drawText("Continue",451,290,30);
		drawText("Exit", 503,320, 10);
	} else if (selection == 2) {
		drawText("Exit", 487, 290, 30);
		drawText("Continue", 492, 320, 10);
	}
	SDL_GL_SwapBuffers();
}

void drawScreen(S_level* level){ 
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	drawTexture(&(level->back));
	drawTexture(&(level->exit));
	for (i=0;i<level->numBlocks;i++){
		drawTexture(&(level->block[i].image));	
	}
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_DST_COLOR, GL_ZERO);
	//drawMask(&(level->blumpy.image));	
	//glBlendFunc(GL_ONE, GL_ONE);
	drawTexture(&(level->blumpy.image));
	//glDisable(GL_BLEND);
	SDL_GL_SwapBuffers();
}
