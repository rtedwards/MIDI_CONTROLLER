#include "FastLED.h"
#define PIN_4          4
#define PIN_5          5
#define PIN_6          6
#define PIN_7          7
#define NUM_LEDS      36

uint8_t midi_in [3];
uint8_t _status;
uint8_t _data_1;
uint8_t _data_2;

bool _red_on = 0;
bool _blue_on = 0;
bool _green_on = 0;

uint8_t _red[NUM_LEDS];   //stored value for red
uint8_t _blue[NUM_LEDS];  //stored value for blue
uint8_t _green[NUM_LEDS]; //stored value for green

uint8_t red[NUM_LEDS];   //final value
uint8_t blue[NUM_LEDS];  //final value
uint8_t green[NUM_LEDS]; //final value

uint8_t _red_pitch = 0; //pitch send from controller
uint8_t _blue_pitch = 0; //pitch send from controller
uint8_t _green_pitch = 0; //pitch send from controller

uint8_t _spread = 1;   //number of pixels turned on
uint8_t _start_pixel = 1; //NUMPIXELS/2;

uint8_t _on_off = 1; //128 = unpressed, 144 = pressed


CRGB strip_1[NUM_LEDS];
//CRGB strip_2[NUM_LEDS];
//CRGB strip_3[NUM_LEDS];
//CRGB strip_4[NUM_LEDS];

void OnOff(uint8_t on_off) {
  for(int i=0;i<NUM_LEDS;i++) {
    strip_1[i].setRGB(red[i],green[i],blue[i]);
//    strip_2[i].setRGB(red[i],green[i],blue[i]);
//    strip_3[i].setRGB(red[i],green[i],blue[i]);
//    strip_4[i].setRGB(red[i],green[i],blue[i]);
  }//end for

}//end OnOff()

void setColors() {
    //reset pixels
    for (int i=0; i<NUM_LEDS; i++) {
      _red[i] = 0;
      _blue[i] = 0;
      _green[i] = 0;
    }//end for

    //set pixel spread from start pixel
    for (int i=_start_pixel; i<_start_pixel + _spread/2; i++) {
      if (i>=0 && i<NUM_LEDS) { //check range of array
        _red[i] = _red_pitch;
        _blue[i] = _blue_pitch;
        _green[i] = _green_pitch;
      }//end if
    }//end for

    for (int i=_start_pixel; i>_start_pixel - _spread/2; i--) {
      if (i>=0 && i<NUM_LEDS) { //check range of array
        _red[i] = _red_pitch;
        _blue[i] = _blue_pitch;
        _green[i] = _green_pitch;
      }//end if
    }//end for
      
}//end setColors()
void checkButton(uint8_t type, uint8_t channel, uint8_t pitch) {

  if (channel == 77) {
    _red_pitch = pitch;
  }//end if
  
  else if (channel == 78) {
    _blue_pitch = pitch;
  }//end elseif
  
  else if (channel == 79) {
    _green_pitch = pitch;
  }//end elseif
  
  //Red On-Off
  else if (channel == 41) {
    if (pitch == 127 && _red_on == 1) {
      _red_on = 0;
      
      for(int i=0;i<NUM_LEDS;i++) {
        strip_1[i].setRGB(0, 0, 0);
//        strip_2[i].setRGB(0, 0, 0);
//        strip_3[i].setRGB(0, 0, 0);
//        strip_4[i].setRGB(0, 0, 0);
      }//end for

      FastLED.show();
    }//end if
    
    else if (pitch == 127 && _red_on == 0) 
      _red_on = 1;
  }//end if

  //Blue On-Off
  if (channel == 42) {
    if (pitch == 127 && _blue_on == 1) {
      _blue_on = 0;
      
      for(int i=0;i<NUM_LEDS;i++) {
        strip_1[i].setRGB(0, 0, 0);
//        strip_2[i].setRGB(0, 0, 0);
//        strip_3[i].setRGB(0, 0, 0);
//        strip_4[i].setRGB(0, 0, 0);
      }//end for

      FastLED.show();
    }//end if
    
    else if (pitch == 127 && _blue_on == 0) 
      _blue_on = 1;
  }//end if

  //Green On-Off
  if (channel == 43) {
    if (pitch == 127 && _green_on == 1) {
      _green_on = 0;
      
      for(int i=0;i<NUM_LEDS;i++) {
        strip_1[i].setRGB(0, 0, 0);
//        strip_2[i].setRGB(0, 0, 0);
//        strip_3[i].setRGB(0, 0, 0);
//        strip_4[i].setRGB(0, 0, 0);
      }//end for

      FastLED.show();
    }//end if
    
    else if (pitch == 127 && _green_on == 0) 
      _green_on = 1;
  }//end if

  //Spread
  if (channel == 83) {
    _spread = pitch;
  }//end if

  //Start Pixel
  if (channel == 84) {
    _start_pixel = (int)(pitch * (NUM_LEDS / 127.0)); //map to length of LED strip
  }//end if
}//end checkButton()


void showColors() {
  if (_red_on == 1) {
    for (int i=0; i<NUM_LEDS; i++)
      red[i] = _red[i];
  }//end if
  else if (_red_on == 0) {
    for (int i=0; i<NUM_LEDS; i++)
      red[i] = 0;
  }//end if
  
  if (_blue_on == 1) {
    for (int i=0; i<NUM_LEDS; i++)
      blue[i] = _blue[i];
  }//end if
  else if (_blue_on == 0) {
    for (int i=0; i<NUM_LEDS; i++)
      blue[i] = 0;
  }//end if
  
  if (_green_on == 1) {
    for (int i=0; i<NUM_LEDS; i++)
      green[i] = _green[i];
  }//end if
  else if (_green_on == 0) {
    for (int i=0; i<NUM_LEDS; i++)
      green[i] = 0;
  }//end if

    for(int i=0;i<NUM_LEDS;i++) {
      strip_1[i].setRGB(red[i],green[i],blue[i]);
//      strip_2[i].setRGB(red[i],green[i],blue[i]);
//      strip_3[i].setRGB(red[i],green[i],blue[i]);
//      strip_4[i].setRGB(red[i],green[i],blue[i]);
    }//end for

    FastLED.show(); 
}//end showColors()



void setup() {
  FastLED.addLeds<WS2812B, PIN_4, RGB>(strip_1, NUM_LEDS);
//  FastLED.addLeds<WS2812B, PIN_5, RGB>(strip_2, NUM_LEDS);
//  FastLED.addLeds<WS2812B, PIN_6, RGB>(strip_3, NUM_LEDS);
//  FastLED.addLeds<WS2812B, PIN_7, RGB>(strip_4, NUM_LEDS);

  FastLED.show();

  //*****  Serial Code  *****//
  Serial.begin(2000000);
  Serial.flush();
} //end setup()


void loop() {
  while(Serial.available() < 3){
    //Wait for bytes to come in
  }//end while
  
  if (Serial.available() >= 3) {
    for (int i=0; i<3; i++) {
      midi_in[i] = Serial.read();  //read midi input
    }//end for

    _status = midi_in[0];
    _data_1 = midi_in[1];
    _data_2 = midi_in[2];

//    OnOff(_status); //check if on_off button pressed
    checkButton(_status, _data_1, _data_2);  
    setColors();
    showColors();
 
  }//end if
  
}//end loop()


