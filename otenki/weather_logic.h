#pragma once // インクルードガード
#include <Arduino.h>

String printWeatherAdvice(float tempMax, float tempMin, float precipitation) {
  String tempComment = "";
  String precipitationComment = "";
  
  // 最高気温35℃以上
  if (tempMax >= 35.0) {
    tempComment = "kyouha mousyobi desu. horeizai to higasa wo wasurezuni.";
  }
  // 最高気温30℃以上（猛暑日未満）
  else if (tempMax >= 30.0) {
    tempComment = "kyouha manatubi desu. horeizai wo wasurezuni.";
  }

  // 降水確率0%
  if (precipitation == 0.0) {
    precipitationComment = "sentakuha yokukawakudesyou.";
  }
  else if (precipitation <= 1.0) {
    precipitationComment = "sentakuha yokukawakudesyou.";
  }
  else {
    precipitationComment = "sentakuha heyabosi simasyou.";
  }

  return tempComment + " " + precipitationComment;
}
