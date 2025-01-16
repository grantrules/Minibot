#include <map>
#include <Arduino.h>
#include <ESP32Servo.h>
#include "drive.h"

#define LEFT_PIN 15
#define RIGHT_PIN 14

// using feebot fs90r
// https://www.pololu.com/file/0J1867/FS90R.pdf

#define PULSE_WIDTH_LOW 700
#define PULSE_WIDTH_HIGH 2300
#define PULSE_WIDTH_MID 1500

MotorFactory mf(PULSE_WIDTH_HIGH, PULSE_WIDTH_MID, PULSE_WIDTH_LOW);

Movement movement(mf);

enum direction
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  STOP
};

std::map<direction, void (Movement::*)()> directions = {
    {FORWARD, &Movement::forward},
    {BACKWARD, &Movement::backward},
    {LEFT, &Movement::left},
    {RIGHT, &Movement::right},
    {STOP, &Movement::stop}};

std::map<char, direction> keyMap = {
    {'w', FORWARD},
    {'s', BACKWARD},
    {'a', LEFT},
    {'d', RIGHT}};

long lastInputTime = 0;

long startTime = millis();

direction currentDirection = STOP;

Motor motor;

void setup()
{
  movement.setMotors(LEFT_PIN, RIGHT_PIN);
  Serial.begin(9600);
  Serial.println("Setup complete");
}

void loop()
{
  if (Serial.available() > 0)
  {
    char lastChar = Serial.read();

    if (keyMap.find(lastChar) != keyMap.end())
    {
      currentDirection = keyMap[lastChar];
      Serial.println(currentDirection);
      lastInputTime = millis();
    }
  }

  if (millis() - lastInputTime > 100)
  {
    currentDirection = STOP;
  }

  (movement.*directions[currentDirection])();
}