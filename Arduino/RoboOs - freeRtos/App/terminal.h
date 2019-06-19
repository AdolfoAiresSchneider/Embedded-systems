#ifndef TERMINAL_H
#define TERMINAL_H 1


#define TERMINAL_NUM_ENTRADA 6
#define TERMINAL_LED 0
#define TERMINAL_PWM 1
#define TERMINAL_FRENTE 2
#define TERMINAL_TRAS 3
#define TERMINAL_ESQUERDA 4
#define TERMINAL_DIREITA 5
#define TERMINAL_INPUT 6

int pwmTerminal = 100;
int pinosTerminal[TERMINAL_NUM_ENTRADA];

void terminalLed(void *p){
  while(1){
    if(digitalRead(pinosTerminal[TERMINAL_LED]) == 1){
      ligaFarol();
    }
    else{
      desligaFarol();
    }
    delayTarefa(1);
  }
}

void terminalPwm(void *p){
  while(1){
    pwmTerminal = map(analogRead(pinosTerminal[TERMINAL_PWM]), 0, 1023, 0, 255);
    delayTarefa(1);
  }
}

void terminalPara(void *p){
  while(1){
    if(digitalRead(pinosTerminal[TERMINAL_FRENTE]) == 0
      && digitalRead(pinosTerminal[TERMINAL_TRAS]) == 0
      && digitalRead(pinosTerminal[TERMINAL_ESQUERDA]) == 0
      && digitalRead(pinosTerminal[TERMINAL_DIREITA]) == 0){
      paraRobo();
    }
    delayTarefa(1);
  }
}

void terminalFrente(void *p){
  while(42){
    if(digitalRead(pinosTerminal[TERMINAL_FRENTE]) == 1){
      avanca(pwmTerminal);
    }
    delayTarefa(1);
  }
}

void terminalTras(void *p){
  while(1){
    if(digitalRead(pinosTerminal[TERMINAL_TRAS]) == 1){
      re();
    }
    delayTarefa(1);
  }
}

void terminalEsquerda(void *p){
  while(42){
    if(digitalRead(pinosTerminal[TERMINAL_ESQUERDA]) == 1){
      viraEsquerda(pwmTerminal);
    }
    delayTarefa(1);
  }
}

void terminalDireita(void *p){
  while(42){
    if(digitalRead(pinosTerminal[TERMINAL_DIREITA]) == 1){
      viraDireita(pwmTerminal);
    }
    delayTarefa(1);
  }
}

void inicializa_terminal(int led, int pwm, int frente, int tras, int esquerda, int direita){
  pinMode(led, INPUT);
  pinMode(pwm, INPUT);
  pinMode(frente, INPUT);
  pinMode(tras, INPUT);
  pinMode(esquerda, INPUT);
  pinMode(direita, INPUT);

  pinosTerminal[TERMINAL_LED] = led;
  pinosTerminal[TERMINAL_PWM] = pwm;
  pinosTerminal[TERMINAL_FRENTE] = frente;
  pinosTerminal[TERMINAL_TRAS] = tras;
  pinosTerminal[TERMINAL_ESQUERDA] = esquerda;
  pinosTerminal[TERMINAL_DIREITA] = direita;

  criaTarefa(&terminalPwm, "tPwm",1,80);
  criaTarefa(&terminalLed, "tLed", 0, 90);
  criaTarefa(&terminalFrente, "tFrente", 0, 80);
  
  criaTarefa(&terminalPara, "tPara", 0, 90);  
  criaTarefa(&terminalTras, "tTras",0,128);
  criaTarefa(&terminalEsquerda, "tEsq",0,128);
  criaTarefa(&terminalDireita, "tDir",0,128);
}

#endif // TERMINAL_H
