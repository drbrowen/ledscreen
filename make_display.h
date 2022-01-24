#ifndef MAKE_DISPLAY_INCLUDE
#define MAKE_DISPLAY_INCLUDE

#include "ws2811.h"
#include "gifloader.h"

typedef struct {
  GIFLOADER *gfl;
  GifColorType **sprites;
  int phase;
  int SpriteW;
  int SpriteH;
} MAKEDISPLAY;

MAKEDISPLAY *initialize_display();
int make_display(MAKEDISPLAY *dis,ws2811_led_t MATRIX[][15]);
void close_display(MAKEDISPLAY *dis);
void _put_sprite(MAKEDISPLAY *dis,ws2811_led_t MATRIX[][15],GifColorType *sprite,int x, int y);

#endif // MAKE_DISPLAY_INCLUDE
