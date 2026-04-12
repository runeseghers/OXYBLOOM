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
int statusPositie = 0;

// knipperen
unsigned long vorigeTijd = 0;
const long interval = 500;
bool ledStatus = false;

void setup() {
  myStepper.setSpeed(10); //snelheid wat vertraagd voor soepelere beweging
  Serial.begin(9600);
  dht.begin();
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);

  Serial.println("Systeem start op... Kalibreren.");
  // De motor draait 800 stappen
  myStepper.step(800); 
  statusPositie = 0; 
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
  if (h >= 30 && h <= 60 && ppm < 800 && statusPositie == 0) {
    Serial.println("Lucht is fris.");
    myStepper.step(-500);  
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    statusPositie = 1;
  } 

  // niet goed: Vochtigheid onder 40 of boven 60 of CO2 boven 1200 ppm
  else if ((h < 30 || h > 60 || ppm > 1200) && statusPositie == 1) {
    Serial.println("Grens overschreden!");
    myStepper.step(800); 
    digitalWrite(greenPin, LOW);
    statusPositie = 0; 
  }

  // knipperen bij hoge CO2
  if (ppm > 1200) {
    unsigned long huidigeTijd = millis();

    if (huidigeTijd - vorigeTijd >= interval) {
      vorigeTijd = huidigeTijd;

      ledStatus = !ledStatus; 
      digitalWrite(redPin, ledStatus);
    }
  } else {
    // de normale rode led
    if (statusPositie == 0) {
      digitalWrite(redPin, HIGH);
    } else {
      digitalWrite(redPin, LOW);
    }
  }

  delay(500);
}