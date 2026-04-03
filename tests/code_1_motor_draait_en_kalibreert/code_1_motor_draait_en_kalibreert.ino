#include <Stepper.h>

int huidigePositie = 0;
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
  
  Serial.println("Systeem start op... Kalibreren.");
  
  // De motor draait 1000 stappen
  myStepper.step(1000);
  huidigePositie = 0;

  Serial.println("Kalibratie voltooid.");
  
  delay(2000);
}

void loop() {

}