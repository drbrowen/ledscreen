// PNG Code shamefully stolen.  Here's the original code...

/*
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>
#include <errno.h>
#include "gifloader.h"
#include "make_display.h"


MAKEDISPLAY *initialize_display()
{
  MAKEDISPLAY *ret;
  int i,j,c;
  
  if(!(ret=malloc(sizeof(MAKEDISPLAY)))) {
    perror("Allocate Display");
    return NULL;
  }

  ret->SpriteW = 16;
  ret->SpriteH = 16;

  if(!(ret->gfl = gifloader_open("spritecloseupsingle.gif",ret->SpriteW,ret->SpriteH))) {
    printf("Can't open gif\n");
    free(ret);
    return NULL;
  }
			  
  if(!(ret->sprites = malloc(sizeof(GifColorType*)*8*4))) {
    perror("Allocate sprite memory");
    gifloader_close(ret->gfl);
    free(ret);
    return NULL;
  }

  c=0;
  for(j=2;j<6;j++) {
    for(i=0;i<8;i++) {
      if(!(ret->sprites[c++] = gifloader_fetch_sprite(ret->gfl,i,j))) {
	fprintf(stderr,"Got a NULL sprite!\n");
	free(ret->sprites);
	gifloader_close(ret->gfl);
	free(ret);
	return NULL;
      }
    }
  }

  ret->phase = 0;

  return ret;  
  
}

int make_display(MAKEDISPLAY *dis,ws2811_led_t MATRIX[][15])
{
  int i,j,jone,jcoord,jonecoord,coord,mirrorcoord;
  int basepos,phase;
  
  GifColorType *sprite;

  //sprite=dis->sprites[(dis->phase++)>>2];

  phase = dis->phase++;
  if (dis->phase >= 92) {
    dis->phase = 0;
  }

  if(phase<36) {
    sprite = dis->sprites[(phase)&1];
    _put_sprite(dis,MATRIX,sprite,0,36 - phase);
  } else if(phase<38) {
    sprite = dis->sprites[6+((phase)&1)];
    _put_sprite(dis,MATRIX,sprite,0,0);
  } else if(phase<54) {
    sprite = dis->sprites[6+((phase)&1)];
    _put_sprite(dis,MATRIX,sprite,phase-38,0);
  } else if(phase<70) {
    sprite = dis->sprites[14 +((phase)&1)];
    _put_sprite(dis,MATRIX,sprite,phase-54-16,0);
  } else if(phase<72) {
    sprite = dis->sprites[10 + ((phase)&1)];
    _put_sprite(dis,MATRIX,sprite,0,0);
  } else if(phase<92) {
    sprite = dis->sprites[10 + ((phase)&1)];
    _put_sprite(dis,MATRIX,sprite,0,phase-72);
  } 


		
  /*
  for(j=0;j<20;j++) {
    {
      for(i=0;i<15;i++) {
	MATRIX[j][i] =
	  sprite[dis->SpriteW*j + i].Red +
	  sprite[dis->SpriteW*j + i].Green*0x100 +
	  sprite[dis->SpriteW*j + i].Blue*0x10000;
      }
    }
  }
  */
  return 0;
	
}

void _put_sprite(MAKEDISPLAY *dis,ws2811_led_t MATRIX[][15],GifColorType *sprite,int x, int y)
{
  int i,j,transx,transy;

  for(j=0;j<dis->SpriteH;j++)
    {
      transy = j+y;
      if(transy>=0 && transy<60) {
	for(i=0;i<dis->SpriteW;i++)
	  {
	    transx = i+x;
	    if(transx>=0 && transx < 15)
	      {
		MATRIX[transy][transx] =
		  sprite[dis->SpriteW*j + i].Red +
		  sprite[dis->SpriteW*j + i].Green*0x100 +
		  sprite[dis->SpriteW*j + i].Blue*0x10000;
	      }
	  }
      }
    }      
}
    
void close_display(MAKEDISPLAY *dis)
{
  gifloader_close(dis->gfl);
  free(dis->sprites);
  free(dis);
}
