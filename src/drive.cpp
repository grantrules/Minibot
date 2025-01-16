#include <ESP32Servo.h>
#include "drive.h"

  Motor::Motor()
  {
  }

  void Motor::attach(int pin, bool isInverted, int high, int low, int mid)
  {
    this->pin = pin;
    this->servo.attach(pin);
    this->mid = mid;
    this->low = (isInverted ? high : low);
    this->high = (isInverted ? low : high);
  }


  void Motor::forward()
  {
    Serial.println("forward");
    Serial.println(this->low);
    Serial.print(this->servo.attached());
    this->servo.write(this->low);
  }

  void Motor::backward()
  {
    this->servo.write(this->high);
  }

  void Motor::stop()
  {
    this->servo.write(this->mid);
  }

MotorFactory::MotorFactory(int high, int mid, int low) : PULSE_WIDTH_HIGH(high), PULSE_WIDTH_MID(mid), PULSE_WIDTH_LOW(low)
{
}

void MotorFactory::attachMotor(Motor& motor, int pin, bool isInverted)
{
  motor.attach(pin, isInverted, this->PULSE_WIDTH_HIGH, this->PULSE_WIDTH_LOW, this->PULSE_WIDTH_MID);
}

Movement::Movement(MotorFactory& mf) : mf(mf)
{
}
/*
void Movement::setMotorFactory(MotorFactory mf) {
  this->mf = mf;
}
*/

void Movement::setMotors(int leftPin, int rightPin)
{
  this->mf.attachMotor(this->leftMotor, leftPin, false);
  this->mf.attachMotor(this->rightMotor, rightPin, true);
}

void Movement::forward()
{
  this->leftMotor.forward();
  this->rightMotor.forward();
}

void Movement::backward()
{
  this->leftMotor.backward();
  this->rightMotor.backward();
}

void Movement::left()
{
  this->leftMotor.backward();
  this->rightMotor.forward();
}

void Movement::right()
{
  this->leftMotor.forward();
  this->rightMotor.backward();
}

void Movement::stop()
{
  this->leftMotor.stop();
  this->rightMotor.stop();
}