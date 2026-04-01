#include <BasicLinearAlgebra.h>
#include <math.h>

// Use the BLA namespace
using namespace BLA;

// X-axis rotation matrix
Matrix<3, 3> Rx(float theta) {
    Matrix<3, 3> rot = {
        1.0, 0.0,         0.0,
        0.0, cos(theta), -sin(theta),
        0.0, sin(theta),  cos(theta)
    };
    return rot;
}

// Y-axis rotation matrix
Matrix<3, 3> Ry(float theta) {
    Matrix<3, 3> rot = {
        cos(theta),  0.0, sin(theta),
        0.0,         1.0, 0.0,
       -sin(theta),  0.0, cos(theta)
    };
    return rot;
}

// Z-axis rotation matrix
Matrix<3, 3> Rz(float theta) {
    Matrix<3, 3> rot = {
        cos(theta), -sin(theta), 0.0,
        sin(theta),  cos(theta), 0.0,
        0.0,         0.0,        1.0
    };
    return rot;
}

void setup() {
    Serial.begin(9600);
    delay(100);

    // theta always in radians
    // Using Arduino's native PI constant
    float alpha = PI / 2.0;
    float beta = PI / 4.0;
    float gamma = PI / 3.0;

    // Calculate composite rotation matrix R = Rz * Ry * Rx
    Matrix<3, 3> R = Rz(alpha) * Ry(beta) * Rx(gamma);
    
    Serial.println("R:");
    Serial.println(R);
    Serial.println();

    // Obtaining the original values for roll, pitch, yaw
    // Note: Arduino has a native sq(x) macro which is much faster than pow(x, 2)
    float cB = sqrt(sq(R(0, 0)) + sq(R(1, 0))); 
    
    float beta_calc = atan2(-R(2, 0), cB);
    float alpha_calc = atan2(R(1, 0) / cB, R(0, 0) / cB);
    float gamma_calc = atan2(R(2, 1) / cB, R(2, 2) / cB);

    // Print the comparisons
    Serial.print("alpha:\t"); 
    Serial.print(alpha, 4); 
    Serial.print("\t\talpha_calc: "); 
    Serial.println(alpha_calc, 4);
    
    Serial.print("beta:\t"); 
    Serial.print(beta, 4); 
    Serial.print("\t\tbeta_calc:  "); 
    Serial.println(beta_calc, 4);
    
    Serial.print("gamma:\t"); 
    Serial.print(gamma, 4); 
    Serial.print("\t\tgamma_calc: "); 
    Serial.println(gamma_calc, 4);
}

void loop() {
    // Leave empty to run the matrix calculations only once at startup
}