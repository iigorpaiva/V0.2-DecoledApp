#include <NTPClient.h>

#include <WiFi.h>
#include "aWOT.h"
#include "StaticFiles.h"

#include <WiFiUdp.h>

#define WIFI_SSID "ISAIAS"
#define WIFI_PASSWORD "09068888"

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String horaAtual;
String dayStamp;
String timeStamp;

// definição das saídas dos LEDs
#define LED_1 26
#define LED_2 27

WiFiServer server(80);
Application app;

// circle slider dos leds (ou circuitos)
String led1;
String led2;

// circle slider da intensidade do ativador
String ledC;

// variaveis do controle: control (intervalos selecionados), controlback (intervalos para voltar para o render())
String control;
String controlback;

// variaveis do ativador
String compara;
String comparaHora;
bool continua = true;
bool novaSelecao = false;

///////////////////////////////////////////////// GETTERS DO SERVIDOR ///////////////////////////////////////////////////////////////////

void readLed1(Request &req, Response &res) {
  res.print(led1);
}

void readLed2(Request &req, Response &res) {
  res.print(led2);
}

void readLedC(Request &req, Response &res) {
  res.print(ledC);
}

void readControl(Request &req, Response &res) {
  res.print(controlback);
}

/////////////////////////////////////////////////  RESPOSTA DO SERVIDOR  /////////////////////////////////////////////////////////////////////


void updateLed1(Request &req, Response &res) {
  led1 = req.readString();
  Serial.println("LED 1: "+led1);
  
  if(led1 == "0")
    ledcWrite(1, 0); // 0%
  if(led1 == "20")
    ledcWrite(1, 51); // 20%
  if(led1 == "40")
    ledcWrite(1, 102); // 40%
  if(led1 == "60")
    ledcWrite(1, 153); // 60%
  if(led1 == "80")
    ledcWrite(1, 204); // 80%
  if(led1 == "10")
    ledcWrite(1, 255); // 100%
  return readLed1(req, res);
}

void updateLed2(Request &req, Response &res) {
  led2 = req.readString();
  Serial.println("LED 2: "+led2);
  
  if(led2 == "0")
    ledcWrite(2, 0); // 0%
  if(led2 == "20")
    ledcWrite(2, 51); // 20%
  if(led2 == "40")
    ledcWrite(2, 102); // 40%
  if(led2 == "60")
    ledcWrite(2, 153); // 60%
  if(led2 == "80")
    ledcWrite(2, 204); // 80%
  if(led2 == "100")
    ledcWrite(2, 255); // 100%
  return readLed2(req, res);
}

void updateLedC(Request &req, Response &res) {
  ledC = req.readString();
  Serial.println("LED de controle: "+ledC);
  
  return readLedC(req, res);
}

///////////////////////////////////////////////// CONFIGURAÇAO ATIVADOR //////////////////////////////////////////////////////////////////

void updateControl(Request &req, Response &res) {
  control = req.readString();
  controlback = control;
  
  // TRATAMENTO PARA LIMPAR A STRING JSON
  int tam = control.length();
  control.remove(tam-1, 1);
  control.remove(0, 1);

  for (int i=0; i  <control.length();++i){
    char c = control.charAt(i);
    if(c=='{'){
      control.remove(i, 1);
      i--;
    }
    if(c=='"')control.remove(i, 1);
    if(c=='}')control.remove(i, 1);
    if(c=='.')control.remove(i, 4);
    
  }
  
  Serial.println(control+" SELECIONADA");

  if(control.length()>0)
    control = control + ",";

  novaSelecao = true;
  
  return readControl(req, res);
}


///////////////////////////////////////////////// SETUP ESP32 //////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());

  app.get("/led1", &readLed1);
  app.get("/led2", &readLed2);
  app.get("/ledC", &readLedC);

  app.get("/control", &readControl);

  app.route(staticFiles());
  
  app.put("/led1", &updateLed1);
  app.put("/led2", &updateLed2);
  app.put("/ledC", &updateLedC);
  app.put("/control", &updateControl);

  server.begin();

  // Relaciona o canal 1 a ao LED_1 uma frequência de 5000MHZ a 8 bits
  ledcSetup(1, 5000, 8);
  ledcAttachPin(LED_1, 1);

  // Relaciona o canal 2 a ao LED_2 uma frequência de 5000MHZ a 8 bits
  ledcSetup(2, 5000, 8);
  ledcAttachPin(LED_2, 2);

  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  // GMT BRASIL = -10800
  timeClient.setTimeOffset(0);
  
}

///////////////////////////////////////////////// LOOP ESP32 ///////////////////////////////////////////////////////////////////

void loop() {
  WiFiClient client = server.available();

  if (client.connected())
    app.process(&client);

  if (!timeClient.update())
    timeClient.forceUpdate();
  horaAtual = timeClient.getFormattedDate();
  horaAtual.remove(13);

////////////////////////////////////////////////////////// ATIVADOR DO PAINEL DE CONTROLE ///////////////////////////////////////////////
  int tam = control.length();
  int r=0, t=0;

  for (int i=0; i < tam; i++){
    if( control.charAt(i) == ',' && (continua == true || novaSelecao == true)) {
      compara = control.substring(r, i);

      Serial.println(compara);
      delay(1000);
      
      r=(i+1); 
      t++;
    }
  }
  
  /*if(compara == horaAtual){
     ledcWrite(1, 255);
     ledcWrite(2, 255);
     continua = false;
     novaSelecao = false;
  }
  if(compara != horaAtual){
     ledcWrite(1, 0);
     ledcWrite(2, 0);
     continua = true;
  }*/

    
}

  
