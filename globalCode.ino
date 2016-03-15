#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Hi Tanner. Happy Birthday. This code should be setup such that you just need to download 
// the "Adafruit Neopixel" library, include it and then run this.
// this is just some setup stuff, the fun code starts in "void loop()". 

#define PIN 6
// Output from the arduino is coming from pin 6 you can use any pins with a line squiggle, 
//this has something to do with being able to send out square pulses. 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)

//Here are some things that you might want to know

// To reduce pixel burnout risk a 300 - 500 Ohm resistor should be added on first pixel's data input
// I soldered a 470 Ohm one there and covered it in heat shrink to make sure the little legs didn't 
// break but if they do it's easily replaced. 
// Avoid connecting the strip to a live circuit, if you do, at least connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz 
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

 // Hi Tanner, this is the fun part
 // I wrote a couple functions in here so you can test the strip
 // Each light has bee assigned to a number, you can address them 
 // individually: 
 
 //(the following code should light up some Ocean and North Africa) 
 
  strip.setPixelColor(0, strip.Color(0, 0, 120)); //some Ocean
  strip.show();
  
  strip.setPixelColor(21, strip.Color(120, 20, 0)); //North Africa
  strip.show();

  //or together: 
  
  //(uncomment one of the following lines to see some cool shit) 
  
  //colorWipe(strip.Color(255, 0, 0), 50); // makes all your stuff red
  //colorWipe(strip.Color(0, 255, 0), 50); // makes all your stuff green
  //colorWipe(strip.Color(0, 0, 255), 50); // makes all your stuff blue
   
 //I found these online, these are exciting 

  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue

 //rainbow(20); // my personal favorite
 //rainbowCycle(20);
 //theaterChaseRainbow(50);

}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
