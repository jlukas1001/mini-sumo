#include "receptorRc.h"

#include <IBusBM.h>
IBusBM IBus;

#define STANDBY 6

#define MOTOR1A 4
#define MOTOR1B 5
#define PWM1 3

#define MOTOR2A 7
#define MOTOR2B 8
#define PWM2 9

void inicioReceptorYMotores(){
  IBus.begin(Serial);
  //Serial.begin(9600);

  pinMode(MOTOR1A, OUTPUT);
  pinMode(MOTOR1B, OUTPUT);
  pinMode(MOTOR2A, OUTPUT);
  pinMode(MOTOR2B, OUTPUT);
  pinMode(STANDBY, OUTPUT);
  digitalWrite(STANDBY,HIGH);

  delay(500);

  while(IBus.readChannel(1) <= 1000){
    //Serial.println("Esperando conexion");
    delay(10);
  }
  delay(100);
  
}

int velocidadIzq, velocidadDer;
int valCh3;

void recibirDatos()
 {
  int valCh1 = map(IBus.readChannel(1), 1000, 2000, 255, 0);
  int valCh5 = map(IBus.readChannel(5), 1000, 2000, 255, 0);
  
  int sensibilidad = valCh5 * 8;
  int valCh3 = map(IBus.readChannel(3), 1000-sensibilidad, 2000+sensibilidad, 0, 255);



  if(valCh1 > 127){
    int vel = map(valCh1,128,255,0,255);
    
    velocidadIzq = vel;
    velocidadDer = vel;
    
    digitalWrite(MOTOR1A,HIGH);  
    digitalWrite(MOTOR1B,LOW);  
    
    digitalWrite(MOTOR2A,HIGH);  
    digitalWrite(MOTOR2B,LOW); 
  }
  if(valCh1 < 127){
    int vel = map(valCh1,126,0,0,255);
    
    velocidadIzq = vel;
    velocidadDer = vel;
    
    digitalWrite(MOTOR1A,LOW);  
    digitalWrite(MOTOR1B,HIGH);  
    
    digitalWrite(MOTOR2A,LOW);  
    digitalWrite(MOTOR2B,HIGH);     
  }


  if(valCh3 > 127){
    int vel = map(valCh3,128,255,0,velocidadIzq);
    velocidadIzq = velocidadIzq - vel;
  }
  if(valCh3 < 127){
    int vel = map(valCh3,126,0,0,velocidadDer);
    velocidadDer = velocidadDer - vel;
  }

  analogWrite(PWM1,velocidadIzq);
  analogWrite(PWM2,velocidadDer);

/*
  Serial.print("Velocidad = ");
  Serial.print( "(");
  Serial.print(velocidadIzq);    
  Serial.print(", ");
  Serial.print(velocidadDer);
  Serial.println(")");
*/
  delay(10);
}
