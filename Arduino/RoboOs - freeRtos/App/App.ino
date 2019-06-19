#include "roboOS.h"

void setup(){
  Serial.begin(9600); 
  inicializa_robo(3, 8, 7, 12, 9, 11);
  inicializa_modo(1, 10, A5, A0, A1, A2, A3);
}

void loop(){
}
