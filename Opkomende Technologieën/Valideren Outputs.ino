#include <Stepper.h>
#include "DFRobotDFPlayerMini.h"

const int redPins[] = {5, 13};
const int greenPins[] = {4, 7};
const int aantalLeds = 2;

const int stepsPerRevolution = 2048;

Stepper motor1(stepsPerRevolution, 8, 10, 9, 11);
Stepper motor2(stepsPerRevolution, 22, 24, 23, 25);

DFRobotDFPlayerMini myDFPlayer;

void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);

  Serial.println("OUTPUT VALIDATIE");
  delay(1000);

  // leds
  for (int i = 0; i < aantalLeds; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
  }


  motor1.setSpeed(5);
  motor2.setSpeed(5);

  // dfplayer
  Serial.println("");
  Serial.println("DFPLAYER TEST");

  if (!myDFPlayer.begin(Serial1)) {
    Serial.println("DFPLAYER NIET GEVONDEN");
  } else {

    Serial.println("DFPLAYER GEVONDEN");
    Serial.println("DFPLAYER WENKT");

    myDFPlayer.volume(20);

    Serial.println("DFPLAYER SPEELT AUDIO 1");
    myDFPlayer.play(1);

    delay(5000);
    
    Serial.println("DFPLAYER SPEELT AUDIO 2");
    myDFPlayer.play(2);

    delay(5000);
  }

  // motor 1 test
  Serial.println("");
  Serial.println("MOTOR 1 TEST");

  Serial.println("MOTOR 1 GAAT NU DRAAIEN");

  motor1.step(1000);


  Serial.println("MOTOR 1 WERKT");

  delay(1500);

  // motor 2 test
  Serial.println("");
  Serial.println("MOTOR 2 TEST");

  Serial.println("MOTOR 2 GAAT NU DRAAIEN");

  motor2.step(1000);

  Serial.println("MOTOR 2 WERKT");

  delay(1500);

  // rode leds test
  Serial.println("");
  Serial.println("RODE LEDS TEST");

  for (int i = 0; i < aantalLeds; i++) {

    Serial.print("RODE LED");
    Serial.print(i + 1);
    Serial.println("BRANDT NU");

    digitalWrite(redPins[i], HIGH);

    delay(1000);

    digitalWrite(redPins[i], LOW);

    delay(300);
  }

  Serial.println("RODE LEDS WERKEN");

  delay(1000);

  // groene leds test
  Serial.println("");
  Serial.println("GROENE LEDS TEST");

  for (int i = 0; i < aantalLeds; i++) {

    Serial.print("GROENE LED");
    Serial.print(i + 1);
    Serial.println("BRANDT NU");

    digitalWrite(greenPins[i], HIGH);

    delay(1000);

    digitalWrite(greenPins[i], LOW);

    delay(300);
  }

  Serial.println("GROENE LEDS WERKEN");

  delay(1000);

  Serial.println(" ");
  Serial.println("ALLE OUTPUTS GETEST");
}
