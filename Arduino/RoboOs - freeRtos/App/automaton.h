#ifndef automaton_h
#define automaton_h

#include "motor.h"
#include "ultrassonico.h"
#include "farol.h"
#include "terminal.h"
#include "automaton.h"
#include "roboOS.h"


#define DIST_LIM 200
#define VELOCIDADE 100

void checaObstaculo(void *p){
  while(1){
   // Serial.println(distObstaculo());
    if(distObstaculo() <= DIST_LIM){
      paraRobo();   
      viraEsquerda(VELOCIDADE);
      while(distObstaculo() <= DIST_LIM){
        ligaFarol();
        delayTarefa(1);
      }
      desligaFarol();
      paraRobo(); 
      avanca(VELOCIDADE);
      delayTarefa(1);
    }
  }
}

void inicializa_automato(){
  avanca(VELOCIDADE);
  criaTarefa(checaObstaculo, "checkObst", 0, 128);
}

#endif
