#include <stdio.h>
#include <stdlib.h>
#include <gif_lib.h>
#include <malloc.h>
#include "gifloader.h"

GIFLOADER* gifloader_open(char* file,int SpriteH,int SpriteW)
{
  GIFLOADER* ret;

  GifColorType rgb;
  int i,j;
  int error;
  int xpos,ypos,red,green,blue;


  // Allocate the handle for this instance
  if(!(ret=malloc(sizeof(GIFLOADER)))) {
    return NULL;
  }


  // Load the file
  ret->F = DGifOpenFileName(file,&error);

  if(!ret->F) {
    fprintf(stderr,"GIF ERROR opening file! %d\n",error);
    // No memory leaks please
    free(ret);
    return NULL;
  }


  // Read in the file
  error = DGifSlurp(ret->F);

  if(error != GIF_OK) {
    fprintf(stderr,"GIF ERROR reading file! %d\n",error);
    DGifCloseFile(ret->F,&error);
    // No memory leaks.
    free(ret);
    return NULL;
  }


  // Handle sizing.ret->
  printf("Found gif with size (%d x %d)\n",ret->F->SWidth,ret->F->SHeight);
  ret->SpriteH = SpriteH;
  ret->SpriteW = SpriteW;

  printf("Sprites are %dx%d\n",ret->SpriteH,ret->SpriteW);
  
  // Get a custom colormap if present
  if(ret->F->SColorMap) {
    printf("Found a colormap\n");
    ret->C = ret->F->SColorMap;
  } else {
    printf("No colormap found\n");
  }


  // Make sure there are images present
  if(ret->F->ImageCount > 0) {
    ret->S = &(ret->F->SavedImages[0]);
  } else {
    printf("No images found, exiting.\n");
    DGifCloseFile(ret->F,&error);
    free(ret);
    return NULL;
  }

  return ret;

}

GifColorType *gifloader_fetch_sprite(GIFLOADER *gfl,int SpriteX, int SpriteY)
{
  GifColorType *ret;
  int i,j;
  int xindex,yindex;
  int cindex;

  GifColorType black;
  black.Red = 0;
  black.Green = 0;
  black.Blue = 0;
  
  // Make sure we're in bounds.
  if( ( (SpriteX * gfl->SpriteW - 1) > gfl->F->SWidth) ||
      ( (SpriteY * gfl->SpriteH - 1) > gfl->F->SHeight) ) {
    printf("Huh, too big.\n");
    return NULL;
  }
  
  if(!(ret=malloc(sizeof(GifColorType)*(gfl->SpriteH)*(gfl->SpriteW)))) {
    perror("Get gif array");
    return NULL;
  }

  
  for(j=0;j<(gfl->SpriteH);j++) {
    yindex = gfl->F->SWidth * (gfl->SpriteH * SpriteY + j);
    for(i=0;i<(gfl->SpriteW);i++) {
      xindex = (gfl->SpriteW * SpriteX + i);

      cindex = gfl->S->RasterBits[xindex + yindex];

      if(cindex != 1) {
	ret[gfl->SpriteW * j + i] = gfl->C->Colors[cindex];
      } else {
	ret[gfl->SpriteW * j + i] = black;
      }
    }
  }

  return ret;
  
}

// Right now, could just be a call to free(), but may change in the future so do it here.
void gifloader_free_sprite(GifColorType *gct)
{
  free(gct);
}

GIFLOADER *gifloader_close(GIFLOADER *gfl)
{
  int error;
  DGifCloseFile(gfl->F, &error);
  free(gfl);
}
