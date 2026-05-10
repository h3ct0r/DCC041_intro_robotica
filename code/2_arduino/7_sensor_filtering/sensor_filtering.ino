#include <Filters.h>
#include <Filters/SMA.hpp>                 // SMA (Simple Moving Average)

const int ECHO_PIN = 11;
const int TRIG_PIN = 10;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

SMA<5> average5 = {0};
SMA<10> average10 = {0};
SMA<20> average20 = {0};
SMA<30> average30 = {0};

void setup() {

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  //Set Echo pin as input to measure the duration of 
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {

  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;

  Serial.print(cm);
  Serial.print("\t");
  Serial.print(average5(cm));
  Serial.print("\t");
  Serial.print(average10(cm));
  Serial.print("\t");
  Serial.print(average20(cm));
  Serial.print("\t");
  Serial.print(average30(cm));
  Serial.println();

  delay(80);
}