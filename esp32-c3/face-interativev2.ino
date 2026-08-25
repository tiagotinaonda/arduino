#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Construtor para o ESP32-C3 Super Mini 0.42" (SCL=6, SDA=5)
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 6, /* data=*/ 5);

unsigned long tempoAnterior = 0;
const long intervalo = 5000; // Tempo de troca de expressão (5 segundos)
int estadoFace = 0;          // Controla a expressão atual

// Protótipos das funções de desenho
void faceFeliz(bool piscando);
void faceNeutro();
void faceTriste();
void faceSurpreso();

void setup() {
  Wire.begin(5, 6); 
  u8g2.begin();
}

void loop() {
  unsigned long tempoAtual = millis();

  // Alterna a expressão do robô a cada 5 segundos
  if (tempoAtual - tempoAnterior >= intervalo) {
    tempoAnterior = tempoAtual;
    estadoFace = (estadoFace + 1) % 4; // Rotaciona entre as 4 faces (0 a 3)
  }

  u8g2.clearBuffer(); 

  // Executa a animação correspondente ao estado atual
  switch (estadoFace) {
    case 0:
      // Modo Feliz: Pisca os olhos rapidamente usando o tempo atual do chip
      faceFeliz((tempoAtual % 2500) < 250); 
      break;
    case 1:
      faceNeutro();
      break;
    case 2:
      faceTriste();
      break;
    case 3:
      faceSurpreso();
      break;
  }

  u8g2.sendBuffer(); 
  delay(30); // Pequena pausa para suavizar as transições e piscadas
}

// ==================== EXPRESSÕES DO ROBÔ ====================

// 1. FELIZ (Estilo da imagem original com piscada automática)
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

// 2. NEUTRO / CALCULANDO (Olhos ovais retos e boca em traço curto)
void faceNeutro() {
  // Olhos em formato de pílula/oval vertical preenchida
  u8g2.drawDisc(22, 16, 4);
  u8g2.drawDisc(50, 16, 4);
  // Boca em traço reto
  u8g2.drawHLine(33, 23, 7);
}

// 3. TRISTE / BAIXA BATERIA (Olhos invertidos para baixo e sem boca)
void faceTriste() {
  // Olhos em semicírculo voltados para baixo (triste/cansado)
  u8g2.drawFilledEllipse(22, 16, 5, 5, U8G2_DRAW_LOWER_RIGHT | U8G2_DRAW_LOWER_LEFT);
  u8g2.drawHLine(17, 16, 11);
  u8g2.drawFilledEllipse(50, 16, 5, 5, U8G2_DRAW_LOWER_RIGHT | U8G2_DRAW_LOWER_LEFT);
  u8g2.drawHLine(45, 16, 11);
  // Boca em arco triste para cima (vazada)
  u8g2.drawCircle(36, 27, 4, U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
}

// 4. SURPRESO (Olhos redondos grandes e boca redonda)
void faceSurpreso() {
  // Olhos circulares totalmente preenchidos e maiores
  u8g2.drawDisc(22, 15, 5);
  u8g2.drawDisc(50, 15, 5);
  // Boca redonda pequena (formato de "O")
  u8g2.drawCircle(36, 24, 3);
}
