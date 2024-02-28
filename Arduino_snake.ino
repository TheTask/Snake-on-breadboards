#include "leds.h"
#include "snake_io.h"
#include "colors.h"
#include "snake.h"

String inputString = "";    // A string to hold incoming data
bool stringComplete = true;  // Whether the string is complete


int led_row = 2;
int led_col = 2;

void setup() 
{
    /*
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

  

  randomSeed(analogRead(0));
  */
  Serial.begin(115200);
  inputString.reserve(200);  // Reserve 200 bytes for the inputString

  config::setDifficulty(config::difficulty::HARD);
  leds::init();

  snake::initBoard();
  snake::initSnake();
}

void loop() 
{
  /*
  // Check if a string has been completed
  analogWrite(3, 128);
  if (stringComplete) {
    int r = random(255);
    int g = random(255);
    int b = random(255);
    int a = random(255);
    


    if (inputString == "U\n") 
    {
      digitalWrite(10, HIGH);


      for(int i = 0; i < NUM_LEDS; i++)
      {
        board::getHandle().setPixelColor(i, colors::RED); // Set the first pixel to red
      }

    } 
    else if (inputString == "D\n")
    {
      digitalWrite(9, HIGH);

      for(int i = 0; i < NUM_LEDS; i++)
      {
        board::getHandle().setPixelColor(i, colors::GREEN); // Set the first pixel to red
      }

    }
    else if (inputString == "R\n")
    {
      digitalWrite(8, HIGH);
      for(int i = 0; i < NUM_LEDS; i++)
      {
        board::getHandle().setPixelColor(i, colors::BLUE); 
      }
    }
    else if (inputString == "L\n")
    {
      digitalWrite(7, HIGH);
      for(int i = 0; i < NUM_LEDS; i++)
      {
        board::getHandle().setPixelColor(i, colors::WHITE); 
      }
    }
    else if (inputString == "A\n")
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        board::getHandle().setPixelColor(i, colors::OFF); 
      }
    }
    else if (inputString == "B\n")
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        board::getHandle().setPixelColor(i, config::BORDER_COLOR); 
      }
    }
    else if (inputString == "Y\n")
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        board::getHandle().setPixelColor(i, config::getGameConfig().SNAKE_COLOR); 
      }
    }
    else
    {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        board::getHandle().setPixelColor(i,colors::SNAKE);
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
  */

  if (stringComplete)
  {
    if (inputString == "U\n") led_row--;
    else if (inputString == "D\n") led_row++;
    else if (inputString == "R\n") led_col++;
    else if (inputString == "L\n") led_col--;
  }

  //snake::board[ led_row * leds::WIDTH + led_col ] = 'O';

  Serial.print(inputString);
  inputString = "";
  stringComplete = false;

  
  leds::display(snake::board);

  delay(10);
}

void serialEvent()
{
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read();
    // Add it to the inputString
    inputString += inChar;
    // If the incoming character is a newline, set stringComplete to true
    if (inChar == '\n') 
    {
      stringComplete = true;
      return;
    }
  }
  
}
