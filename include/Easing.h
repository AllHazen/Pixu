#ifndef EASING_H
#define EASING_H 
#include <Arduino.h>

class Easing{
  public: 
  Easing() = delete; // mencegah membuat objek dari class ini

  static float easeIn(float t){
    return t*t; // ketika t kecil maka return kecil, dan sebaliknya
  }

  static float easeOut(float t) {
    return 1-pow(1-t,2);
  }

  static float easeInOut(float t) {
    return t < 0.5 ? 2*t*t : 1- 2*pow(1-t,2);
  }

  static float linearInter(float initial, float end, float t){
    return initial + (end - initial) * t;
  }

};

#endif 