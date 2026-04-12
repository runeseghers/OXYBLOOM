#include <Stepper.h>
#include <DHT.h>

#define DHTPIN A3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int MQ_PIN = A0;
const int POT_PIN = A1;

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
  myStepper.setSpeed(10);
  Serial.begin(9600);
  dht.begin(); 
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.println("Systeem start op... Kalibreren.");
  // De motor draait 800 stappen
  myStepper.step(800);
  statusPositie = 0;

}

void loop() {
  float h = dht.readHumidity();
  int co2Raw = analogRead(MQ_PIN);
  int potWaarde = analogRead(POT_PIN);


  // helderheid schalen en deadzone voor led volledig af
  int helderheid = map(potWaarde, 0, 1023, 0, 255);
  if (helderheid < 8) { 
    helderheid = 0;
  }

  // berekening naar ppm
  // de waarde: 69 komt ongeveer overeen met 400 ppm.
  // Als de waarde stijgt, stijgt de PPM mee.
  float ppm = map(co2Raw, RO_SCHONE_LUCHT, 1023, 400, 5000);

  // Print naar monitor
  Serial.print("Vocht: "); Serial.print(h);
  Serial.print("% | CO2 Waarde: "); Serial.print(ppm);
  Serial.println(" ppm");


  if (h >= 30 && h <= 60 && ppm < 800 && statusPositie == 0) {
    myStepper.step(-500);
    statusPositie = 1;
  } 
  else if ((h < 30 || h > 60 || ppm > 1200) && statusPositie == 1) {
    myStepper.step(800);
    statusPositie = 0;
  }

  // led aansturing apart
  if (ppm > 1200) {
    unsigned long huidigeTijd = millis();
    if (huidigeTijd - vorigeTijd >= interval) {
      vorigeTijd = huidigeTijd;
      ledStatus = !ledStatus;
    }
    
    if (ledStatus && helderheid > 0) {
      analogWrite(redPin, helderheid);
    } else {
      analogWrite(redPin, 0);
    }
    analogWrite(greenPin, 0);

  } else {
    if (statusPositie == 0) {
      analogWrite(redPin, helderheid);
      analogWrite(greenPin, 0);
    } else {
      analogWrite(greenPin, helderheid);
      analogWrite(redPin, 0);
    }
  }

  delay(100); //delay vertraagd
}