#include <NewPing.h> //Se importa la librería para controlar los sensores ultrasonido

//Pines del echo y trigger para todos los sensores ultrasonido
int tgr1 = 3;
int tgr2 = 4;
int tgr3 = 5;
int tgr4 = 6;
int tgr5 = 7;
int tgr6 = 8;

//Se define la distancia máxima que leerá el ultrasonido
int max_distance = 50;

//Se define un pin PWM para el buzzer
int pwmBuzzer=9;

//Pines final de carrera
int p1 = 10;
int p2 = 11;
int p3 = 12;
int p4 = 13;
int p5 = A0;
int p6 = A1;

//Estados de los final de carrera
int player1 = 0;
int player2 = 0;
int player3 = 0;
int player4 = 0;
int player5 = 0;
int player6 = 0;

//Pines modo de juego y reset

int btnMJ = 2;
int btnReset = A3;

//variable modo de juego
int modoJuego = 0;

//Variables para posiciones finales 
int usf1;
int usf2;
int usf3;
int usf4;
int usf5;
int usf6;

//Notas de GAME OVER
  String gameOver[] = {"do","sol","mi","la","si","la","sol#","la#","sol#","mi","re","mi",
                       "n","do","sol","mi","la","si","la","sol#","la#","sol#","mi","re","mi",
                       "n","do","sol","mi","la","si","la","sol#","la#","sol#","mi","re","mi",
                       "n","do","sol","mi","la","si","la","sol#","la#","sol#","mi","re","mi",
                       "n"};

//Contador para la música final
int notaActual = 0;                       

 
//Se Crean los objeto de la clase NewPing para cada ultrasonido*/
NewPing sonar1(tgr1, tgr1, max_distance);
NewPing sonar2(tgr2, tgr2, max_distance);
NewPing sonar3(tgr3, tgr3, max_distance);
NewPing sonar4(tgr4, tgr4, max_distance);
NewPing sonar5(tgr5, tgr5, max_distance);
NewPing sonar6(tgr6, tgr6, max_distance);
 
void setup() {
  //Se define la velocidad de trasmisión de datos en serie
  Serial.begin(9600);

  //Los pines para los sensores final de carrera se definen como inputs (incluyendo A0 y A1, que son 14 y 15 respectivamente);
  for(int x=10; x<=15;x++){
    pinMode(x, INPUT);
  } 
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  
}
 
void loop() {
  /*
   * Se especifican 3 modos de juegos:
   * Modo 0: etapa de ubicación de los personajes. En este modo solo se leen las posiciones de los sensores ultrasonido.
   * Modo 1: etapa de guerra. En este modo solo se leen los estados del final de carrera
   * Modo 2: etapa de finalización. En ese modo ya no se leen datos de los sensores; simplemente se reproduce la canción final a través del buzzer.
   * 
   * Las posiciones de los personajes varían de 0 a 50cm, relativos a la posición del sensor uS. En caso de que el sensor lea una distancia mayor, se devolverá un 0. 
   * 
   * Los estados de los personajes se declaran así:
   * Player_n = 0: Personaje vivo
   * Player_n  =  1:  Personaje muerto
   * 
   * En el puerto serial se escribe una línea de datos con la siguiente estructura:
   *  usf1, usf2, usf3, usf4, usf5, usf6, player1, player2, player3, player4, player5, player6, modoJuego
   * 
   */
  // Esperar 100ms  entre mediciones
  delay(100);
  //Se lee el estado del botón de jugadores listos
  int playersReady = digitalRead(btnMJ);
  //Se verifica si el botón de jugadores listos se ha pulsado. 
  if(playersReady == 1){
    //Si se pulsó el botón, se cambia al modo de juego 1
    modoJuego = 1;
    
  }
  //Se lee el estado del botón de reiniciar partida
  int reset = digitalRead(btnReset);
  //Se verifica si el botón de reiniciar partida se ha pulsado. 
  if(reset == 1){
    //Si se pulsó el botón, se cambia al modo de juego 0 y se reinician los valores de los estados de los personajes a 0.
    modoJuego = 0;
      player1 = 0;
      player2 = 0;
      player3 = 0;
      player4 = 0;
      player5 = 0;
      player6 = 0;
  }

  //Se verifica si uno de los jugadores ha derrotado a los 3 personajes enemigos. En tal caso, se pasa al modo de juego 2.
  if((player1 == 1 && player2 == 1 && player3 == 1) || (player4 == 1 && player5 == 1 && player6 == 1)){
    modoJuego = 2;
  }

  //Si se está en el modo de juego 0, se leen las distancias relativas de los personajes.
  if(modoJuego == 0){
  // Se obtiene la medición de tiempo de viaje del sonido se guarda en variables uS
  int uS1 = sonar1.ping_median();
  int uS2 = sonar2.ping_median();
  int uS3 = sonar3.ping_median();
  int uS4 = sonar4.ping_median();
  int uS5 = sonar5.ping_median();
  int uS6 = sonar6.ping_median();

  //Estos valores se almacenan en variables globales finales para tenerlos en caso de que se pase al modo de juego 1, en donde ya no se actualiza la distancia
  usf1 = uS1 / US_ROUNDTRIP_CM; // Calcular la distancia en cm. con base en una constante almacenada en una variable de la librería NewPing
  usf2 = uS2 / US_ROUNDTRIP_CM;
  usf3 = uS3 / US_ROUNDTRIP_CM;
  usf4 = uS4 / US_ROUNDTRIP_CM;
  usf5 = uS5 / US_ROUNDTRIP_CM;
  usf6 = uS6 / US_ROUNDTRIP_CM;

   // Imprimir los datos en la consola serial COM
    Serial.print(usf1); 
    Serial.print(",");
    Serial.print(usf2);
    Serial.print(",");
     Serial.print(usf3);
    Serial.print(",");
    Serial.print(usf4);
    Serial.print(",");
     Serial.print(usf5);
    Serial.print(",");
    Serial.print(usf6);
    Serial.print(",0,0,0,0,0,0,"); //Los estados de los personajes deberían ser, en este caso, cero para todos. No hay necesidad de leer los sensores. 
    Serial.print(modoJuego);
    Serial.println();

  //Si el modo de juego es 1, se leen los estados de cada sensor de carrera. 
  }else if(modoJuego == 1){
    //Debido a que los sensores están conectados a NC (normalmente cerrado), se debe esperar a que este valor sea cero para actualizar el estado de los personajes
    //Se lee el estado del sensor. Si este es 0, se actualiza el estado del personaje.
   if(digitalRead(p1) == 0){
    player1 = 1;
    }//Nótese que no existe un else, lo que significa que una vez se ha cambiado el estado del personaje a 1 (muerto), ya no puede volver al estado 0 (vivo), a menos que se reinicie el juego
  if(digitalRead(p2) == 0){
    player2 = 1;
    }
  if(digitalRead(p3) == 0){
    player3 = 1;
    }
  if(digitalRead(p4) == 0){
  player4 = 1;
    }
  if(digitalRead(p5) == 0){
    player5 = 1;
    }
  if(digitalRead(p6) == 0){
    player6 = 1;
    }
    //Escribir estos datos en el puerto COM
    Serial.print(usf1); //Nótese que las posiciones de los personajes ya no se actualizan, por lo que este dato será invariable durante modo de juego 1
    Serial.print(",");
    Serial.print(usf2);
    Serial.print(",");
     Serial.print(usf3);
    Serial.print(",");
    Serial.print(usf4);
    Serial.print(",");
     Serial.print(usf5);
    Serial.print(",");
    Serial.print(usf6);
    Serial.print(",");
    Serial.print(/*digitalRead(p1)*/player1);
    Serial.print(",");
    Serial.print(/*digitalRead(p2)*/player2);
    Serial.print(",");
    Serial.print(/*digitalRead(p3)*/player3);
    Serial.print(",");
    Serial.print(/*digitalRead(p4)*/player4);
    Serial.print(",");
    Serial.print(/*digitalRead(p5)*/player5);
    Serial.print(",");
    Serial.print(/*digitalRead(p6)*/player6);
    Serial.print(",");
    Serial.print(modoJuego);
    Serial.println();
  } //Si el modo de juego es 2, simplemente se reproduce la música final en bucle hasta que se reinicie el juego
  else if(modoJuego == 2){
    musicaFinal();
  }
  
}

//Método que lee las notas que van a ser reproducidads y las envía por parámetro al método sonido
void musicaFinal(){
  if(notaActual<=52){
    sonido(gameOver[notaActual]);
    delay(250); //Tiempo de espera entre notas
    notaActual++;
  }else{
    notaActual= 0;
    delay(2000); //tiempo de espera después de reproducir la canción completa
  }
  
  }
  
//Método que recibe un identificador de la nota a reproducir y la reproduce usando la función tone
void sonido(String nota){
  double frecuencia = 0; //frecuencia por defecto
  int duracion = 250; //duración por defecto
  //Cada nota tiene una frecuencian en Hz diferente
  if(nota.equals("do")){
    frecuencia = 261.625565;
  }else if(nota.equals("re")){
    frecuencia = 293.664768;
  }else if(nota.equals("mi")){
    frecuencia = 329.627557;
    duracion=300; //algunas notas tienen una mayor duración 
  }else if(nota.equals("fa")){
    frecuencia = 349.228231;
  }else if(nota.equals("sol")){
    frecuencia = 391.995436;
  }else if(nota.equals("la")){
    frecuencia = 440.000000;
  }else if(nota.equals("si")){
    frecuencia = 493.883301;
  }else if(nota.equals("sol#")){
    frecuencia = 415.000000;
  }else if(nota.equals("la#")){
    frecuencia = 466.000000;
  }else{
    frecuencia = 0;
  }
  tone(pwmBuzzer, frecuencia,duracion); //generates a square wave of the specified frequency (and 50% duty cycle) on a pin

}
