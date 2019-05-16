void setup() {
  Serial.begin(9600);
}

int sz_buffer = 0, flag_buffer = 0;
char t_buffer[100], comand[108];

void read_terminal(){
   while (Serial.available() > 0) {
    char c = Serial.read();
    if((int)c == 13){ // '\n' 
      flag_buffer = 1;
      break;
    }t_buffer[sz_buffer++] = c;
  }
  t_buffer[sz_buffer] = 13;
  if(flag_buffer){
      memset(comand, 0, sizeof comand);
      memcpy(comand, t_buffer, sizeof(char)*(sz_buffer));
      memset(t_buffer, 0, sizeof t_buffer);
      flag_buffer = sz_buffer = 0;
  }
}

void loop() {
  read_terminal();
}
