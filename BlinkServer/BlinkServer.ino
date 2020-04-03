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


///////////////////////////////////////////////// VARIAVEIS GLOBAIS ////////////////////////////////////////////////////////

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

// toggles
bool ledon1;
bool ledon2;

// variaveis do controle: control (intervalos selecionados), controlback (intervalos para voltar para o render())
String control;
String controlback;

// variaveis do ativador
String compara;
String comparaHora;
bool continua = true;
int auxC;

int auxL1 = 0;
int auxL2 = 0;

///////////////////////////////////////////////// GETTERS DO SERVIDOR ///////////////////////////////////////////////////////////////////

void readLedOn1(Request &req, Response &res) {
  res.print(ledon1);
}

void readLedOn2(Request &req, Response &res) {
  res.print(ledon2);
}

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

void updateLedOn1(Request &req, Response &res) {
  ledon1 = (req.read() != '0');
  return readLedOn1(req, res);
}

void updateLedOn2(Request &req, Response &res) {
  ledon2 = (req.read() != '0');
  return readLedOn2(req, res);
}

void updateLed1(Request &req, Response &res) {
  led1 = req.readString();
  Serial.println("LED 1: "+led1);
  
  if(led1 == "0" && (continua == true || ledon1 == false) ){
    ledcWrite(1, 0); // 0%
    auxL1 = 0;
  }
  if(led1 == "20" && (continua == true || ledon1 == false)){
    ledcWrite(1, 51); // 20%
    auxL1 = 51;
  }
  if(led1 == "40" && (continua == true || ledon1 == false)){
    ledcWrite(1, 102); // 40%
    auxL1 = 102;
  }
  if(led1 == "60" && (continua == true || ledon1 == false)){
    ledcWrite(1, 153); // 60%
    auxL1 = 153;
  } 
  if(led1 == "80" && (continua == true || ledon1 == false)){
    ledcWrite(1, 204); // 80%
    auxL1 = 204;
  }
  if(led1 == "10" && (continua == true || ledon1 == false)){
    ledcWrite(1, 255); // 100%
    auxL1 = 255;
  }
  return readLed1(req, res);
}

void updateLed2(Request &req, Response &res) {
  led2 = req.readString();
  Serial.println("LED 2: "+led2);
  
  if(led2 == "0" && (continua == true || ledon1 == false)){
    ledcWrite(2, 0); // 0%
    auxL2 = 0;
  }
  if(led2 == "20" && (continua == true || ledon1 == false)){
    ledcWrite(2, 51); // 20%
    auxL2 = 51;
  }
  if(led2 == "40" && (continua == true || ledon1 == false)){
    ledcWrite(2, 102); // 40%
    auxL2 = 102;
  }
  if(led2 == "60" && (continua == true || ledon1 == false)){
    ledcWrite(2, 153); // 60%
    auxL2 = 153;
  }
  if(led2 == "80" && (continua == true || ledon1 == false)){
    ledcWrite(2, 204); // 80%
    auxL2 = 204;
  }
  if(led2 == "100" && (continua == true || ledon1 == false)){
    ledcWrite(2, 255); // 100%
    auxL2 = 255;
  }
  return readLed2(req, res);
}

void updateLedC(Request &req, Response &res) {
  ledC = req.readString();
  Serial.println("LED de controle: "+ledC);

  if(ledC == "0")
    auxC = 0; // 0%
  if(ledC == "20")
    auxC = 51; // 20%
  if(ledC == "40")
    auxC = 102; // 40%
  if(ledC == "60")
    auxC = 153; // 60%
  if(ledC == "80")
    auxC = 204; // 80%
  if(ledC == "100")
    auxC = 255; // 100%
  
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

  continua = true;
  
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
  app.get("/ledon1", &readLedOn1);
  app.get("/ledon2", &readLedOn2);
  app.get("/control", &readControl);

  app.route(staticFiles());
  
  app.put("/led1", &updateLed1);
  app.put("/led2", &updateLed2);
  app.put("/ledC", &updateLedC);
  app.put("/control", &updateControl);
  app.put("/ledon1", &updateLedOn1);
  app.put("/ledon2", &updateLedOn2);

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
  // USAMOS GMT 0 PARA SINCRONIZAR COM O COMPONENTE SCHEDULE DO REACT
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

if(compara != horaAtual || compara == "" || tam<1 )
  continua = true;
  
if(continua == true){
  for (int i=0; i < tam; i++){
    if( control.charAt(i) == ',' && continua == true) {
      compara = control.substring(r, i);
      comparaHora = control.substring(0, 13);
      
      compara.remove(13);

      //Serial.println(compara);
      //delay(1000);
    
      r=(i+1); 
      t++;

      
      if(compara == horaAtual){
        if(ledon1 == 1)
          ledcWrite(1, auxC);
        if(ledon1 == 0)
          ledcWrite(1, auxL1);
        if(ledon2 == 1)
          ledcWrite(2, auxC);
        if(ledon2 == 0)
          ledcWrite(2, auxL2);
        continua=false;
        Serial.println("CONTROLE ATIVADO");
      }
      if(compara != horaAtual || compara == "" || tam<1 ){ 
          ledcWrite(1, auxL1);
          ledcWrite(2, auxL2);
        continua=true;
        Serial.println("CONTROLE DESATIVADO");
      }
      
    }
  }
}

  /*if(compara == horaAtual)
    continua = false;
  if(compara != horaAtual)
    continua = true;*/
  
    
}

  
