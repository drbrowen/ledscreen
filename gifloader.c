#include <stdio.h>
#include <stdlib.h>
#include <gif_lib.h>
#include <malloc.h>

GIFLOADER* gifloader_open(char* file,int SpriteH,int SpriteW)
{
  GIFLOADER* ret;

  GifColorType rgb;
  int i,j;
  int error;
  int xpos,ypos,red,green,blue;
  int cindex;

  if(!(ret=malloc(sizeof(GIFLOADER)))) {
    return NULL;
  }

  ret->F = DGifOpenFileName(file,&error);

  if(!ret->F) {
    fprintf(stderr,"GIF ERROR opening file! %d\n",error);
    free(ret);
    return NULL;
  }

  error = DGifSlurp(ret->F);

  if(error != GIF_OK) {
    fprintf(stderr,"GIF ERROR reading file! %d\n",error);
    DGifClose(ret->F);
    free(ret);
    return NULL;
  }

  printf("Found gif with size (%d x %d)\n",ret->F->SWidth,ret->F->SHeight);
  if(ret->F->SColorMap) {
    printf("Found a colormap\n");
    ret->C = ret->F->SColorMap;
  } else {
    printf("No colormap found\n");
  }

  printf("Found %d images\n",ret->F->ImageCount);

  if(ret->F->ImageCount > 0) {
    ret->S = &(ret->F->SavedImages[0]);
  } else {
    printf("No images found, exiting.\n");
    return 1;
  }

  return 0;

}
