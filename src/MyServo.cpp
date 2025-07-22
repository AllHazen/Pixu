#include <ESP32Servo.h>
#include "Easing.h"
#include <MyServo.h>

MyServo::MyServo(int pin, Servo& servo) : servo(servo), servoPin(pin) {
    servo.attach(servoPin, minUs, maxUs);
    servo.writeMicroseconds(1166);
}

void MyServo::servoOpen(){
        int currentServoPos = servo.readMicroseconds();
    for(int step=0; step<12; step++){
        float t = (float)step/11.0;
        float easeRatio = Easing::easeIn(t);
        int target = 1550;
        float easedPos = minUs + (target - currentServoPos) * easeRatio;
        servo.writeMicroseconds((int)easedPos);
    }
}

void MyServo::servoSleep() {
        int currentServoPos = servo.readMicroseconds();
    for (int step=0; step< 12; step++){
        float t = (float)step/11.0;
        float easeRatio = Easing::easeOut(t);
        int target = 1330;
        float easedPos = currentServoPos + (target - currentServoPos) * easeRatio;
        servo.writeMicroseconds((int)easedPos);
    } 
}