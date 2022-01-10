/* Jogo do Labirinto
 *  
 */

#include <Servo.h>          // Incluir biblioteca para o servo
#define START_BUTTON 2      // Botão de iniciar jogo definido no pino 2
#define BUZZER 13           // Buzzer  definido no pino 13

Servo servo_x;              // Servo do eixo X
Servo servo_y;              // Servo do eixo Y
int pot_x = A0;             // Pino onde o potenciômetro X é conectado
int pot_y = A1;             // Pino onde o potenciômetro Y é conectado
int val_x;                  // Variável para ler o pino analógico do eixo X
int val_y;                  // Variável para ler o pino analógico do eixo Y
int duracao;                // Variável com a duração do jogo

void setup() {
  servo_x.attach(9);        // Servo do Eixo X ligado no pino 9
  servo_y.attach(10);       // Servo do Eixo Y ligado no pino 10 
  pinMode(START_BUTTON, INPUT_PULLUP); // Botão de Iniciar no pino 2 definido como entrada e Pull-up interno
  pinMode(BUZZER, OUTPUT);  // Buzzer como saída no pino 13
  servo_x.write(90);        // Centraliza servo do X no centro
  servo_y.write(90);        // Centraliza servo do Y no centro 
}

void loop() {
  espera_iniciar();         // Chama a rotina para esperar botão iniciar ser apertado
  jogar();                  // Chama a rotina de jogar
}

void espera_iniciar(){
  while (digitalRead(START_BUTTON) == HIGH){  // Espera o botão ser presionado a cada 150 ms
    duracao = 60;                             // Define duração de jogo
    delay(150);                               // Espera 150 ms
  }
  tone(BUZZER, 1000, 250);                    // Se o botão foi pressionado toca o tom de inicio
}

void jogar(){
  unsigned long startTime = millis();
  unsigned long timer = 1000ul * duracao;
  while ((millis() - startTime) <= timer){    // Enquanto o tempo que passou não chega ao total de duração do jogo
    int elapsed = int((millis() - startTime)/1000); // Calcula o tempo que passou em ms
    val_x = analogRead(pot_x);                // Lê o valor do Potenciômetro X
    val_y = analogRead(pot_y);                // Lê o valor do Potenciômetro Y
    val_x = map(val_x, 0, 1023, 80, 100);     // Transforma o valor de 0 à 1023 em 70 à 110, valores dos ângulos do servo X
    val_y = map(val_y, 0, 1023, 80, 100);     // Transforma o valor de 0 à 1023 em 70 à 110, valores dos ângulos do servo Y
    servo_x.write(val_x);                     // Coloca o servo X na posição de acordo com o potenciômetro
    servo_y.write(val_y);                     // Coloca o servo Y na posição de acordo com o potenciômetro
    delay(15);                                // Espera 15 ms
    
    if (((millis() - startTime) > 30000) && ((millis() - startTime) < 30300)){ // Se passou 30 s toca um som
      tone(BUZZER, 600, 150);                 //
    }
    if (((millis() - startTime) > 45000) && ((millis() - startTime) < 45300)){ // Se passou 45 s toca um som
      tone(BUZZER, 700, 150);
    }
    if (((millis() - startTime) > 55000) && ((millis() - startTime) < 55300)){ // Se passou 55 s toca um som
      tone(BUZZER, 800, 150);
    }        
  }
  servo_x.write(90);        // Centraliza servo do X no centro
  servo_y.write(90);        // Centraliza servo do Y no centro
  tone(BUZZER, 2000, 1000); // Tempo acabou e toca tom de final
}
