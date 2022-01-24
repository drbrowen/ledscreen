This drives an LED strip with WS2812 individually-addressible LEDs.

I used the rpi_ws281x library for the IO.

I added in something to read some gifs and display them on a display made by splicing
LED strips 15 across, back and forth.  The LEDs are numberd as follows:

<pre>
Row 0:  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
Row 1: 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15
Row 2: 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44
Ro2 3: 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45
</pre>
etc.

