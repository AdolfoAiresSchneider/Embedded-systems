#include "roboOS.h"
#ifndef farol_h
#define farol_h

int pinoFarol;

void inicializa_farol(int pino){
  pinMode(pino, OUTPUT);
  //Serial.println(pino);
  pinoFarol = pino;
}

void ligaFarol(){
  digitalWrite(pinoFarol, HIGH);
}

void desligaFarol(){
 digitalWrite(pinoFarol, LOW);
}

#endif
