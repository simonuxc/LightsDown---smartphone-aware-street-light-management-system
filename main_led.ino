#include <FastLED.h>
#include <Wire.h>

#define LED_PIN     5
#define NUM_LEDS    86
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() { 
      Serial.begin(9600);
      Wire.begin(8);                /* join i2c bus with address 8 */
      Wire.onReceive(receiveEvent); /* register receive event */
      FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
      fill_solid(leds, NUM_LEDS, CHSV(HUE_BLUE, 255, 1));

      // Serial.begin(9600);           /* start serial for debug */
}

int lastDistance = -1;

// amount of lights to one side to be lit up
int lastId = 0;
int moveDir = 1;
int currLed = 1;
int radius = 10;
int maxBrightness = 255;

void moveThroughLeds() {
  if (currLed == NUM_LEDS - 1) {
    moveDir = -1;
  }
  else if (currLed == 0) {
    moveDir = 1;
  }

  lastId = currLed;
  currLed = lastId + moveDir;

  LightUp(currLed);
  int brightnessStep = (maxBrightness * (99 / radius)) / 100;
  int currBrightness = maxBrightness;
  // set the brightness of lamps to the left (id decreasing)
  int currId = currLed;
  while (currId < NUM_LEDS && currId - currLed < radius) {
    currBrightness -= brightnessStep;
    currId++;
    leds[currId] = CHSV(HUE_PINK, 255, currBrightness);
  }
  // set the brightness of lamps to the right (id increasing)
  currBrightness = maxBrightness;
  currId = currLed;
  while (currId >= 0 && currLed - currId < radius) {
    currBrightness -= brightnessStep;
    currId--;
    leds[currId] = CHSV(HUE_PINK, 255, currBrightness);
  }

  FastLED.show();
}

void loop() {
  // moveThroughLeds();
  delay(80);
}

int ledId1= 5;
int ledId2 = 5;
int nextLed = -1;

void receiveEvent(int howMany) {
  // fill_solid(leds, NUM_LEDS, CHSV(HUE_BLUE, 255, 1));
  // Serial.println((Wire.available()));

 while (0 < Wire.available()) {
    int c = Wire.read();      /* receive byte as a character */
    Serial.println(c);
    Serial.println(letter);
    if (letter == 1) {
      nextLed = 1;
    }
    if (letter == 2) {
      nextLed = 2;
    }
    uint8_t c = Wire.read();
    // Serial.println(c);
    if (nextLed == 1) {
      Serial.print("pirmas: ");
      Serial.println(c);
      leds[ledId1] = CHSV(HUE_BLUE, 255, 1);
      ledId1 = LedID(c);
      leds[ledId1] = CHSV(HUE_PINK, 255, maxBrightness);
      nextLed = -1;
    }
    if (nextLed == 2) {
      Serial.print("antras: ");
      Serial.println(c);
      leds[ledId2] = CHSV(HUE_BLUE, 255, 1);
      ledId2 = c / 3.5;
      leds[ledId2] = CHSV(HUE_PINK, 255, maxBrightness);
      nextLed = -1;
    }
    
    if (c != 1) {
      // Serial.println(c);
      int ledId = LedID(c);
      //Serial.print(c);
      //LightUp(ledId);
    }
    if (lastDistance == -1) {
      lastDistance = c;
    }
    else {
      int distanceDifference = lastDistance - distance;
      Serial.print("Last distance: ");
      Serial.println(lastDistance);
      Serial.print("Current distance: ");
      Serial.println(distance);
      Serial.println();
      if (distanceDifference < 0) { distanceDifference *= -1; }
      if (distanceDifference >= 25) {
        Serial.println("DIfference");
        if (distance > lastDistance) {
          distance = lastDistance + 25;
        }
        else {
          distance = lastDistance - 25;
        }
      }
      int ledID = LedID(c * 1.4);
      Serial.print("Led id ");
      Serial.println(ledID);

      if (ledID < 30 && c != 13) {
        LightUpSector(0, 43);
      }
      else {
        LightUpSector(43, 86);
      }
      
      Serial.print("Aproximated: ");
      Serial.println(c);
    }
  }
  FastLED.show();
}
 
int LedID(int distance) {
  // Serial.println(distance);
  // int ledGap = 300/86;
  return distance / 3.5; //+ 30/ledGap;
}

// changing intensity of individual light
// intensity of the main lamp

void LightUpSector(int start, int end) {
  fill_solid(leds, NUM_LEDS, CHSV(HUE_BLUE, 255, 1));
  for (int i = start; i < end; i++) {
    leds[i] = CHSV(HUE_PINK, 255, maxBrightness);
  }
  FastLED.show();
}

void LightUp(int mainLampId) {
  fill_solid(leds, NUM_LEDS, CHSV(HUE_BLUE, 255, 1));
  leds[mainLampId] = CHSV(HUE_YELLOW, 255, maxBrightness);

  int brightnessStep = (maxBrightness * (99 / radius)) / 100;
  int currBrightness = maxBrightness;
  // set the brightness of lamps to the left (id decreasing)
  int currId = mainLampId;
  while (currId < NUM_LEDS && currId - mainLampId < radius) {
    currBrightness -= brightnessStep;
    currId++;
    leds[currId] = CHSV(HUE_YELLOW, 255, currBrightness);
  }
  // set the brightness of lamps to the right (id increasing)
  currBrightness = maxBrightness;
  currId = mainLampId;
  while (currId >= 0 && mainLampId - currId < radius) {
    currBrightness -= brightnessStep;
    currId--;
    leds[currId] = CHSV(HUE_YELLOW, 255, currBrightness);
  }
  // if (mainLampId + radius + 1 < NUM_LEDS) {
  //   leds[mainLampId + radius + 1] = CHSV(HUE_BLUE, 255, 1);
  // }
  // if (mainLampId - radius - 1 >= 0) {
  //   leds[mainLampId - radius - 1] = CHSV(HUE_BLUE, 255, 1);
  // }
  // FastLED.show();
}