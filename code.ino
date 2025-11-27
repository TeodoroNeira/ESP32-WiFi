#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "XXXXXXXX";
const char* password = "XXXXXXXX";
const char* ubidotsToken = "XXXXXXX";
const char* deviceLabel = "esp32"; 

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Conectando no WiFi ...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    int rssi = WiFi.RSSI();
    unsigned long tempo = millis() / 1000; // tempo em segundos

    String url = "http://industrial.api.ubidots.com/api/v1.6/devices/";
    url += deviceLabel;

    String payload = "{\"rssi\":";
    payload += rssi;
    payload += ",\"tempo\":";
    payload += tempo;
    payload += "}";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Auth-Token", ubidotsToken);

    int httpResponseCode = http.POST(payload);

    Serial.print("Enviando para Ubidots: ");
    Serial.println(payload);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.println("WiFi desconectado!");
    initWiFi();
  }

  delay(3000); // envia a cada 3 segundos
}