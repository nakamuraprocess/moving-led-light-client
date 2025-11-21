#include <Adafruit_NeoPixel.h>

#define LED_PIN 5
#define LED_MAX_SIZE 120
#define LED_BRIGHTNESS 100

Adafruit_NeoPixel strip(LED_MAX_SIZE, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t COLOR_BASE = strip.Color(255, 255, 255);
uint32_t COLOR_NONE = strip.Color(0, 0, 0);

void colorWipeForward(Adafruit_NeoPixel &strip){
  for(int i = 0; i < LED_MAX_SIZE; i++){
    if(i == 0){
        strip.setPixelColor(LED_MAX_SIZE-1, COLOR_NONE);
    }
    else{
        strip.setPixelColor(i-1, COLOR_NONE);
    }
    strip.setPixelColor(i, COLOR_BASE);
    strip.show();
  }
}

void colorWipeReverse(Adafruit_NeoPixel &strip){
  for(int i = LED_MAX_SIZE; i >= 0; i--){
    if(i == LED_MAX_SIZE-1){
      strip.setPixelColor(0, COLOR_NONE);
    }
    else{
      strip.setPixelColor(i+1, COLOR_NONE);
    }
    strip.setPixelColor(i, COLOR_BASE);
    strip.show();
  }
}

void colorWipeAll(Adafruit_NeoPixel &strip){
  for(int i = 0; i < LED_MAX_SIZE; i++){
    strip.setPixelColor(i, COLOR_BASE);
  }
  strip.show();
  delay(200);
  for(int i = 0; i < LED_MAX_SIZE; i++){
    strip.setPixelColor(i, COLOR_NONE);
  }
  strip.show();
  delay(100);
}

void colorWipeAllBlack(Adafruit_NeoPixel &strip){
  for(int i = 0; i < LED_MAX_SIZE; i++){
    strip.setPixelColor(i, COLOR_NONE);
  }
  strip.show();
}

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(LED_BRIGHTNESS);
  strip.show();
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    if (cmd == "FORWARD") {
      colorWipeForward(strip);
      Serial.println("FORWARD DONE");
    }
    else if (cmd == "REVERSE") {
      colorWipeReverse(strip);
      Serial.println("REVERSE DONE");
    }
    else if(cmd == "ALL"){
      colorWipeAll(strip);
      Serial.println("ALL DONE");
    }
    else if(cmd == "CLOSE"){
      colorWipeAllBlack(strip);
      Serial.println("CLOSE DONE");
    }
  }
}