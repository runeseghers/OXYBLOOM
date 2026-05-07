#include <DHT.h>
#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int MQ_PIN = A0;
const int POT_PIN = A1;
const int BUTTON_PIN = 2;
const int knopMuziek = A2;
const int potVolume = A5;
