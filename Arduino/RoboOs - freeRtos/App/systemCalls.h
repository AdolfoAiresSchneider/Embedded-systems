#include <Arduino_FreeRTOS.h>

// ----Chamadas de sistema------------------------------------------------------------------------------------------------------------------------

TaskHandle_t * criaTarefa(void (*func)(void *pvParameters), const char * nome, int prioridade, int pilha){
  TaskHandle_t * nick = new TaskHandle_t;
  xTaskCreate(*func, nome, pilha, NULL, prioridade, nick);
  return nick; 
}

void pausaTarefa(TaskHandle_t & nick){
  vTaskSuspend(nick);
}

void adicionaTarefa(TaskHandle_t & nick){
  vTaskResume(nick);
}

void delayTarefa(int ms){
  vTaskDelay(ms);
}

// -----------------------------------------------------------------------------------------------------------------------------------------------
