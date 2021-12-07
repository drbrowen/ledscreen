#include <stdio.h>
#include <errno.h>

#include "gifloader.h"

int main(int argc,char* argv[])
{
  int i;
  int j;
  GIFLOADER *gfl;

  GifColorType *colors;

  if(!(gfl = gifloader_open("spritecloseupsingle.gif",16,16))) {
    perror("Can't open gif");
    return 1;
  }

  if(!(colors = gifloader_fetch_sprite(gfl,0,4))) {
    fprintf(stderr,"gifloader can't fetch colors.\n");
    return 1;
  }

  printf("Here's sprite 0\n\n");
  
  for(j=0;j<16;j++) {
    for(i=0;i<16;i++) {
      printf("0x%02x%02x%02x ",
	     colors[16*j+i].Red,
	     colors[16*j+i].Green,
	     colors[16*j+i].Blue);
    }
    printf("\n");
  }

  gifloader_free_sprite(colors);

  if(!(colors = gifloader_fetch_sprite(gfl,1,4))) {
    fprintf(stderr,"gifloader can't fetch colors.\n");
    return 1;
  }

  printf("\nHere's sprite 1\n\n");

  for(j=0;j<16;j++) {
    for(i=0;i<16;i++) {
      printf("0x%02x%02x%02x ",
	     colors[16*j+i].Red,
	     colors[16*j+i].Green,
	     colors[16*j+i].Blue);
    }
    printf("\n");
  }

  gifloader_free_sprite(colors);  

}
