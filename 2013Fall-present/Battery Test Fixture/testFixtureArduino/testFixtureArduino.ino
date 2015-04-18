void setup(){
  Serial.begin(115200);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
}

char OPEN_COMMAND = '0';
char CLOSE_COMMAND = '1';

void loop(){  
  char readIn;
  while(1){
     readIn = (char)Serial.read();
     if(readIn==OPEN_COMMAND)
        digitalWrite(4,LOW);
     if(readIn==CLOSE_COMMAND)
        digitalWrite(4,HIGH);
  } 
}
