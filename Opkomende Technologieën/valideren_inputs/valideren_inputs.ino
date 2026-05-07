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


void setup() {

 Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(knopMuziek, INPUT_PULLUP);

  dht.begin();

  Serial.println("INPUT VALIDATIE");
  delay(1000);

  // dht sensor
  float humidity = dht.readHumidity();

  Serial.println("");
  Serial.println("DHT11 TEST");

  if (!isnan(humidity)) {
    Serial.print("Vochtigheid: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.println("DHT11 WERKT");
  } else {
    Serial.println("DHT11 FOUT");
  }

  delay(1500);

  // mq sensor
  int mq = analogRead(MQ_PIN);

  Serial.println("");
  Serial.println("MQ SENSOR TEST");

  Serial.print("Gemeten waarde: ");
  Serial.println(mq);

  if (mq > 0) {
    Serial.println("MQ SENSOR WERKT");
  } else {
    Serial.println("MQ SENSOR FOUT");
  }

  delay(1500);

  Serial.println("");
  Serial.println("START MANUELE TESTS");
}


void loop() {

  // knop 1
  if (!knop1Getest) {
    Serial.println("");
    Serial.println("DRUK OP KNOP 1");

    while (digitalRead(BUTTON_PIN) == HIGH) {
    }

    Serial.println("KNOP 1 WERKT");
    knop1Getest = true;

    delay(1500);
  }


  // knop 2
  if (!knop2Getest) {
    Serial.println("");
    Serial.println("DRUK OP KNOP 2");

    while (digitalRead(knopMuziek) == HIGH) {
    }

    Serial.println("KNOP 2 WERKT");
    knop2Getest = true;

    delay(1500);
  }

  // potmeter 1
  if (!pot1Getest) {
    Serial.println("");
    Serial.println("DRAAI AAN POTMETER HELDERHEID");

    int startWaarde = analogRead(POT_PIN);

    while (abs(analogRead(POT_PIN) - startWaarde) < 50) {
    }

    Serial.println("POTMETER HELDERHEID WERKT");
    pot1Getest = true;

    delay(1500);
  }

  // potmeter 2
  if (!pot2Getest) {
    Serial.println("");
    Serial.println("DRAAI AAN POTMETER VOLUME");

    int startWaarde = analogRead(potVolume);

    while (abs(analogRead(potVolume) - startWaarde) < 50) {
    }

    Serial.println("POTMETER VOLUME WERKT");
    pot2Getest = true;

    delay(1500);
  }
    if (knop1Getest && knop2Getest && pot1Getest && pot2Getest) {

    Serial.println("");
    Serial.println("ALLE INPUTS WERKEN");
    while(true);
    
}
}