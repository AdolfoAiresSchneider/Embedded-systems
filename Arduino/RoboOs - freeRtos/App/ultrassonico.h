#ifndef ultrassonico_h
#define ultrassonico_h


int trigger, echo;

bool inicializa_sensorDistancia(int pino1, int pino2){
 // pinMode(pino, INPUT);
  trigger = pino1;
  echo = pino2;
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

long distObstaculo(){
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger, LOW);
    // pwm do som: 340 m/s ≃ 29 ms/cm
    long x =  pulseIn(echo, HIGH);
    return x/29/2;    
}

#endif
