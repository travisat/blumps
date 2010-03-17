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

#include <libconfig.h>
#include "blumps.h"
#include "draw.h"


void load_blumpy(config_t *config, S_blumpy *blumpy)
{
	blumpy->image.still = loadTexture(config_setting_get_string(config_lookup(config,"level.blumpy.image.still")));
	blumpy->image.left = loadTexture(config_setting_get_string(config_lookup(config,"level.blumpy.image.left")));
	blumpy->image.right = loadTexture(config_setting_get_string(config_lookup(config,"level.blumpy.image.right")));
	blumpy->image.dead = loadTexture(config_setting_get_string(config_lookup(config,"level.blumpy.image.dead")));
	blumpy->image.mask = loadTexture(config_setting_get_string(config_lookup(config,"level.blumpy.image.mask")));
	blumpy->image.texture = blumpy->image.still;

	config_setting_t *area = config_lookup(config,"level.blumpy.image.area");
	blumpy->image.area.x = config_setting_get_int_elem(area,0);
	blumpy->image.area.y = config_setting_get_int_elem(area,1);
	blumpy->image.area.x2 = config_setting_get_int_elem(area,2);
	blumpy->image.area.y2 = config_setting_get_int_elem(area,3);

	config_setting_t *vec = config_lookup(config,"level.blumpy.vec");
	blumpy->vec.x = config_setting_get_int_elem(vec,0);
	blumpy->vec.y = config_setting_get_int_elem(vec,1);

	blumpy->isjumping = config_setting_get_int(config_lookup(config,"level.blumpy.isjumping"));
}

void load_image(config_setting_t *config, S_image *image)
{
	image->texture = loadTexture(config_setting_get_string(config_setting_get_member(config,"image")));

	config_setting_t *area = config_setting_get_member(config,"area");
	image->area.x = config_setting_get_int_elem(area,0);
	image->area.y = config_setting_get_int_elem(area,1);
	image->area.x2 = config_setting_get_int_elem(area,2);
	image->area.y2 = config_setting_get_int_elem(area,3);
}

void load_block(config_setting_t *config, S_block *block)
{
	load_image(config,&(block->image));
	printf("area: %d %d %d %d\n",block->image.area.x, block->image.area.y, block->image.area.x2, block->image.area.y2);
	config_setting_t *vec = config_setting_get_member(config,"vec");
	block->vec.x = config_setting_get_int_elem(vec,0);
	block->vec.y = config_setting_get_int_elem(vec,1);

	block->donttouch = config_setting_get_int(config_setting_get_member(config,"donttouch"));

}

void load_blocks(config_setting_t *blocks,int numBlocks,S_level *level)
{
	int i;
	for (i=0;i<numBlocks;i++){
		load_block(config_setting_get_elem(blocks,i),&(level->block[i]));
		printf("loaded block %d\n",i+1);
	}
}

void load_level_config(S_level *level, const char *choice)
{
	struct config_t config;
	config_init(&config);
	if (!config_read_file(&config,choice))
		printf("error in %s\n",choice);
	level->text = config_setting_get_string(config_lookup(&config,"level.text"));

	load_blumpy(&config,&(level->blumpy));
	load_image(config_lookup(&config,"level.exit"),&(level->exit));
	load_image(config_lookup(&config,"level.paused"),&(level->paused));
	load_image(config_lookup(&config,"level.back"),&(level->back));
	
	config_setting_t *blocks = config_lookup(&config,"level.blocks");
	level->numBlocks = config_setting_length(blocks);
	level->block = malloc(sizeof(S_block) * level->numBlocks);
	load_blocks(blocks,level->numBlocks,level);
}
