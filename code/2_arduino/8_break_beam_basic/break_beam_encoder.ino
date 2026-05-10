const byte SENSOR_PIN_D0 = 18;
const byte SENSOR_PIN_A0 = 3;

const int holes = 40; // Number of holes in the 20mm encoder disc
volatile unsigned long pulseCount = 0; // Use 'volatile' for variables changed in ISR
unsigned long lastInterrupt = 0;
unsigned long lastOdomMillis = 0;

float rpm = 0;
float wheel_radius_cm = 3.35;
float distance_cm = 0;

// The Interrupt Service Routine (ISR) - Keep it short!
void pulseCounter() {
  unsigned long currentTime = millis();
  if(currentTime - lastInterrupt > 10){
    pulseCount++;
    lastInterrupt = currentTime;
  }
}

void setup() {
  pinMode(SENSOR_PIN_D0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN_D0), pulseCounter, RISING);

  pinMode(SENSOR_PIN_A0, INPUT);

  Serial.begin(9600);
}

void loop() {
  int sensorValueD = digitalRead(SENSOR_PIN_D0);
  int sensorValueA = analogRead(SENSOR_PIN_A0);
  Serial.print(sensorValueD * 1000);
  Serial.print("\t");
  Serial.println(sensorValueA);
  // Serial.print("\t");
  // Serial.println(pulseCount);
}