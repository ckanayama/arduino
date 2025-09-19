#include <WiFiS3.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "arduino_secrets.h"
#include "weather_logic.h" 

// Open-Meteo APIの設定
const char server[] = "api.open-meteo.com";
const int port = 80;

// Wi-Fi設定
const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;
WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

// デジタルピン割り当て
SoftwareSerial softSerial(6,7); //RX (Receiver), TX (Transmitter)

// センサー設定
int ledPin = 13;
int inputPin = 2;
int val = 0;

// リクエストを過剰に送信しないための制御
unsigned long lastRequestTime = -300000;
const unsigned long requestInterval = 300000; // 5分 = 300,000 ミリ秒

// シリアル通信設定
void setup() {
  // Serial Monitor
  Serial.begin(9600);
  while (!Serial) {
    ; // USBシリアル接続が開くまで待つ
  }

  // Aquest TALK
  softSerial.begin(9600);
  softSerial.print("?");

  // Wi-Fi接続
  Serial.print("Connecting to WiFi...");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(1000);
    Serial.print("wifi status: ");
    Serial.println(WiFi.status());
  }
  Serial.println("connected!");
  
  delay(1000); // TCPスタックが安定するまで待機

  // センサー
  pinMode(inputPin, INPUT);  
}

void loop() {
  val = digitalRead(inputPin);
  unsigned long currentTime = millis();

  if (val == HIGH && (currentTime - lastRequestTime >= requestInterval)) {
    digitalWrite(ledPin, HIGH);

    // API用のパスを生成
    String path = "/v1/forecast?latitude=" + String(LATITUDE) +
                  "&longitude=" + String(LONGITUDE) +
                  "&daily=temperature_2m_max,temperature_2m_min,precipitation_sum" +
                  "&models=jma_seamless&timezone=Asia%2FTokyo" +
                  "&forecast_days=1";

    // APIリクエスト
    Serial.println("Sending request...");
    client.get(path);

    // APIレスポンスを受け取る
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();
    Serial.println("Status code: " + String(statusCode));

    // JSONパース
    JsonDocument doc;
    deserializeJson(doc, response);
    float tempMax = doc["daily"]["temperature_2m_max"][0].as<float>();
    float tempMin = doc["daily"]["temperature_2m_min"][0].as<float>();
    float precipitation = doc["daily"]["precipitation_sum"][0].as<float>();

    String comment = printWeatherAdvice(tempMax, tempMin, precipitation);

    softSerial.print("ohayougozaimasu. " + comment + "\r");

    lastRequestTime = currentTime;
  } else {
    digitalWrite(ledPin, LOW);
  }
}
