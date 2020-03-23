#include <WiFi.h>
#include "aWOT.h"
#include "StaticFiles.h"

#include <NTPClient.h> // biblioteca NTP ( Network Time Protocol )

#define WIFI_SSID "ISAIAS"
#define WIFI_PASSWORD "09068888"

#define LED_1 26
#define LED_2 27

WiFiUDP udp;

NTPClient ntp(udp, "a.st1.ntp.br", -3 * 3600, 60000);//Cria um objeto "NTP" com as configurações.utilizada no Brasil 

String hora;            // Variável que armazena

WiFiServer server(80);
Application app;
String ledon1;
String ledon2;

void readLed1(Request &req, Response &res) {
  res.print(ledon1);
}

void readLed2(Request &req, Response &res) {
  res.print(ledon2);
}

void updateLed1(Request &req, Response &res) {
  char aux = req.read();
  Serial.println(aux);
  if(aux == '0')
    ledcWrite(1, 0); // 0%
  if(aux == '2')
    ledcWrite(1, 51); // 20%
  if(aux == '4')
    ledcWrite(1, 102); // 40%
  if(aux == '6')
    ledcWrite(1, 153); // 60%
  if(aux == '8')
    ledcWrite(1, 204); // 80%
  if(aux == '1')
    ledcWrite(1, 255); // 100%
  return readLed1(req, res);
}

void updateLed2(Request &req, Response &res) {
  char aux2 = req.read();
  Serial.println(aux2);
  if(aux2 == '0')
    ledcWrite(2, 0); // 0%
  if(aux2 == '2')
    ledcWrite(2, 51); // 20%
  if(aux2 == '4')
    ledcWrite(2, 102); // 40%
  if(aux2 == '6')
    ledcWrite(2, 153); // 60%
  if(aux2 == '8')
    ledcWrite(2, 204); // 80%
  if(aux2 == '1')
    ledcWrite(2, 255); // 100%
  return readLed1(req, res);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  app.get("/led1", &readLed1);
  app.get("/led2", &readLed2);


  app.route(staticFiles());
  
  app.put("/led1", &updateLed1);
  app.put("/led2", &updateLed2);

  server.begin();

  ledcSetup(1, 5000, 8);
  ledcAttachPin(LED_1, 1);

  ledcSetup(2, 5000, 8);
  ledcAttachPin(LED_2, 2);

  ntp.begin();           // Inicia o protocolo ntp
  ntp.forceUpdate();    // Atualização .

}

void loop() {
  WiFiClient client = server.available();

  if (client.connected()) {
    app.process(&client);
  }

  hora = ntp.getFormattedTime();  //Armazena na variável hora, o horário atual.
  Serial.println(hora);     // Escreve a hora no monitor serial.
}
