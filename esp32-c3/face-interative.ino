#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Construtor específico para o ESP32-C3 Super Mini 0.42" informando os pinos: (Rotação, Reset, Clock/SCL, Data/SDA)
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 6, /* data=*/ 5);

unsigned long tempoAnterior = 0;
const long intervalo = 5000; 
int estadoFace = 0;          

void desenhaFeliz(bool olhoAberto);
void desenhaNeutro();
void desenhaSurpreso();

void setup() {
  // Força o barramento I2C interno a iniciar nos pinos corretos da tela integrada (SDA=5, SCL=6)
  Wire.begin(5, 6); 
  u8g2.begin();
}

void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;
    estadoFace = (estadoFace + 1) % 3; 
  }

  u8g2.clearBuffer(); 

  // Como a tela de 0.42" usa uma janela menor dentro do driver, ajustamos as coordenadas X dos desenhos
  switch (estadoFace) {
    case 0:
      desenhaFeliz((tempoAtual % 2000) > 300); 
      break;
    case 1:
      desenhaNeutro();
      break;
    case 2:
      desenhaSurpreso();
      break;
  }

  u8g2.sendBuffer(); 
  delay(50);         
}

// --- Expressão 1: Feliz ---
void desenhaFeliz(bool olhoAberto) {
  if (olhoAberto) {
    u8g2.drawDisc(20, 12, 4); // Olho esquerdo (ajustado para esquerda)
    u8g2.drawDisc(48, 12, 4); // Olho direito (ajustado para direita)
  } else {
    u8g2.drawHLine(16, 12, 8); 
    u8g2.drawHLine(44, 12, 8); 
  }
  u8g2.drawCircle(34, 16, 10, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
}

// --- Expressão 2: Neutro ---
void desenhaNeutro() {
  u8g2.drawDisc(20, 14, 4);  
  u8g2.drawDisc(48, 14, 4);  
  u8g2.drawHLine(24, 28, 20); 
}

// --- Expressão 3: Surpreso ---
void desenhaSurpreso() {
  u8g2.drawCircle(20, 12, 5); 
  u8g2.drawDisc(20, 12, 2);   
  u8g2.drawCircle(48, 12, 5); 
  u8g2.drawDisc(48, 12, 2);   
  u8g2.drawCircle(34, 28, 4); 
}
