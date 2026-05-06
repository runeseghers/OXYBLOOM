#include <Stepper.h>
#include <DHT.h>
#include "DFRobotDFPlayerMini.h"

// --- PIN DEFINITIES ---
#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int MQ_PIN = A0;
const int POT_PIN = A1;
const int BUTTON_PIN = 2;   // Hoofdschakelaar Systeem
const int knopMuziek = A2;  // Context-knop
const int potVolume = A5;

// LED Groepen (Gecorrigeerd naar laatste pinnen)
// PWM pinnen op Mega: 2-13, 44, 45, 46. 
// Pin 41 ondersteunt GEEN PWM.
const int redPins[] = {5, 44, 12, 13}; 
const int greenPins[] = {6, 41, 4, 7}; 
const int aantalLeds = 4;

// Stepper configuratie
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper stepper2(stepsPerRevolution, 22, 24, 23, 25); 

// --- VARIABELEN ---
int groeiFase = 0;
unsigned long vorigeKnipperTijd = 0;
unsigned long lastSensorUpdate = 0;
unsigned long goedeLuchtStartTijd = 0; 
bool ledStatus = false;
bool systeemAan = true;      
bool laatsteKnopStaat = HIGH;
bool laatstStatusMuziek = HIGH;
int laatsteVolume = -1;

const unsigned long groeiInterval = 5000; 
const int maxFases = 5;

DFRobotDFPlayerMini myDFPlayer;

// --- VERBETERDE LED FUNCTIE ---
void setLeds(const int pinnen[], int waarde) {
  for(int i = 0; i < aantalLeds; i++) {
    if (waarde <= 0) {
      digitalWrite(pinnen[i], LOW); // Altijd volledig uit
    } 
    else {
      // Controleer of pin PWM ondersteunt (2-13, 44-46)
      // Pin 41 is de enige in jouw lijst die geen PWM heeft.
      if (pinnen[i] != 41) { 
        analogWrite(pinnen[i], waarde); 
      } else {
        digitalWrite(pinnen[i], HIGH); // Pin 41 gaat gewoon vol aan
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); 

  dht.begin();
  myStepper.setSpeed(5);
  stepper2.setSpeed(5);
  
  for(int i = 0; i < aantalLeds; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
  }
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(knopMuziek, INPUT_PULLUP);

  Serial.println("--- SYSTEEM START OP ---");
  Serial.println("Kalibreren motoren...");
  myStepper.step(500); 
  stepper2.step(-1200); 
  groeiFase = 0;

  if (!myDFPlayer.begin(Serial1)) {
    Serial.println("DFPlayer Error: Check verbinding");
  } else {
    Serial.println("DFPlayer Online");
    myDFPlayer.volume(25);
  }
}

void loop() {
  // --- 1. SYSTEEM AAN/UIT ---
  bool huidigeKnopStaat = digitalRead(BUTTON_PIN);
  if (huidigeKnopStaat == LOW && laatsteKnopStaat == HIGH) {
    systeemAan = !systeemAan; 
    Serial.print("Systeem: "); Serial.println(systeemAan ? "AAN" : "UIT");
    delay(250); 
    if (!systeemAan) {
      setLeds(redPins, 0);
      setLeds(greenPins, 0);
      myDFPlayer.stop();
    }
  }
  laatsteKnopStaat = huidigeKnopStaat;

  if (!systeemAan) return;

  // --- 2. HELDERHEID & VOLUME ---
  int potH = analogRead(POT_PIN);
  int helderheid;

  // Verbeterde logica voor 'volledig uit'
  if (potH < 50) { 
    helderheid = 0;
  } else if (potH > 950) {
    helderheid = 255;
  } else {
    helderheid = map(potH, 100, 950, 0, 255);
  }

  int volWaarde = analogRead(potVolume);
  int volume = map(volWaarde, 0, 1023, 0, 30);
  if (abs(volume - laatsteVolume) >= 1) { 
    myDFPlayer.volume(volume);
    laatsteVolume = volume;
  }

  // --- 3. MUZIEK KNOP ---
  bool huidigeStatusMuziek = digitalRead(knopMuziek);
  if (huidigeStatusMuziek == LOW && laatstStatusMuziek == HIGH) {
    if (groeiFase > 0) {
      myDFPlayer.play(2);
      Serial.println("Muziek: Goede lucht track");
    } else {
      myDFPlayer.play(1);
      Serial.println("Muziek: Slechte lucht track");
    }
    delay(250); 
  }
  laatstStatusMuziek = huidigeStatusMuziek;

  // --- 4. SENSOREN & LOGGING ---
  int co2Raw = analogRead(MQ_PIN);
  float ppm = map(co2Raw, 69, 1023, 400, 5000); 

  if (millis() - lastSensorUpdate > 1100) {
    float h = dht.readHumidity();
    
    Serial.print("Vocht: "); Serial.print(h);
    Serial.print("% | CO2: "); Serial.print(ppm);
    Serial.print(" ppm | Fase: "); Serial.println(groeiFase);

    if (h >= 30 && h <= 60 && ppm < 800) {
      if (groeiFase == 0) {
        myStepper.step(-400); 
        stepper2.step(600); 
        groeiFase = 1;
        goedeLuchtStartTijd = millis();
      } 
      else if (groeiFase > 0 && groeiFase < maxFases) {
        if (millis() - goedeLuchtStartTijd >= groeiInterval) {
          stepper2.step(120); 
          groeiFase++;
          goedeLuchtStartTijd = millis();
        }
      }
    } 
    else {
      if (groeiFase > 0) {
        int totaalTerug = 400 + ((groeiFase - 1) * 200);
        stepper2.step(-totaalTerug);
        myStepper.step(totaalTerug);
        
        groeiFase = 0;
        myDFPlayer.stop(); 
      }
    }
    lastSensorUpdate = millis();
  }

  // --- 5. LED FEEDBACK ---
  if (helderheid == 0) {
    setLeds(redPins, 0);
    setLeds(greenPins, 0);
  } 
  else if (ppm > 1200) {
    if (millis() - vorigeKnipperTijd >= 500) {
      vorigeKnipperTijd = millis();
      ledStatus = !ledStatus;
    }
    setLeds(redPins, ledStatus ? helderheid : 0);
    setLeds(greenPins, 0);
  } 
  else {
    if (groeiFase == 0) {
      setLeds(redPins, helderheid);
      setLeds(greenPins, 0);
    } else {
      setLeds(greenPins, helderheid);
      setLeds(redPins, 0);
    }
  }
}