#include <WiFi.h>
#include "aWOT.h"
#include "StaticFiles.h"
#include <EEPROM.h>

#include <NTPClient.h> // biblioteca NTP ( Network Time Protocol )

#define WIFI_SSID "ISAIAS"
#define WIFI_PASSWORD "09068888"

// definição das saídas dos LEDs

#define LED_1 26
#define LED_2 27

WiFiUDP udp;

NTPClient ntp(udp, "a.st1.ntp.br", -3 * 3600, 60000);//Cria um objeto "NTP" com as configurações.utilizada no Brasil 

String hora;  // Variável que armazena a hora atual

String horaInicio;
String horaFinal;

WiFiServer server(80);
Application app;

String led1;
String led2;
String time1;
String time2;

void readLed1(Request &req, Response &res) {
  res.print(led1);
}

void readLed2(Request &req, Response &res) {
  res.print(led2);
}

void readTime1(Request &req, Response &res) {
  res.print(time1);
}

void readTime2(Request &req, Response &res) {
  res.print(time2);
}

void updateLed1(Request &req, Response &res) {
  led1 = req.readString();
  Serial.println(led1);
  
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
  Serial.println(led2);
  
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


///////////////////////////////////////////////// CONFIGURAÇAO ALARME //////////////////////////////////////////////////////////////////

void updateTime1(Request &req, Response &res) {
  time1 = req.readString();
  horaInicio = time1+":00";
     
  Serial.println("hora inicio: "+ horaInicio);
  
  return readTime1(req, res);
}


void updateTime2(Request &req, Response &res) {
  time2 = req.readString();
  horaFinal = time2+":00";

  Serial.println("hora final: "+ horaFinal);
  return readTime2(req, res);
}

///////////////////////////////////////////////// SETUP ESP32 //////////////////////////////////////////////////////////////////

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

  app.get("/time1", &readTime1);
  app.get("/time2", &readTime2);

  app.route(staticFiles());
  
  app.put("/led1", &updateLed1);
  app.put("/led2", &updateLed2);

  app.put("/time1", &updateTime1);
  app.put("/time2", &updateTime2);

  server.begin();

  // Relaciona o canal 1 a ao LED_1 uma frequência de 5000MHZ a 8 bits
  ledcSetup(1, 5000, 8);
  ledcAttachPin(LED_1, 1);

  // Relaciona o canal 2 a ao LED_2 uma frequência de 5000MHZ a 8 bits
  ledcSetup(2, 5000, 8);
  ledcAttachPin(LED_2, 2);

  // Inicia o protocolo ntp
  ntp.begin();           
  ntp.forceUpdate();    // Atualização .

}

///////////////////////////////////////////////// LOOP ESP32 ///////////////////////////////////////////////////////////////////

void loop() {
  WiFiClient client = server.available();

  if (client.connected())
    app.process(&client);

  hora = ntp.getFormattedTime();  //Armazena na variável hora, o horário atual.
  //Serial.println(horaInicio);
  //Serial.println(hora);
  //delay(1000);
  
  if (hora == horaInicio){ 
    ledcWrite(1, 255);
    Serial.println("LED SALA ACESO");
  }

  if (hora == horaFinal){
    ledcWrite(1, 0);
    Serial.println("LED SALA APAGADO");
  }
  
}
