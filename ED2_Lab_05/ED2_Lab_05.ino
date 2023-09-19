/*
  Author: Gabriel Carrera 21216
  
  Electrónica Digital 2 - Laboratorio 5 
*/

//definir numero de pines
#define START 11

// ocho pines para jugador 2 - LEDs
#define LED1_J2 23
#define LED2_J2 24
#define LED3_J2 25
#define LED4_J2 26
#define LED5_J2 27
#define LED6_J2 28
#define LED7_J2 29
#define LED8_J2 10

// --------------- Variables ---------------
int stage; //variable para definir la etapa del juego
int bandera; //bandera para antirrebotes

int cont2; // variable para contador de j2

void setup() {
  stage = 0; //Inicializar en etapa 0, juego apagado
  bandera = 0; //Iniciar en 0 bandera

  pinMode(PUSH1, INPUT_PULLUP); //definir botón con pullup interno
  pinMode(PUSH2, INPUT_PULLUP); //definir botón con pullup interno
  
  //asignar leds como salidas
  pinMode(RED_LED, OUTPUT); 
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(PUSH1), start, LOW); //asignar interrupción a boton de iniciar carrera cuando el pin esté en bajo
  attachInterrupt(digitalPinToInterrupt(PUSH2), button2, LOW); //asignar interrupción a botón de jugador 2 cuando el pin esté en bajo
} 

void loop()  { 
  //Etapa 0 (Todo apagado, led en fade para indicar que esta idle)
  while(stage == 0){
    detachInterrupt(digitalPinToInterrupt(PUSH2)); //Deshabilitar interrupción de botón del jugador 2
    
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  }
  //Etapa 1 (Semaforo de inicializacion)
  while(stage == 1){
    cont2 = 0; //Reiniciar contador J2
    //Iniciar secuencia
    //Color ROJO
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    delay(1000); //delay de 1s
    //Color AMARILLO
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    delay(1000); //delay de 1s
    //Color VERDE
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(1000); //delay de 1s
    stage = 2;
  }
  //Etapa 2 (Inicio del juego)
  while(stage == 2){
    attachInterrupt(digitalPinToInterrupt(PUSH2), button2, LOW); //Habilitar interrupción al jugador 2
  }
  while(stage == 3){
    detachInterrupt(digitalPinToInterrupt(PUSH2)); //Habilitar interrupción al jugador 2
    if (cont2 == 8){ // SI GANA EL J2, ENCENDER LED DE TIVA EN AZUL
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    }
  }
}

//Función de interrupción del botón de inicio del juego
void start(){
  delay(5); //delay de 5ms
  bandera = 1; //encender bandera para antirrebote
  if (digitalRead(PUSH1) == HIGH && bandera == 1){ //Si ya se soltó el botón, ejecutar
    stage = 1;
 }
  bandera = 0; //limpiar bandera
}

//Función de interrupción del botón del jugador 2
void button2(){
  delay(5); //delay mínimo
  bandera = 2; //encender bandera para antirrebote
  if (digitalRead(PUSH2) == HIGH && bandera == 2){ //Si ya se soltó el botón, ejecutar
    if (cont2 == 0){
      //Leds si contador en 0
      digitalWrite(LED1_J2, HIGH);
      digitalWrite(LED2_J2, LOW);
      digitalWrite(LED3_J2, LOW);
      digitalWrite(LED4_J2, LOW);
      digitalWrite(LED5_J2, LOW);
      digitalWrite(LED6_J2, LOW);
      digitalWrite(LED7_J2, LOW);
      digitalWrite(LED8_J2, LOW);
      cont2 = 1; //Aumentar contador
    }
    else if (cont2 == 1){
      //Leds si contador en 1
      digitalWrite(LED1_J2, LOW);
      digitalWrite(LED2_J2, HIGH);
      digitalWrite(LED3_J2, LOW);
      digitalWrite(LED4_J2, LOW);
      digitalWrite(LED5_J2, LOW);
      digitalWrite(LED6_J2, LOW);
      digitalWrite(LED7_J2, LOW);
      digitalWrite(LED8_J2, LOW);
      cont2 = 2; //Aumentar contador
    }
    else if (cont2 == 2){
      //Leds si contador en 2
      digitalWrite(LED1_J2, LOW);
      digitalWrite(LED2_J2, LOW);
      digitalWrite(LED3_J2, HIGH);
      digitalWrite(LED4_J2, LOW);
      digitalWrite(LED5_J2, LOW);
      digitalWrite(LED6_J2, LOW);
      digitalWrite(LED7_J2, LOW);
      digitalWrite(LED8_J2, LOW);
      cont2 = 3; //Aumentar contador
    }
    else if (cont2 == 3){
      //Leds si contador en 3
      digitalWrite(LED1_J2, LOW);
      digitalWrite(LED2_J2, LOW);
      digitalWrite(LED3_J2, LOW);
      digitalWrite(LED4_J2, HIGH);
      digitalWrite(LED5_J2, LOW);
      digitalWrite(LED6_J2, LOW);
      digitalWrite(LED7_J2, LOW);
      digitalWrite(LED8_J2, LOW);
      cont2 = 4; //Aumentar contador
    }
    else if (cont2 == 4){
      //Leds si contador en 4
      digitalWrite(LED1_J2, LOW);
      digitalWrite(LED2_J2, LOW);
      digitalWrite(LED3_J2, LOW);
      digitalWrite(LED4_J2, LOW);
      digitalWrite(LED5_J2, HIGH);
      digitalWrite(LED6_J2, LOW);
      digitalWrite(LED7_J2, LOW);
      digitalWrite(LED8_J2, LOW);
      cont2 = 5; //Aumentar contador
    }
    else if (cont2 == 5){
      //Leds si contador en 5
      digitalWrite(LED1_J2, LOW);
      digitalWrite(LED2_J2, LOW);
      digitalWrite(LED3_J2, LOW);
      digitalWrite(LED4_J2, LOW);
      digitalWrite(LED5_J2, LOW);
      digitalWrite(LED6_J2, HIGH);
      digitalWrite(LED7_J2, LOW);
      digitalWrite(LED8_J2, LOW);
      cont2 = 6; //Aumentar contador
    }
    else if (cont2 == 6){
      //Leds si contador en 6
      digitalWrite(LED1_J2, LOW);
      digitalWrite(LED2_J2, LOW);
      digitalWrite(LED3_J2, LOW);
      digitalWrite(LED4_J2, LOW);
      digitalWrite(LED5_J2, LOW);
      digitalWrite(LED6_J2, LOW);
      digitalWrite(LED7_J2, HIGH);
      digitalWrite(LED8_J2, LOW);
      cont2 = 7; //Aumentar contador
    }
    else if (cont2 == 7){
      //Leds si contador en 7
      digitalWrite(LED1_J2, LOW);
      digitalWrite(LED2_J2, LOW);
      digitalWrite(LED3_J2, LOW);
      digitalWrite(LED4_J2, LOW);
      digitalWrite(LED5_J2, LOW);
      digitalWrite(LED6_J2, LOW);
      digitalWrite(LED7_J2, LOW);
      digitalWrite(LED8_J2, HIGH);
      cont2 = 8; //Aumentar contador
    }
    else if (cont2 == 8){ //Aumentar contador
      //Leds si contador en 8
      digitalWrite(LED1_J2, LOW);
      digitalWrite(LED2_J2, LOW);
      digitalWrite(LED3_J2, LOW);
      digitalWrite(LED4_J2, LOW);
      digitalWrite(LED5_J2, LOW);
      digitalWrite(LED6_J2, LOW);
      digitalWrite(LED7_J2, LOW);
      digitalWrite(LED8_J2, LOW);
      stage = 3; //Ganó, entonces cambiar etapa
      }
      bandera = 0; //Limpiar bandera
    }
  }
