#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"

#include "ws2811.h"
#include "make_display.h"

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define XSIZE 15
#define YSIZE 60 // MUST BE EVEN or SEGFAULT
#define LED_COUNT (XSIZE * YSIZE)

static int running = 1;

ws2811_t ledstring =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = GPIO_PIN,
            .count = LED_COUNT,
            .invert = 0,
            .brightness = 255,
            .strip_type = STRIP_TYPE,
        },
        [1] =
        {
            .gpionum = 0,
            .count = 0,
            .invert = 0,
            .brightness = 0,
        },
    },
};

ws2811_led_t buffer[LED_COUNT];

ws2811_led_t matrix[YSIZE][XSIZE];

static void ctrl_c_handler(int signum)
{
  (void)(signum);
  running = 0;
}

static void setup_handlers(void)
{
  struct sigaction sa =
    {
     .sa_handler = ctrl_c_handler,
    };

  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);
}

void clear_buffer() {
  int j;
  for(j=0;j<YSIZE;j++) {
    memset(matrix[j],0,XSIZE*sizeof(ws2811_led_t));
  }
}

int push_matrix() {
  int i,j;
  ws2811_return_t ret;
  
  for (j=0;j<YSIZE;j+=2) {
    for(i=0;i<XSIZE;i++) {
      buffer[(XSIZE*j)+i] = matrix[j][i];
      buffer[(XSIZE*(j+1)) + i] = matrix[j][XSIZE-i];
    }
  }

  if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS) {
    fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
    return 1;
  }

  return 0;

}


int main(int argc,char* argv[])
{
  ws2811_return_t ret;
  error = 0;

  setup_handlers();

  if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
    fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
    return ret;
  }

  while(running == 1) {
    make_display(matrix,XSIZE,YSIZE);
    if(push_matrix()) {
      running=0;
      error = 1;
    }
  }

  clear_buffer();
  push_matrix();

  return error;
}
