#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Construtor para o ESP32-C3 Super Mini 0.42" (SCL=6, SDA=5)
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 6, /* data=*/ 5);

// Protótipo da função de desenho
void faceFeliz(bool piscando);

void setup() {
  Wire.begin(5, 6); 
  u8g2.begin();
}

void loop() {
  unsigned long tempoAtual = millis();

  u8g2.clearBuffer(); 

  // Mantém apenas a face feliz piscando
  // O cálculo (tempoAtual % 2500) < 250 faz o robô piscar por 250ms a cada 2.5 segundos
  faceFeliz((tempoAtual % 2500) < 250); 

  u8g2.sendBuffer(); 
  delay(30); // Pequena pausa para suavizar as transições e piscadas
}

// ==================== EXPRESSÃO DO ROBÔ ====================

// FELIZ (Estilo da imagem original com piscada automática)
void faceFeliz(bool piscando) {
  if (piscando) {
    // Olhos fechados (Linhas grossas)
    u8g2.drawHLine(17, 16, 11); u8g2.drawHLine(17, 17, 11);
    u8g2.drawHLine(45, 16, 11); u8g2.drawHLine(45, 17, 11);
  } else {
    // Olhos semicírculo para cima
    u8g2.drawFilledEllipse(22, 16, 5, 5, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
    u8g2.drawHLine(17, 16, 11);
    u8g2.drawFilledEllipse(50, 16, 5, 5, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
    u8g2.drawHLine(45, 16, 11);
  }
  // Boca semicírculo para baixo
  u8g2.drawFilledEllipse(36, 22, 3, 3, U8G2_DRAW_LOWER_RIGHT | U8G2_DRAW_LOWER_LEFT);
  u8g2.drawHLine(33, 22, 7);
}
face-ap
