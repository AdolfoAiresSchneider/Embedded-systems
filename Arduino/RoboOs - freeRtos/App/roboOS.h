#ifndef roboOS_h
#define roboOS_h

#include <Arduino_FreeRTOS.h>
#include "motor.h"
#include "ultrassonico.h"
#include "farol.h"
#include "terminal.h"
#include "automaton.h"

// ------------------------------------------------------------------------------------------------------------------------- API*****
/* setup todas as partes do robo */
void inicializa_robo(int pin_vel, int pin_sent1, int pin_sent2, int pin_farol, int pin_ultra1, int pin_ultra2);
// Define o modo de operação do robo(controlado ou automatico)
bool inicializa_modo(bool modo, int in_led, int in_velocidade, int in_frente, int in_tras, int in_esquerda, int in_direita );

/* Controle dos motores */
void inicializa_motores(int pino_velocidade, int pino_sentido1, int pino_sentido2); // setuplização
void viraEsquerda(int pwm);
void viraDireita(int pwm);
void re();
void avanca(int pwm);
void paraRobo();

/* Controle do farol */
void inicializa_farol(int pino);// setuplização
void ligaFarol();
void desligaFarol();

/* Controle do ultrassonico */
bool inicializa_sensorDistancia(int pino1, int pino2);// setuplização
long distObstaculo();

// -------------------------------------------------------------------------------------------------------------------------

/* setup todas as partes do robo */
void inicializa_robo(int pin_vel, int pin_sent1, int pin_sent2, int pin_farol, int pin_ultra1, int pin_ultra2){
  inicializa_motores(pin_vel, pin_sent1, pin_sent2);
  inicializa_farol(pin_farol);
  inicializa_sensorDistancia(pin_ultra1, pin_ultra2);
}

bool inicializa_modo(bool modo, int in_led = -1, int in_velocidade = -1, int in_frente = -1, int in_tras= -1, int in_esquerda = -1, int in_direita = -1){
  if(modo == 0){ // modo autonomo
    inicializa_automato();
  }else{ // modo terminal(controlado)
    if(in_led == -1 || in_velocidade == -1 || in_frente == -1|| in_tras  ==  -1 || in_esquerda == -1 || in_direita == -1)  return false;
    inicializa_terminal(in_led, in_velocidade, in_frente, in_tras, in_esquerda, in_direita);
    return true;
  }
}

#endif
