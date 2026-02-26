#include <Arduino.h>
#include <SPI.h>
#include <WiFiS3.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 12
#define CS_PIN 10

static uint8_t fontColon[] = { 1, 0x24 };

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const int sensorA = 2;
const int sensorB = 3;

unsigned long tempoA = 0;
unsigned long tempoB = 0;
constexpr int janelaTempo = 500;
bool estadoAnteriorA = HIGH;
bool estadoAnteriorB = HIGH;

 /// VARIAVEIS DE CONTROLE
int voltas = 0;
unsigned long tempoTotal = 0;
unsigned int tempoVolta = 0;
unsigned int somaTempoVoltas = 0;
bool corridaAtiva = false;
long treinoId = -1;

 /// FUNÇÕES
void lerSensores();
void atualizaDisplay();
void registraVolta();
void enviarVoltaParaAPI(long treinoId, unsigned int tempoVolta);

 /// CONFIGURAÇÕES DE REDE
char ssid[] = "nome_rede";
char pass[] = "senha";

IPAddress local_IP(192, 168, 1, 150);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

  // CONFIGURAÇÕES DA API
char server[] = "192.168.1.X";
int port = 8080;

WiFiServer serverLocal(80);
WiFiClient client;

void setup() {
   /// Inicia Sensores
  pinMode(sensorA, INPUT_PULLUP);
  pinMode(sensorB, INPUT_PULLUP);

   /// Inicia Displays
  P.begin(3);
  P.setZone(0, 0, 3);
  P.setZone(1, 4, 7);
  P.setZone(2, 8, 11);
  P.addChar(0, 58, fontColon);
  P.setIntensity(5);
  P.displayClear();

   /// Inicia a conexão com a rede
  Serial.begin(9600);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, pass);

  unsigned long timeout = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - timeout < 15000)) {
    delay(300);
  }

  if (WiFi.status() == WL_CONNECTED) {
    P.displayZoneText(2, "Ligado", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayZoneText(1, "ao", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayZoneText(0, "Wifi!!", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayAnimate();
    delay(3000);

    serverLocal.begin();

    P.displayClear();
    P.displayZoneText(1, "Aguardando inicio do treino pelo App...", PA_CENTER, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    timeout = millis();
    while (treinoId == -1 && (millis() - timeout < 60000)) {
      if (P.displayAnimate()) {
        if (P.getZoneStatus(1)) {
          P.displayReset(1);
        }
      }
      delay(20);

      WiFiClient appClient = serverLocal.available();
      if (appClient) {
        String request = appClient.readStringUntil('\r');
        int pos = request.indexOf("id=");
        if (pos != -1) {
          treinoId = request.substring(pos + 3, request.indexOf(" ", pos)).toInt();
        }
        appClient.println("HTTP/1.1 200 OK\r\n\r\nID OK");
        appClient.stop();
      }
    }
  }
  else {
    P.displayZoneText(2, "Falha", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayZoneText(1, "na:", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayZoneText(0, "conexão", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayAnimate();
    delay(3000);
  }

  if (treinoId != -1) {
    P.displayZoneText(2, "Modo de", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayZoneText(1, "treino:", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayZoneText(0, "Online", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayAnimate();
  }else {
    P.displayZoneText(2, "Modo de", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayZoneText(1, "treino:", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayZoneText(0, "offline", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
    P.displayAnimate();
  }


}

void loop() {
  lerSensores();
  atualizaDisplay();
}

void lerSensores() {
  bool leituraA = digitalRead(sensorA);
  bool leituraB = digitalRead(sensorB);

  if (leituraA == LOW && estadoAnteriorA == HIGH) {
   tempoA = millis();
  }

  if (leituraB == LOW && estadoAnteriorB == HIGH) {
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
    tempoAtual = (millis() - tempoTotal);
  }
  else {
    return;
  }

  unsigned int horas = (tempoAtual / 1000) / 60 / 60;
  unsigned int minutos = (tempoAtual / 1000) / 60 % 60;
  unsigned int segundos = (tempoAtual / 1000) % 60;

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
    tempoTotal = millis();
    corridaAtiva = true;
  }else {
    if (WiFi.status() == WL_CONNECTED && treinoId != -1) {
      unsigned int tempoVoltaAPI = (millis() - tempoTotal) - somaTempoVoltas * 1000;
      enviarVoltaParaAPI(treinoId, tempoVoltaAPI);
    }

    tempoVolta = (millis() - tempoTotal) / 1000 - somaTempoVoltas;
    somaTempoVoltas += tempoVolta;
    voltas++;
  }
}

void enviarVoltaParaAPI(long treinoId, unsigned int tempoVolta) {
  if (client.connect(server, port)) {
    String jsonData = "{\"tempoVolta\":" + String(tempoVolta) + "}";

    client.print("POST /treinos/");
    client.print(treinoId);
    client.println("/voltas HTTP/1.1");

    client.print("Host: "); client.println(server);
    client.println("Content-Type: application/json");
    client.print("Content-Length: "); client.println(jsonData.length());
    client.println("Connection: close");
    client.println();
    client.print(jsonData);
    client.stop();
    }
}
