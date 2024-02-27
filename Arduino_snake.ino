#include <Adafruit_NeoPixel.h>
#include "snake_io.h"
#include "colors.h"

#define LED_PIN     13  // Define the pin connected to the NeoPixels
#define NUM_LEDS    18  // Number of LEDs you are controlling

// Create an instance of the Adafruit_NeoPixel class called 'leds'.
// Parameter 1 = number of pixels in the strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);



String inputString = "";    // A string to hold incoming data
bool stringComplete = false;  // Whether the string is complete

void setup() {
  leds.begin(); // Initialize the NeoPixel library.
  leds.setBrightness(20); // Set brightness to maximum (0-255)
  pinMode(2, OUTPUT); //0
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(2, HIGH);

  Serial.begin(9600);
  inputString.reserve(200);  // Reserve 200 bytes for the inputString

  randomSeed(analogRead(0));
}

void loop() {



  
  // Check if a string has been completed
  analogWrite(3, 128);
  if (stringComplete) {
    int r = random(255);
    int g = random(255);
    int b = random(255);
    int a = random(255);
    



    if (inputString == "DPAD_UP\n") 
    {
      digitalWrite(10, HIGH);


      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds.setPixelColor(i, colors::RED); // Set the first pixel to red
      }

    } 
    else if (inputString == "DPAD_DOWN\n")
    {
      digitalWrite(9, HIGH);

      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds.setPixelColor(i, colors::GREEN); // Set the first pixel to red
      }

    }
    else if (inputString == "DPAD_RIGHT\n")
    {
      digitalWrite(8, HIGH);
      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds.setPixelColor(i, colors::BLUE); 
      }
    }
    else if (inputString == "DPAD_LEFT\n")
    {
      digitalWrite(7, HIGH);
      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds.setPixelColor(i, colors::WHITE); 
      }
    }
    else
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds.setPixelColor(i,colors::SNAKE);
      }

      digitalWrite(10, LOW);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      
    }
    Serial.print(inputString);
    // Clear the string for new input:
    inputString = "";
    stringComplete = false;
  }
  leds.show(); // Update the LED(s) with the set color
  
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    // Add it to the inputString
    inputString += inChar;
    // If the incoming character is a newline, set stringComplete to true
    if (inChar == '\n') {
      stringComplete = true;
      return;
    }
  }
}
