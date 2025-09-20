#pragma once // インクルードガード
#include <Arduino.h>

String printWeatherAdvice(float tempMax, float tempMin, float precipitation) {
  String tempComment = "";
  String precipitationComment = "";
  
  // 最高気温35℃以上
  if (tempMax >= 35.0) {
    tempComment = "kyo'-wa mousyobidesu. horeizaito,hi'gasawo,wasurezuni.";
  }
  // 最高気温30℃以上（猛暑日未満）
  else if (tempMax >= 30.0) {
    tempComment = "kyo'-wa manatubidesu horeizai,wo wasurezuni";
  } else if (tempMin <= 15.0) {
    tempComment = "kyo'-wa hadazamuidesu uwagi,wo wasurezuni";
  } else if (tempMin <= 10.0) {
    tempComment = "kyo'-wa totemosamuidesu boukangi,wo wasurezuni";
  } else {
    tempComment = "kyo'-wa sugosiyasui kiondesyou.";
  }

  // 降水確率0%
  if (precipitation <= 1.0) {
    precipitationComment = "sentakuwa yo'kukawakudesyou.";
  }
  else {
    precipitationComment = "sentakuwa heyabosi simasyou.";
  }

  return tempComment + " " + precipitationComment;
}
