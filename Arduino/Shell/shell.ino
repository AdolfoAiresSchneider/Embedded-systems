#include <Arduino_FreeRTOS.h>

#define qtd_comands 3
// Criar semaforo para imprimir no terminal

void get_comand(void *pvParameters);
void list_comand(void *pvParameters);
void pisca_led( void *pvParameters);

int sz_buffer = 0, flag_buffer = 0;
char t_buffer[100], comand[108];

int flag = 1;
void setup() {
  Serial.begin(9600);
  xTaskCreate(get_comand, (const portCHAR *)"Terminal" , 128, NULL, 3, NULL );
  xTaskCreate(list_comand, (const portCHAR *)"LC" , 128, NULL, 1, NULL );  
}

void read_terminal(){
 //  while(Serial.available() == 0) vTaskDelay(10);   
   while (1){
    while(Serial.available() == 0) vTaskDelay(1);   
    
    char c = Serial.read();
    delay(10);
    //Serial.print(" >>> ");
   // Serial.print((int)c);
    if((int)c == 13){ // '\n' 
     // Serial.println("ASDAD");
      break;
    }t_buffer[sz_buffer++] = c;
  }
  t_buffer[sz_buffer] = 13;
  delay(10);
 Serial.println(t_buffer);
  delay(10);
  
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
 // Serial.println("#####");
  return 1;
}

void loop(){
}

void list_comand(void *pvParameters){
 while(1){
  if(flag)Serial.println("##8###");
    vTaskDelay(1);
 }
}

void get_comand(void *pvParameters){
  while(1){
    Serial.print("> ");
    flag = 0;
    read_terminal();
    flag = 1;
    vTaskDelay(1);
    //Serial.print("@ ");  
   // Serial.print("@ ");
    vTaskDelay(1);
    
    
   /* vTaskDelay(10);
    if(cmp_str("lc", "lc")){
      vTaskDelay(10);
       Serial.println("#####");
       delay(10000);
       xTaskCreate(list_comand, (const portCHAR *)"LC" , 128, NULL, 0, NULL );  
       vTaskDelay(10);
    }
    else Serial.println("ERRROOO");
    vTaskDelay(10);*/
  }
}
