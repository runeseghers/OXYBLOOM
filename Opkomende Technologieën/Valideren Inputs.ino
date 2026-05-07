#include <DHT.h>
#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int MQ_PIN = A0;
const int POT_PIN = A1;
const int BUTTON_PIN = 2;
const int knopMuziek = A2;
const int potVolume = A5;

bool knop1Getest = false;
bool knop2Getest = false;
bool pot1Getest = false;
bool pot2Getest = false;

void loop() {

  // knop 1
  if (!knop1Getest) {
    Serial.println("");
    Serial.println("DRUK OP KNOP 1");

    while (digitalRead(BUTTON_PIN) == HIGH) {
    }

    Serial.println("KNOP 1 WERKT");
    knop1Getest = true;

    delay(1000);
  }


  // knop 2
  if (!knop2Getest) {
    Serial.println("");
    Serial.println("DRUK OP KNOP 2");

    while (digitalRead(knopMuziek) == HIGH) {
    }

    Serial.println("KNOP 2 WERKT");
    knop2Getest = true;

    delay(1000);
  }