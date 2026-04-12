#include <Stepper.h>
#include <DHT.h>

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int MQ_PIN = A0;
const int POT_PIN = A1;
const int BUTTON_PIN = 2;
//KALIBRATIE 
const float RO_SCHONE_LUCHT = 69.0; // gemeten waarde bij schone lucht
const int redPin = 5;
const int greenPin = 6;

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// Positie 0 = startpunt, Positie 1 = andere kant
int Positie = 0; 
// knipperen
unsigned long vorigeTijd = 0;
const long interval = 500; 
bool ledStatus = false;
bool systeemAan = true;      
bool laatsteKnopStaat = LOW;

SoftwareSerial mySoftwareSerial(4, 7);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;
const int knopPin = A2;
const int potPin = A5;
bool laatstStatus = HIGH;
int laatsteVolume = -1;

void setup() {
  myStepper.setSpeed(5); //snelheid nog verlaagd
  Serial.begin(9600);
  dht.begin();
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // De motor draait 800 stappen
  myStepper.step(800);
  Positie = 0;
  Serial.println("Systeem start op... Kalibreren.");

  pinMode(knopPin, INPUT_PULLUP);

  mySoftwareSerial.begin(9600);


  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("DFPlayer niet gevonden!");
  }

  myDFPlayer.volume(30); // startvolume
}

void loop() {
  // aan/uit
  bool huidigeKnopStaat = digitalRead(BUTTON_PIN);

  // Als de knop wordt ingedrukt gaat hij van LOW naar HIGH
  if (huidigeKnopStaat == HIGH && laatsteKnopStaat == LOW) {
    systeemAan = !systeemAan; 
    delay(150);// Debounce
    
    if (systeemAan) {
      Serial.println(">>> SYSTEEM AAN");
    } else {
      Serial.println(">>> SYSTEEM UIT");
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
    }
  }
  laatsteKnopStaat = huidigeKnopStaat;






  // knop
  bool knopStatus = digitalRead(knopPin);

  if (laatstStatus == HIGH && knopStatus == LOW) {
    Serial.println("Knop ingedrukt → speel muziek");
    myDFPlayer.play(1);  // speel 0001.mp3
    delay(300);
  }

  laatstStatus = knopStatus;

  // potentiometer
  int potValue = analogRead(potPin);

  // map naar 0–30
  int volume = map(potValue, 0, 1023, 0, 30);

  // alleen aanpassen als het verandert
  if (abs(volume - laatsteVolume) >= 1) { 
    myDFPlayer.volume(volume);
    laatsteVolume = volume;
  }




  if (systeemAan) {
    float h = dht.readHumidity();
    int co2Raw = analogRead(MQ_PIN);
    int potWaarde = analogRead(POT_PIN);

    int helderheid = map(potWaarde, 0, 1023, 0, 255);
    if (helderheid < 8) helderheid = 0;// bij lage waarden led uit

    float ppm = map(co2Raw, RO_SCHONE_LUCHT, 1023, 400, 5000);

    // Monitor
    static unsigned long lastPrint = 0;
    if(millis() - lastPrint > 800) { // Print 1x per seconde
       Serial.print("Vocht: "); Serial.print(h);
       Serial.print("% | PPM: "); Serial.println(ppm);
       lastPrint = millis();
    }

    // Motor
    if (h >= 30 && h <= 60 && ppm < 800 && Positie == 0) {
      myStepper.step(-600);
      Positie = 1;
    } 
    else if ((h < 30 || h > 60 || ppm > 800) && Positie == 1) {
      myStepper.step(800);
      Positie = 0;
    }

    // led 
    if (ppm > 1200) {
      unsigned long huidigeTijd = millis();
      if (huidigeTijd - vorigeTijd >= interval) {
        vorigeTijd = huidigeTijd;
        ledStatus = !ledStatus;
      }
      if (ledStatus && helderheid > 0) analogWrite(redPin, helderheid);
      else analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
    } else {
      if (Positie == 0) {
        analogWrite(redPin, helderheid);
        analogWrite(greenPin, 0);
      } else {
        analogWrite(greenPin, helderheid);
        analogWrite(redPin, 0);
      }
    }
  } 

  delay(10);
}