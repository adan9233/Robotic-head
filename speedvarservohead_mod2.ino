#include <VarSpeedServo.h>
VarSpeedServo myservo1;
VarSpeedServo myservo2;
const int servoPin1 = 11;//define â€˜Servo Signal Pinâ€™
const int servoPin2 = 6;
const int trigPin = 10; //define â€˜Trigger Pinâ€™
const int echoPin = 12; //define â€˜Echo Pinâ€™

// define variables
long duration;
int distance;
int distanciaCalculada;
int pos_myservo1 = 0; // Variable para almacenar la posicion del servo
int pos_myservo2 = 0;
int pulsoMinimo = 580; // Para el servo que yo tengo esta me funciona
int pulsoMaximo = 2500;// Para el servo que yo tengo esta me funciona

int estado = LOW;


void setup() {
  pinMode(trigPin, OUTPUT); // Establece a â€˜trigPinâ€™ como Salida
  pinMode(echoPin, INPUT); // Establece a â€˜echoPinâ€™ como Entrada
  myservo1.attach(servoPin1, pulsoMinimo, pulsoMaximo); // Acopla al servo en el pin 9
  myservo2.attach(servoPin2, pulsoMinimo, pulsoMaximo);
  myservo1.write(20); /*Posicion inicial servo1 y servo2 cabeza arriba girada a la derecha*/
  myservo2.write(40);
  delay (2000);

  Serial.begin(9600); // Comienza la comunicacion serial
}

void loop() {

  distanciaCalculada = medirDistancia();

  if (distanciaCalculada < 50)
  { //Revision: que la distancia sea menos que 50cm
    myservo1.attach (servoPin1, pulsoMinimo, pulsoMaximo);
    myservo2.attach (servoPin2, pulsoMinimo, pulsoMaximo);
    myservo1.write(110, 30, true); /*Posicion 2 cabeza al frente inclinada hacia abajo*/
    myservo2.write(110, 30, true);
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    myservo1.detach();
    myservo2.detach();

    delay(2000);/*tiempo en que se mantiene la cabeza mirando hacia el frente*/



    for (int i = 0; i < 50; i++) { // el 50 son las veces que recorreremos este ciclo
      myservo1.attach (servoPin1, pulsoMinimo, pulsoMaximo);
      myservo1.write(20, 30, true); // Mover el servo hacia la posiciÃ³n 0 sin esperar a que termine de hacerlo
      myservo2.attach (servoPin2, pulsoMinimo, pulsoMaximo);
      myservo2.write(40, 30, true);
      distanciaCalculada = medirDistancia();
      
      if (distanciaCalculada < 50) { // Si la distancia se detectÃ³ <50
        myservo1.attach (servoPin1, pulsoMinimo, pulsoMaximo);
        myservo2.attach (servoPin2, pulsoMinimo, pulsoMaximo);
        myservo1.write(110, 30, true);
        myservo2.write(110, 30, true);
        digitalWrite(3,LOW);
        digitalWrite(2,HIGH);
         // enciende el LED.
         // retardo en milisegundosSerial.println(i);
        myservo1.detach();
        myservo2.detach();
        delay(2000);/*tiempo en que se mantiene la cabeza mirando hacia el frente*/
        i = 0; // Reiniciar el contador de este ciclo for
      }
      else { // Si no se detectÃ³ el obstÃ¡culo en el sensor continuar
        digitalWrite(2,LOW);
        digitalWrite(3,HIGH);
        
        //digitalWrite(3,LOW);
        //delay(25);
        Serial.println(i);
        delay(50);
      }
    }

    myservo1.detach();
    myservo2.detach();
    delay(500);
  }
}

///// FunciÃ³n para medir distancia con el sensor ultrasÃ³nico
int medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Establece a â€˜trigPinâ€™ en estado alto (HIGH) por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lectura del â€˜echoPinâ€™, retorna el tiempo de viaje de la onda ultrasonica en microsegundos
  duration = pulseIn(echoPin, HIGH);

  // Calculando la distancia
  distance = duration * 0.034 / 2;

  // Imprime la distancia en el monitor serial
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}
