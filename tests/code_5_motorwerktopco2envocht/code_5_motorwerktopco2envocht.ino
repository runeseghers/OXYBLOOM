#include <Stepper.h>
#include <DHT.h>

#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int MQ_PIN = A0;

//KALIBRATIE 
const float RO_SCHONE_LUCHT = 69.0; // gemeten waarde bij schone lucht

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
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);

  Serial.println("Systeem start op... Kalibreren.");
  // De motor draait 800 stappen
  myStepper.step(800);
  Positie = 0;
}

void loop() {
  float h = dht.readHumidity();
  int co2Raw = analogRead(MQ_PIN);

  // berekening naar ppm
  // de waarde: 69 komt ongeveer overeen met 400 ppm.
  // Als de waarde stijgt, stijgt de PPM mee.
  float ppm = map(co2Raw, RO_SCHONE_LUCHT, 1023, 400, 5000);

  // Print naar monitor
  Serial.print("Vocht: "); Serial.print(h);
  Serial.print("% | CO2 Waarde: "); Serial.print(ppm);
  Serial.println(" ppm");

  // logica op basis van ppm en vochtigheid
  // goed: Vochtigheid tussen 40 en 60 en CO2 onder 800 ppm
  if (h >= 40 && h <= 60 && ppm < 800 && Positie == 0) {
    Serial.println("-> STATUS: Lucht is fris. Motor naar stand 1.");
    myStepper.step(-500);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    Positie = 1;
  } 

  // niet goed: Vochtigheid onder 40 of boven 60 of CO2 boven 1200 ppm
  else if ((h < 40 || h > 60 || ppm > 1200) && Positie == 1) {
    Serial.println("-> WAARSCHUWING: Grens overschreden! Terug naar stand 0.");
    myStepper.step(800);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    Positie = 0;
  }

  delay(2000);
}