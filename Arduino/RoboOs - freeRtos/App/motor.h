#ifndef motor_h
#define motor_h

#include "systemCalls.h"

#define HORARIO 1
#define ANTIHORARIO 0

//---------------------------------
int pino_velocidade, pino_sentido[2];
int pwm;
bool sentido[2];
TaskHandle_t task_girar[2], task_parar[2];

void tarefaGirar1(void *pvParameters){
  while(1){
    digitalWrite(pino_sentido[0], (sentido[0] ? HIGH : LOW));
    analogWrite(pino_velocidade, pwm);
    pausaTarefa(task_girar[0]);
  }
}

void tarefaGirar2(void *pvParameters){
  while(1){
    digitalWrite(pino_sentido[1], (sentido[1] ? HIGH : LOW));
    analogWrite(pino_velocidade, pwm);
    pausaTarefa(task_girar[1]);
  }
}

void tarefaParar1(void *pvParameters){
  while(1){
    analogWrite(pino_velocidade, 0);
    pausaTarefa(task_parar[0]);
  }
}

void tarefaParar2(void *pvParameters){
  while(1){
    analogWrite(pino_velocidade, 0);
    pausaTarefa(task_parar[1]);
  }
}

void criaTarefaMotor1(){
  int tam = 80;
  task_girar[0] = *criaTarefa(&tarefaGirar1, "tarefa_girar1", 0, tam);
  pausaTarefa(task_girar[0]);
  task_parar[0] = *criaTarefa(&tarefaParar1, "tarefa_parar1", 0, tam);
  pausaTarefa(task_parar[0]);
}

void criaTarefaMotor2(){
    int tam = 80;
  task_girar[1] = *criaTarefa(&tarefaGirar2, "tarefa_girar2", 0, tam);
  pausaTarefa(task_girar[1]);
  task_parar[1] = *criaTarefa(&tarefaParar2, "tarefa_parar2", 0, tam);
  pausaTarefa(task_parar[1]);
}

void girar(int motor, bool sen, int vel){// FAZ O MOTOR GIRAR.. ANDAR
  // criar tarefa para ficar girando
  pwm = vel;
  sentido[motor] = sen;
  adicionaTarefa(task_girar[motor]);
}

void para(int motor){
  // pause na tarefa que gira ESSA roda
  adicionaTarefa(task_parar[motor]);
}

/************************************************************************************************/
// API

// pino_sentidoX -> horário ou anti-horário
// pino_motorX -> pino que define a pwm do motor, tem de ser PWM
void inicializa_motores(int pino_vel, int pino_sentido1, int pino_sentido2){
  /*
  Serial.println("----");
  Serial.println(pino_vel);
  Serial.println(pino_sentido1);
  Serial.println(pino_sentido2);
  Serial.println("----");
  //*/
  pinMode(pino_vel, OUTPUT);
  pinMode(pino_sentido1, OUTPUT);
  pinMode(pino_sentido2, OUTPUT);
  pino_velocidade = pino_vel;
  pino_sentido[0] = pino_sentido1;
  pino_sentido[1] = pino_sentido2;
  criaTarefaMotor1();
  criaTarefaMotor2();
}

// horario -> horário ou anti-horário
// pwm -> em uma escala de 0 a 255

void paraRobo(){
  para(0);
  para(1);
}

//para o robô, vira para esquerda durante x ms, a roda da direita vai para frente e a da esquerda vai para trás.
void viraEsquerda(int pwm){
  para(0);
  para(1);
  girar(0, ANTIHORARIO, pwm);
  girar(1, ANTIHORARIO, pwm);
}

//para o robô, vira para esquerda durante x ms, a roda da esquerda vai para frente e a da direita vai para trás.
void viraDireita(int pwm){
  para(0);
  para(1);
  girar(0, HORARIO, pwm);
  girar(1, HORARIO, pwm);
}

void re(){
  const int pwm = 100;
  para(0);
  para(1);
  girar(0, ANTIHORARIO, pwm);
  girar(1, HORARIO, pwm);
}

void avanca(int pwm){
  para(0);
  para(1);
  girar(0, HORARIO, pwm);
  girar(1, ANTIHORARIO, pwm);
}

#endif
