#include <Adafruit_MotorShield.h>
#include <BasicLinearAlgebra.h>
#include <Servo.h>

#include "Arduino.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Encoder
const byte ENCODER_L_PIN = 19;

volatile unsigned long pulseCountLeft = 0;

unsigned long lastPulseLeftMillis = 0;
unsigned long lastOdomMillis = 0;
unsigned long lastControlMillis = 0;
const unsigned short PULSE_TIMEOUT_MILLIS = 5;
const unsigned short ODOM_TIMEOUT_MILLIS = 200;
const unsigned short CONTROL_TIMEOUT_MILLIS = 50;

float odomVL = 0;

// Robot config
const float TICKS_PER_REV = 40.0;
const float WHEEL_DIAMETER_CM = 6.8;
const float TRACK_WIDTH = 12.5;
const float DIST_PER_TICK = (M_PI * WHEEL_DIAMETER_CM) / float(TICKS_PER_REV);

// DC motor Control
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor* dcMotorLeft = AFMS.getMotor(2);

const int MAX_PWM = 230;

struct MotorPD {
    float kp;  // Proportional Gain
    float kd;  // Derivative Gain
    float prev_error;
    float prev_pwm;
};

// Tune these experimentally for your specific motors
// MotorPD motorctrL = {4, 0.00, 0.0, 0.0};
// MotorPD motorctrL = {2, 0.00, 0.0, 0.0};
// MotorPD motorctrL = {1.2, 0.00, 0.0, 0.0};
// MotorPD motorctrL = {1.2, 0.01, 0.0, 0.0};
// MotorPD motorctrL = {1.2, 0.4, 0.0, 0.0};
MotorPD motorctrL = {1.2, 0.25, 0.0, 0.0};

float targetOmegaL = 20.0;

void pulseCounterLeft() {
    unsigned long currentTime = millis();
    if (currentTime - lastPulseLeftMillis > PULSE_TIMEOUT_MILLIS) {
        pulseCountLeft++;
        lastPulseLeftMillis = currentTime;
    }
}

void setup() {
    pinMode(ENCODER_L_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_L_PIN), pulseCounterLeft, FALLING);

    AFMS.begin();
    Serial.begin(9600);

    dcMotorLeft->run(FORWARD);
    dcMotorLeft->setSpeed(0);
    
    delay(500);
}

void verifyUpdateOdometry(unsigned long currentTime) {
    unsigned long dt = currentTime - lastOdomMillis;
    if (dt > ODOM_TIMEOUT_MILLIS) {
        detachInterrupt(digitalPinToInterrupt(ENCODER_L_PIN));

        float dtSecs = (dt / 1000.0);

        odomVL = 0.0;
        if (pulseCountLeft > 0)
            odomVL = (DIST_PER_TICK * pulseCountLeft) / dtSecs;

        pulseCountLeft = 0;
        lastOdomMillis = currentTime;

        attachInterrupt(digitalPinToInterrupt(ENCODER_L_PIN), pulseCounterLeft, RISING);
    }
}

float computePD(float target_vel, float actual_vel, MotorPD& motorPD, float dt) {
    float error = target_vel - actual_vel;

    // Proportional
    float p_term = motorPD.kp * error;

    // Derivative
    float d_term = motorPD.kd * ((error - motorPD.prev_error) / dt);
    motorPD.prev_error = error;

    float output = motorPD.prev_pwm + p_term + d_term;
    output = constrain(output, -MAX_PWM, MAX_PWM);
    motorPD.prev_pwm = output;

    return output;
}

void runMotorControllers(unsigned long currentTime) {
    unsigned long dt = currentTime - lastControlMillis;
    if (dt > CONTROL_TIMEOUT_MILLIS) {
        float dtSecs = dt / 1000.0;

        float pwm_cmd_L = computePD(targetOmegaL, odomVL, motorctrL, dtSecs);

        Serial.print(targetOmegaL);
        Serial.print("\t");
        Serial.println(odomVL);

        if (pwm_cmd_L >= 0) {
            dcMotorLeft->run(FORWARD);
        } else {
            dcMotorLeft->run(BACKWARD);
        }

        dcMotorLeft->setSpeed(abs(pwm_cmd_L));
        lastControlMillis = currentTime;
    }
}

void loop() {
    unsigned long currentTime = millis();

    verifyUpdateOdometry(currentTime);
    runMotorControllers(currentTime);
}