#include <stdio.h>
#include <stdlib.h>
#include <gif_lib.h>

#define SPRITEHEIGHT 16
#define SPRITEWIDTH  16

int gifinit

int main(int argc,char* argv[])
{
  GifColorType rgb;
  int i,j;
  int error;
  int xpos,ypos,red,green,blue;
  int cindex;

  F = DGifOpenFileName("spritecloseupsingle.gif",&error);

  if(!F) {
    fprintf(stderr,"GIF ERROR opening file! %d\n",error);
    exit(1);
  }

  error = DGifSlurp(F);

  if(error != GIF_OK) {
    fprintf(stderr,"GIF ERROR reading file! %d\n",error);
    exit(1);
  }

  printf("Found gif with size (%d x %d)\n",F->SWidth,F->SHeight);
  if(F->SColorMap) {
    printf("Found a colormap\n");
    C = F->SColorMap;
  } else {
    printf("No colormap found\n");
  }

  printf("Found %d images\n",F->ImageCount);

  if(F->ImageCount > 0) {
    S = &(F->SavedImages[0]);
  } else {
    printf("No images found, exiting.\n");
    return 1;
  }

  for(j=0;j<SPRITEHEIGHT;j++) {
    ypos = F->SWidth * (SPRITEHEIGHT*IMAGEY + j);
    for(i=0;i<SPRITEWIDTH;i++) {
      xpos = (SPRITEWIDTH*IMAGEX + i);
      
      cindex = S->RasterBits[xpos + ypos];

      if(cindex == 1) {
	printf("       ");
      } else {
	rgb = C->Colors[S->RasterBits[xpos + ypos]];
	printf("%02x%02x%02x ",rgb.Red,rgb.Blue,rgb.Green);
      }
    }
    putchar('\n');
  }		      
		      
  
  return 0;

}
