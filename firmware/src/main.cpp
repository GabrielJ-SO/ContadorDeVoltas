#include <Arduino.h>
#include <SPI.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 12
#define CS_PIN 10

static uint8_t fontColon[] = { 1, 0x24 };

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const int sensorA = 2;
const int sensorB = 3;

unsigned long tempoA = 0;
unsigned long tempoB = 0;
constexpr int janelaTempo = 300;
bool estadoAnteriorA = LOW;
bool estadoAnteriorB = LOW;

int voltas = 0;
unsigned long tempoInicial = 0;
unsigned int tempoVolta = 0;
unsigned int tempoVoltaPassada = 0;
bool corridaAtiva = false;

 /// Funções
void lerSensores();
void atualizaDisplay();
void registraVolta();

void setup() {
  pinMode(sensorA, INPUT_PULLUP);
  pinMode(sensorB, INPUT_PULLUP);

  P.begin(3);
  P.setZone(0, 0, 3);
  P.setZone(1, 4, 7);
  P.setZone(2, 8, 11);
  P.addChar(0, 58, fontColon);
  P.setIntensity(5);
  P.displayClear();
}

void loop() {
  lerSensores();
  atualizaDisplay();
}

void lerSensores() {
  bool leituraA = digitalRead(sensorA);
  bool leituraB = digitalRead(sensorB);

  if (leituraA == HIGH && estadoAnteriorA == LOW) {
   tempoA = millis();
  }

  if (leituraB == HIGH && estadoAnteriorB == LOW) {
    tempoB = millis();
  }

  if (tempoA > 0 && tempoB > 0) {
    long diferenca = abs((long)tempoA - (long)tempoB);
    if (diferenca < janelaTempo) {
      registraVolta();
      tempoA = 0;
      tempoB = 0;

    }
  }
  estadoAnteriorA = leituraA;
  estadoAnteriorB = leituraB;
}

void atualizaDisplay() {
  unsigned long tempoAtual = 0;
  if (corridaAtiva) {
    tempoAtual = (millis() - tempoInicial) / 1000;
  }
  else {
    return;
  }

  unsigned int horas = (tempoAtual / 60) / 60;
  unsigned int minutos = (tempoAtual / 60) % 60;
  unsigned int segundos = tempoAtual % 60;

  char bufferTempo[20];
  char bufferVoltas[20];
  char bufferTempoVolta[20];

  sprintf(bufferTempo, "%d:%02d:%02d", horas, minutos, segundos);
  sprintf(bufferVoltas, "V: %d", voltas);

  minutos = tempoVolta / 60;
  segundos = tempoVolta % 60;
  sprintf(bufferTempoVolta, "%02d:%02d", minutos, segundos);

  P.displayZoneText(0, bufferTempo, PA_LEFT, 0, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(2, bufferVoltas, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(1, bufferTempoVolta, PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);

  P.displayAnimate();

}

void registraVolta() {
  if (!corridaAtiva) {
    tempoInicial = millis();
    corridaAtiva = true;
  }else {
    tempoVolta = (millis() - tempoInicial) / 1000 - tempoVoltaPassada;
    tempoVoltaPassada += tempoVolta;
    voltas++;
  }
}