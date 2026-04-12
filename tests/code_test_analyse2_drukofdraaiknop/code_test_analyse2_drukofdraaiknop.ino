// Pinnen definiëren
const int ledPin = 6;      // PWM pin voor de LED
const int potPin = A1;     // Analoge pin voor de potmeter
const int buttonPin = 2;   // Pin voor de drukknop (met externe pull-down weerstand)

// Variabelen voor de status
int helderheid = 0;        
int laatstePotWaarde = 0;  
int knopStap = 0;          
bool knopWasIngetikt = false; // Om te voorkomen dat de stap door blijft lopen als je de knop inhoudt

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);      // Gewone input, we gebruiken externe weerstand
  laatstePotWaarde = analogRead(potPin);
}

void loop() {
  // 1. Potentiometer uitlezen
  int huidigePotWaarde = analogRead(potPin);
  
  // Als de potmeter wordt bewogen (marge van 5 tegen ruis)
  if (abs(huidigePotWaarde - laatstePotWaarde) > 5) {
    helderheid = map(huidigePotWaarde, 0, 1023, 0, 255);
    laatstePotWaarde = huidigePotWaarde;
    
    // Reset de knopStap zodat de knop weer bij de huidige helderheid begint bij volgende klik
    knopStap = helderheid / 63; 
  }

  // 2. Drukknop uitlezen (Nu op HIGH omdat hij aan 5V hangt)
  bool knopNuIngetikt = (digitalRead(buttonPin) == HIGH);

  if (knopNuIngetikt && !knopWasIngetikt) { // Alleen reageren op de eerste klik (state change)
    knopStap++;
    if (knopStap > 4) knopStap = 0; 
    
    helderheid = knopStap * 63; 
    delay(50); // Korte debounce
  }
  
  knopWasIngetikt = knopNuIngetikt; // Onthoud de status voor de volgende ronde

  // 3. LED aansturen
  analogWrite(ledPin, helderheid);
}