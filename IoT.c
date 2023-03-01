#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

// Impostazioni WiFi
const char* ssid = "nome-rete-WiFi";
const char* password = "password-rete-WiFi";

// Impostazioni server
ESP8266WebServer server(80);
const int sensor_pin = A0;

void setup() {
  Serial.begin(115200);

  // Connessione alla rete WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione in corso...");
  }

  Serial.println("Connesso alla rete WiFi.");

  // Configurazione rotte dell'API RESTful
  server.on("/api/temperature", HTTP_GET, [](){
    // Leggi la temperatura dal sensore
    int sensor_value = analogRead(sensor_pin);
    float temperature = sensor_value * 0.48828125;

    // Costruisci la risposta JSON
    StaticJsonDocument<100> json;
    json["temperature"] = temperature;

    // Converti la risposta JSON in una stringa
    String json_string;
    serializeJson(json, json_string);

    // Invia la risposta JSON
    server.send(200, "application/json", json_string);
  });

  // Avvia il server
  server.begin();
  Serial.println("Server avviato.");
}

void loop() {
  // Gestisci le richieste HTTP
  server.handleClient();
}
