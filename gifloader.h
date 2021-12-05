#ifndef GIFLOADER
#define GIFLOADER

#include <gif_lib.h>

struct {
  GifFileType *F;
  SavedImage *S;
  ColorMapObject *C;
  GraphicsControlBlock gcb;
  int SpriteH;
  int SpriteW;
} GIFLOADER;

GIFLOADER *gifloader_open(char* file,int SpriteH,int SpriteW);
GifColorType *gifloader_fetch_sprite(GIFLOADER *gfl,int SpriteX, int SpriteY);


#endif // GIFLOADER
