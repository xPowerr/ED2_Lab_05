/*
  Author: Gabriel Carrera 21216
  
  Electrónica Digital 2 - Laboratorio 5 
*/

//definir numero de pines
#define START 12

// ocho pines para jugador 1 - LEDs
#define LED1_J1 23
#define LED2_J1 24
#define LED3_J1 25
#define LED4_J1 26
#define LED5_J1 27
#define LED6_J1 28
#define LED7_J1 29
#define LED8_J1 10

// ocho pines para jugador 2 - LEDs
#define LED1_J2 38
#define LED2_J2 37
#define LED3_J2 36
#define LED4_J2 35
#define LED5_J2 34
#define LED6_J2 33
#define LED7_J2 32
#define LED8_J2 11

// --------------- Variables ---------------
int stage; //variable para definir la etapa del juego
int bandera; //bandera para antirrebotes

int cont1; // variable para contador de j1
int cont2; // variable para contador de j2

void setup() {
  stage = 0; //Inicializar en etapa 0, juego apagado
  bandera = 0; //Iniciar en 0 bandera

  pinMode(START, INPUT_PULLUP); //definir botón con pullup interno
  pinMode(PUSH1, INPUT_PULLUP); //definir botón con pullup interno
  pinMode(PUSH2, INPUT_PULLUP); //definir botón con pullup interno
  
  //asignar leds como salidas
  pinMode(RED_LED, OUTPUT); 
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(LED1_J1, OUTPUT);
  pinMode(LED2_J1, OUTPUT);
  pinMode(LED3_J1, OUTPUT);
  pinMode(LED4_J1, OUTPUT);
  pinMode(LED5_J1, OUTPUT);
  pinMode(LED6_J1, OUTPUT);
  pinMode(LED7_J1, OUTPUT);
  pinMode(LED8_J1, OUTPUT);

  pinMode(LED1_J2, OUTPUT);
  pinMode(LED2_J2, OUTPUT);
  pinMode(LED3_J2, OUTPUT);
  pinMode(LED4_J2, OUTPUT);
  pinMode(LED5_J2, OUTPUT);
  pinMode(LED6_J2, OUTPUT);
  pinMode(LED7_J2, OUTPUT);
  pinMode(LED8_J2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(START), start, LOW); //asignar interrupción a boton de iniciar carrera cuando el pin esté en bajo
  attachInterrupt(digitalPinToInterrupt(PUSH1), button1, LOW); //asignar interrupción a botón de jugador 1 cuando el pin esté en bajo
  attachInterrupt(digitalPinToInterrupt(PUSH2), button2, LOW); //asignar interrupción a botón de jugador 2 cuando el pin esté en bajo
} 

void loop()  { 
  //Etapa 0 (Todo apagado, led en fade para indicar que esta idle)
  while(stage == 0){
    detachInterrupt(digitalPinToInterrupt(PUSH1)); //Deshabilitar interrupción de botón del jugador 1
    detachInterrupt(digitalPinToInterrupt(PUSH2)); //Deshabilitar interrupción de botón del jugador 2
    
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  }
  //Etapa 1 (Semaforo de inicializacion)
  while(stage == 1){
    cont1 = 0; //Reiniciar contador J1
    digitalWrite(LED1_J1, LOW);
    digitalWrite(LED2_J1, LOW);
    digitalWrite(LED3_J1, LOW);
    digitalWrite(LED4_J1, LOW);
    digitalWrite(LED5_J1, LOW);
    digitalWrite(LED6_J1, LOW);
    digitalWrite(LED7_J1, LOW);
    digitalWrite(LED8_J1, LOW);
    cont2 = 0; //Reiniciar contador J2
    digitalWrite(LED1_J2, LOW);
    digitalWrite(LED2_J2, LOW);
    digitalWrite(LED3_J2, LOW);
    digitalWrite(LED4_J2, LOW);
    digitalWrite(LED5_J2, LOW);
    digitalWrite(LED6_J2, LOW);
    digitalWrite(LED7_J2, LOW);
    digitalWrite(LED8_J2, LOW);
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
    // Apagar LED interno de TIVA
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    attachInterrupt(digitalPinToInterrupt(PUSH1), button1, LOW); //Habilitar interrupción al jugador 1
    attachInterrupt(digitalPinToInterrupt(PUSH2), button2, LOW); //Habilitar interrupción al jugador 2
  }
  while(stage == 3){
    detachInterrupt(digitalPinToInterrupt(PUSH1)); //Deshabilitar interrupción de botón del jugador 1
    detachInterrupt(digitalPinToInterrupt(PUSH2)); //Deshabilitar interrupción al jugador 2
    if (cont1 == 8){ // SI GANA EL J1, ENCENDER LED DE TIVA EN VERDE
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }
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
  if (digitalRead(START) == HIGH && bandera == 1){ //Si ya se soltó el botón, ejecutar
    stage = 1;
 }
  bandera = 0; //limpiar bandera
}

//Función de interrupción del botón del jugador 2
void button1(){
  delay(5); //delay mínimo
  bandera = 3; //encender bandera para antirrebote
  if (digitalRead(PUSH1) == HIGH && bandera == 3){ //Si ya se soltó el botón, ejecutar
    if (cont1 == 0){
      //Leds si contador en 0
      digitalWrite(LED1_J1, HIGH);
      digitalWrite(LED2_J1, LOW);
      digitalWrite(LED3_J1, LOW);
      digitalWrite(LED4_J1, LOW);
      digitalWrite(LED5_J1, LOW);
      digitalWrite(LED6_J1, LOW);
      digitalWrite(LED7_J1, LOW);
      digitalWrite(LED8_J1, LOW);
      cont1 = 1; //Aumentar contador
    }
    else if (cont1 == 1){
      //Leds si contador en 1
      digitalWrite(LED1_J1, LOW);
      digitalWrite(LED2_J1, HIGH);
      digitalWrite(LED3_J1, LOW);
      digitalWrite(LED4_J1, LOW);
      digitalWrite(LED5_J1, LOW);
      digitalWrite(LED6_J1, LOW);
      digitalWrite(LED7_J1, LOW);
      digitalWrite(LED8_J1, LOW);
      cont1 = 2; //Aumentar contador
    }
    else if (cont1 == 2){
      //Leds si contador en 2
      digitalWrite(LED1_J1, LOW);
      digitalWrite(LED2_J1, LOW);
      digitalWrite(LED3_J1, HIGH);
      digitalWrite(LED4_J1, LOW);
      digitalWrite(LED5_J1, LOW);
      digitalWrite(LED6_J1, LOW);
      digitalWrite(LED7_J1, LOW);
      digitalWrite(LED8_J1, LOW);
      cont1 = 3; //Aumentar contador
    }
    else if (cont1 == 3){
      //Leds si contador en 3
      digitalWrite(LED1_J1, LOW);
      digitalWrite(LED2_J1, LOW);
      digitalWrite(LED3_J1, LOW);
      digitalWrite(LED4_J1, HIGH);
      digitalWrite(LED5_J1, LOW);
      digitalWrite(LED6_J1, LOW);
      digitalWrite(LED7_J1, LOW);
      digitalWrite(LED8_J1, LOW);
      cont1 = 4; //Aumentar contador
    }
    else if (cont1 == 4){
      //Leds si contador en 4
      digitalWrite(LED1_J1, LOW);
      digitalWrite(LED2_J1, LOW);
      digitalWrite(LED3_J1, LOW);
      digitalWrite(LED4_J1, LOW);
      digitalWrite(LED5_J1, HIGH);
      digitalWrite(LED6_J1, LOW);
      digitalWrite(LED7_J1, LOW);
      digitalWrite(LED8_J1, LOW);
      cont1 = 5; //Aumentar contador
    }
    else if (cont1 == 5){
      //Leds si contador en 5
      digitalWrite(LED1_J1, LOW);
      digitalWrite(LED2_J1, LOW);
      digitalWrite(LED3_J1, LOW);
      digitalWrite(LED4_J1, LOW);
      digitalWrite(LED5_J1, LOW);
      digitalWrite(LED6_J1, HIGH);
      digitalWrite(LED7_J1, LOW);
      digitalWrite(LED8_J1, LOW);
      cont1 = 6; //Aumentar contador
    }
    else if (cont1 == 6){
      //Leds si contador en 6
      digitalWrite(LED1_J1, LOW);
      digitalWrite(LED2_J1, LOW);
      digitalWrite(LED3_J1, LOW);
      digitalWrite(LED4_J1, LOW);
      digitalWrite(LED5_J1, LOW);
      digitalWrite(LED6_J1, LOW);
      digitalWrite(LED7_J1, HIGH);
      digitalWrite(LED8_J1, LOW);
      cont1 = 7; //Aumentar contador
    }
    else if (cont1 == 7){
      //Leds si contador en 7
      digitalWrite(LED1_J1, LOW);
      digitalWrite(LED2_J1, LOW);
      digitalWrite(LED3_J1, LOW);
      digitalWrite(LED4_J1, LOW);
      digitalWrite(LED5_J1, LOW);
      digitalWrite(LED6_J1, LOW);
      digitalWrite(LED7_J1, LOW);
      digitalWrite(LED8_J1, HIGH);
      cont1 = 8; //Aumentar contador
    }
    else if (cont1 == 8){ //Aumentar contador
      //Leds si contador en 8
      digitalWrite(LED1_J1, LOW);
      digitalWrite(LED2_J1, LOW);
      digitalWrite(LED3_J1, LOW);
      digitalWrite(LED4_J1, LOW);
      digitalWrite(LED5_J1, LOW);
      digitalWrite(LED6_J1, LOW);
      digitalWrite(LED7_J1, LOW);
      digitalWrite(LED8_J1, LOW);
      stage = 3; //Ganó, entonces cambiar etapa
      }
      bandera = 0; //Limpiar bandera
    }
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
