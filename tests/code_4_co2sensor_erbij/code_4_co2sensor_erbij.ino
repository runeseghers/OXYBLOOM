#include <Stepper.h>
#include <DHT.h>

#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int mq135Pin = A0;
int sensorValue = 0;

const int redPin = 5;
const int greenPin = 6;
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// Positie 0 = startpunt, Positie 1 = andere kant
int Positie = 0;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
  dht.begin();

  pinMode(mq135Pin, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  
  Serial.println("Systeem start op... Kalibreren.");
  // De motor draait 800 stappen
  myStepper.step(800);
  Serial.println("Kalibratie voltooid.");

  Positie = 0;
  delay(2000);
}

void loop() {
  // sensoren uitlezen
  float vochtigheid = dht.readHumidity();
  sensorValue = analogRead(mq135Pin);

  Serial.print("Vochtigheid: ");
  Serial.print(vochtigheid);
  Serial.print("% | CO2 Waarde: ");
  Serial.println(sensorValue);

  if(sensorValue > 300) {
    Serial.println("WAARSCHUWING: Slechte luchtkwaliteit!");
  }

  // Draai naar de andere kant (-2048)
  // Alleen als vochtigheid tussen 40 en 60 is en positie staat nog op 0
  if (vochtigheid >= 40 && vochtigheid <= 60 && Positie == 0) {
    Serial.println("Vochtigheid optimaal. Motor draait...");
    myStepper.step(-500);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    Positie = 1;
  } 

  // Draai terug naar 0 (+2048)
  // Alleen als de motor aan de andere kant staat (Positie 1)
  // En de vochtigheid is buiten het bereik (lager dan 40 OF hoger dan 60)
  else if ((vochtigheid < 40 || vochtigheid > 60) && Positie == 1) {
    Serial.println("Vochtigheid buiten bereik! Motor herstelt...");
    myStepper.step(800);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    Positie = 0;
  }

  delay(2000);
}