#ifndef MY_SERVO_H
#define MY_SERVO_H
#include <ESP32Servo.h>
#include "Easing.h"

class MyServo{
    protected:
    Servo &servo; 
    int servoPin;
    int minUs = 1000;
    int maxUs = 2000; 
    
    public:
    MyServo(int pin, Servo &servo);   

    void servoOpen(){};

    void servoSleep() {};
};


#endif