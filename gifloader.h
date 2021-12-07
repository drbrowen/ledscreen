#ifndef GIFLOADER_INCLUDE
#define GIFLOADER_INCLUDE

#include <stdlib.h>
#include <gif_lib.h>

typedef struct {
  GifFileType *F;
  SavedImage *S;
  ColorMapObject *C;
  GraphicsControlBlock gcb;
  int SpriteH;
  int SpriteW;
} GIFLOADER;

GIFLOADER *gifloader_open(char* file,int SpriteH,int SpriteW);
GifColorType *gifloader_fetch_sprite(GIFLOADER *gfl,int SpriteX, int SpriteY);
void gifloader_free_sprite(GifColorType *gct);
GIFLOADER *gifloader_close(GIFLOADER *gfl);


#endif // GIFLOADER_INCLUDE
