#include <Stepper.h>
#include <DHT.h>

#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// Positie 0 = startpunt, Positie 1 = andere kant
int Positie = 0;

void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
  dht.begin();
  
  Serial.println("Systeem start op... Kalibreren.");
  // De motor draait 1000 stappen
  myStepper.step(1000);
  Serial.println("Kalibratie voltooid.");
  
  Positie = 0;
  delay(2000);
}

void loop() {
  float vochtigheid = dht.readHumidity();

  Serial.print("Vochtigheid: ");
  Serial.print(vochtigheid);
  Serial.println("%");

  // Draai naar de andere kant (-2048)
  // Alleen als vochtigheid tussen 40 en 60 is en en positie staat nog op 0
  if (vochtigheid >= 40 && vochtigheid <= 60 && Positie == 0) {
    Serial.println("Vochtigheid optimaal (40-60%).");
    myStepper.step(-2048);
    Positie = 1;
  } 

  // Draai terug naar 0 (+2048)
  // Alleen als de motor aan de andere kant staat (Positie 1)
  // en de vochtigheid is buiten het bereik (lager dan 40 of hoger dan 60)
  else if ((vochtigheid < 40 || vochtigheid > 60) && Positie == 1) {
    Serial.println("Vochtigheid buiten bereik!");
    myStepper.step(2048);
    Positie = 0;
  }

  delay(2000);
}