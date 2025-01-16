#ifndef DRIVE_H
#define DRIVE_H

#include <ESP32Servo.h>

class Motor
{
private:
    int pin;
    bool isInverted;
    int high;
    int low;
    int mid;
    Servo servo;

public:
    //Motor(int pin, bool isInverted, int high, int low, int mid);
    Motor();
    void attach(int pin, bool isInverted, int high, int low, int mid);
    void forward();
    void backward();
    void stop();
};

class MotorFactory
{
private:
    int PULSE_WIDTH_HIGH;
    int PULSE_WIDTH_MID;
    int PULSE_WIDTH_LOW;

public:
    MotorFactory(int high, int mid, int low);
    void attachMotor(Motor& motor, int pin, bool isInverted);
};

class Movement
{
private:
    MotorFactory& mf;
    Motor leftMotor;
    Motor rightMotor;

public:
      Movement(MotorFactory& mf);
      void setMotors(int leftPin, int rightPin);
    void forward();
    void backward();
    void left();
    void right();
    void stop();
};

#endif // DRIVE_H