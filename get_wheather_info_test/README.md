## 概要
天気予報APIからお天気情報を取得するテスト

## 部品
- Arduino UNO R4 WiFi

## 天気情報API
- Open-Meteo JMA API
https://open-meteo.com/en/docs/jma-api
- レスポンスサンプル
```json
{
  "latitude": 35.7,
  "longitude": 139.625,
  "generationtime_ms": 0.03910064697265625,
  "utc_offset_seconds": 32400,
  "timezone": "Asia/Tokyo",
  "timezone_abbreviation": "GMT+9",
  "elevation": 55.0,
  "daily_units": {
    "time": "iso8601",
    "temperature_2m_max": "°C",
    "temperature_2m_min": "°C",
    "precipitation_sum": "mm"
  },
  "daily": {
    "time": [
      "2025-08-30"
    ],
    "temperature_2m_max": [
      35.0
    ],
    "temperature_2m_min": [
      24.1
    ],
    "precipitation_sum": [
      0.00
    ]
  }
}
```

## Serial Monitor出力サンプル
```
00:37:01.801 -> Sending request...
00:37:03.836 -> Status code: 200
00:37:03.836 -> temperature_2m_max: 35.00
```

## 参考資料
- [Wi-Fiに接続する — SunFounder Elite Explorer Kit  ドキュメント](https://docs.sunfounder.com/projects/elite-explorer-kit/ja/latest/new_feature_projects/01_1_connect_to_wifi.html)
- [UNO R4 WiFi Network Examples | Arduino Documentation](https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/)
- [ArduinoHttpClient | Arduino Documentation](https://docs.arduino.cc/libraries/arduinohttpclient)
