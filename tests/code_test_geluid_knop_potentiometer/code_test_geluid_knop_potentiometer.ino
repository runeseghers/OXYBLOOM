#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// DFPlayer pins
SoftwareSerial mySoftwareSerial(10, 11);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// knop
const int knopPin = 2;

// potentiometer
const int potPin = A0;

bool laatstStatus = HIGH;
int laatsteVolume = -1;

void setup() {
  pinMode(knopPin, INPUT_PULLUP);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("DFPlayer niet gevonden!");
    while (true);
  }

  myDFPlayer.volume(10); // startvolume
}

void loop() {
  // --- KNOP ---
  bool knopStatus = digitalRead(knopPin);

  if (laatstStatus == HIGH && knopStatus == LOW) {
    Serial.println("Knop ingedrukt → speel muziek");
    myDFPlayer.play(1);  // speel 0001.mp3
    delay(300);
  }

  laatstStatus = knopStatus;


  int potValue = analogRead(potPin);

  // map naar 0–30
  int volume = map(potValue, 0, 1023, 0, 30);

  // alleen aanpassen als het verandert
  if (volume != laatsteVolume) {
    myDFPlayer.volume(volume);
    Serial.print("Volume: ");
    Serial.println(volume);
    laatsteVolume = volume;
  }

  delay(50);
}