#include <WiFiS3.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "arduino_secrets.h"

// Wi-Fi設定
const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;

// Open-Meteo APIの設定
const char server[] = "api.open-meteo.com";
const int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // USBシリアル接続が開くまで待つ
  }

  // Wi-Fi接続
  Serial.print("Connecting to WiFi...");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
    Serial.print("wifi status: ");
    Serial.println(WiFi.status());
  }
  Serial.println("connected!");
  
  delay(1000); // TCPスタックが安定するまで待機

  // API用のパスを生成（LATITUDE, LONGITUDE を利用）
  String path = "/v1/forecast?latitude=" + String(LATITUDE) +
                "&longitude=" + String(LONGITUDE) +
                "&daily=temperature_2m_max,temperature_2m_min,precipitation_sum" +
                "&models=jma_seamless&timezone=Asia%2FTokyo" +
                "&forecast_days=1";

  // APIへリクエスト
  Serial.println("Sending request...");
  client.get(path);

  // レスポンスを受け取る
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  // JSONパース
  JsonDocument doc;
  deserializeJson(doc, response);

  Serial.println("Status code: " + String(statusCode));
  Serial.println("temperature_2m_max: " + String(doc["daily"]["temperature_2m_max"][0].as<float>()));
}

void loop() {
  // 今回は一度だけ実行
}
