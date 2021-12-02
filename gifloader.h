#ifndef GIFLOADER
#define GIFLOADER

struct {
  GifFileType *F;
  SavedImage *S;
  ColorMapObject *C;
  GraphicsControlBlock gcb;
  int SpriteH;
  int SpriteW;
} GIFLOADER;


GIFLOADER *gifloader_open(char* file,int SpriteH,int SpriteW);
long int *gifloader_get_sprite(GIFLOADER g, int x, int y);

#endif // GIFLOADER
