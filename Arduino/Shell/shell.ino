#include <Arduino_FreeRTOS.h>
#include <semphr.h>  

#define qtd_comands 3

void get_comand(void *pvParameters);
void list_comand(void *pvParameters);
void pisca_led( void *pvParameters);

int sz_buffer = 0, flag_buffer = 0;
char t_buffer[100], comand[108];
char list_comands[qtd_comands][20] = {"LC", "PLED", "-PLED"};

TaskHandle_t LC, PLED;
SemaphoreHandle_t xSerialSemaphore;

void setup() {
  Serial.begin(9600);
  
  xSerialSemaphore = xSemaphoreCreateMutex();
  if ( ( xSerialSemaphore ) != NULL ) xSemaphoreGive( ( xSerialSemaphore ) );

  xTaskCreate(get_comand, (const portCHAR *)"Terminal" , 128, NULL, 3, NULL );
  xTaskCreate(list_comand, (const portCHAR *)"LC" , 128, NULL, 1, &LC );  
  xTaskCreate(pisca_led, (const portCHAR *)"PLED" , 128, NULL, 2, &PLED );
  vTaskSuspend( LC ), vTaskSuspend( PLED );
  
}

void read_terminal(){
   while (1){
    while(Serial.available() == 0) vTaskDelay(5);       
    char c = Serial.read();
    delay(1);
    if((int)c == 13) break; // '\n' 
    t_buffer[sz_buffer++] = c;
  } t_buffer[sz_buffer] = 13;
  memset(comand, 0, sizeof comand);
  memcpy(comand, t_buffer, sizeof(char)*(sz_buffer));
  memset(t_buffer, 0, sizeof t_buffer);
  flag_buffer = sz_buffer = 0;
}

bool cmp_str(const char * a,const char * b){
  if(strlen(a) != strlen(b)) return 0;
  for(int i = 0; i < strlen(a); i++){
    if(a[i] != b[i]) return 0;
  }
  return 1;
}

void loop(){
}

void list_comand(void *pvParameters){
 while(1){
  if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE ){
    Serial.println();
    for(int i = 0; i < qtd_comands; i++){
      Serial.print(list_comands[i]);    
      Serial.print(" ");
      vTaskDelay(1);
    }
    Serial.println();
    xSemaphoreGive( xSerialSemaphore );
    vTaskSuspend( NULL );
  }
 }
}

void pisca_led( void *pvParameters){
  pinMode(LED_BUILTIN, OUTPUT);
  while(1){
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); 
  }
}

void get_comand(void *pvParameters){
  while(1){
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE ){
      Serial.print("> ");
      read_terminal();
      xSemaphoreGive( xSerialSemaphore );
      if(cmp_str("PLED", comand)) vTaskResume(PLED);
      else if(cmp_str("-PLED", comand)) vTaskSuspend(PLED);
      else if(cmp_str("LC", comand)) vTaskResume(LC);
      else Serial.println("ERRO!!!");
      vTaskDelay(1);
    }
  }
}
