
/*
 * UNIVERSIDAD TECNICA DEL NORTE
 * FACULTAD DE INGENIERIA EN CIENCIAS APLICADAS
 * SISTEMAS EMBEBIDOS
 * STEVEN FLORES
 * 5to Nivel; 
 * Laboratorio 2:
 */
#include <MsTimer2.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd (13,12,11,10,9,8);
const int led1=8; //led en pin8
const int leds [4]={4,5,6,7};
const int sensor1 = A2;
const int sensor2 = A3;
const int sensor3 = A4;
const int sensor4 = A5;
int aux1=0;
int aux2=0;
int minutos=0;
int horas=0;
int i;
int random1;
int horap;
int minutop;
void setup() {
  for(i=0;i<6;i++){
    pinMode(leds[i],OUTPUT);
  }
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);
  i=0;
  Serial.begin(9600);
  lcd.begin(16,2);
  attachInterrupt(0,modo,LOW);
  attachInterrupt(1,juego,LOW);
  MsTimer2::set(1000,reloj);
  Serial.println("Presione para encender el sistema");
}

void loop() {
  if(aux1==2){
    switch(aux2){
      case 1:
      modo1();
      break;
      case 2:
      modo2();
      break;
      case 3:
      modo3();
      break;
    }
  }
}

void modo(){
  switch(aux1){
    case 0:
    MsTimer2::start();
    Serial.println("Seleccione un modo mediante boton");
    aux1++;
    break;
    case 1:
    Serial.println("Iniciando opcion elegida");
    aux1++;
    break;
    case 2:
    Serial.println("Apagado del sistema");
    aux1=0;
    aux2=0;
    lcd.clear();
    MsTimer2::stop();
  }
}

void juego(){
  if(aux1==1){
    switch(aux2){
      case 0:
      Serial.println("Activacion luces de forma aleatoria");
      aux2++;
      break;
      case 1:
      Serial.println("Cambio de hora de reloj");
      aux2++;
      break;
      case 2:
      Serial.println("Sistema de seguridad de sensores");
      aux2++;
      break;
      case 3:
      Serial.println("Seleccion de modos");
      aux2=0;
      break;
    }
  }
  if(aux1==2){
      aux1=0;
      aux2=0;
      Serial.println("Salio del modo");
    }
}
void modo1(){
  for(i=0;i<5;i++){
    random1=random(1,5);
    digitalWrite(leds[random1],HIGH);
    delay(200);
    digitalWrite(leds[random1],LOW);
    delay(200);
  }
  i=0;
  aux1=0;
  aux2=0;
}
void modo2(){
  horap=analogRead(0);
  horas=map(horap,0,1023,0,23);
  minutop=analogRead(1);
  minutos=map(minutop,0,1023,0,59);
}
void modo3(){
  if(digitalRead(sensor1)==HIGH||digitalRead(sensor2)==HIGH||digitalRead(sensor3)==HIGH||digitalRead(sensor4)==HIGH){
    Serial.println("Un sensor ha sido activado, verifique la seguridad");
    delay(200);
  }
}
void reloj(){
  if(minutos<59){
    minutos++;
  }else{
    minutos=0;
    if(horas<23){
      horas++;
    }else{
      horas=0;
     }
   }
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Reloj: ");
   lcd.setCursor(8,0);
   lcd.print(String(horas)+String(":")+String(minutos));   
}
