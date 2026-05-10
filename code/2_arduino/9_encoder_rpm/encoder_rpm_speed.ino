const byte SENSOR_PIN_D0 = 18;
const byte SENSOR_PIN_A0 = 5;

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
  unsigned long currentTime = millis();
  if (currentTime - lastOdomMillis > 500) {
    detachInterrupt(digitalPinToInterrupt(SENSOR_PIN_D0));

    rpm = (pulseCount * 60.0) / holes;
    
    Serial.print("Pulses: ");
    Serial.print(pulseCount);

    Serial.print("\tRPM: ");
    Serial.print(rpm);

    float rps = rpm / 60.0;
    Serial.print("\tRPS: ");
    Serial.print(rps);

    Serial.print("\tcm/s: ");
    float cm_ps = (rpm * (2 * M_PI * wheel_radius_cm)) / 60.0;
    Serial.print(cm_ps);

    Serial.print("\tdist_cm:");
    distance_cm += (pulseCount / float(holes)) * (2 * M_PI * wheel_radius_cm);
    Serial.println(distance_cm);
    
    pulseCount = 0;
    lastOdomMillis = currentTime;
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN_D0), pulseCounter, RISING);
  }
}