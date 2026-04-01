#include <BasicLinearAlgebra.h>
#include <math.h>

// Use the BLA namespace
using namespace BLA;

// Define the Z-axis rotation matrix function
// Returns a 3x3 statically sized matrix
Matrix<3, 3> Rz(float theta) {
    // In BLA, you can initialize matrices using curly braces
    Matrix<3, 3> z_rot = {
        cos(theta), -sin(theta), 0.0,
        sin(theta),  cos(theta), 0.0,
        0.0,         0.0,        1.0
    };
    return z_rot;
}

void setup() {
    Serial.begin(9600);
    delay(100);

    // BLA uses Matrix<Rows, Cols>. Matrix<3> defaults to a 3x1 column vector.
    Matrix<3> pb = {3.0, 7.0, 6.0};
    Matrix<3> pa_borg = {1.0, 2.0, 0.0};

    // --- Translation ---
    // Note: In BLA, the '~' operator is used to transpose a matrix/vector
    Serial.print("pb: \t\t");
    Serial.println(~pb); 
    
    Serial.print("pa_borg: \t");
    Serial.println(~pa_borg);
    
    Matrix<3> translation = pb + pa_borg;
    Serial.print("Translation: \t");
    Serial.println(~translation);
    Serial.println();

    // --- Rotation ---
    // Arduino already has 'PI' defined natively
    float theta = 30.0 * (PI / 180.0); 
    
    // Reassign values for the rotation step
    pb = {0.0, 2.0, 0.0}; 
    
    Matrix<3> pb_rotated = Rz(theta) * pb;
    Serial.print("Rotation: \t");
    Serial.println(~pb_rotated);
    Serial.println();

    // --- Rotation and Translation ---
    pb = {3.0, 7.0, 6.0};
    pa_borg = {10.0, 5.0, 0.0};
    
    Matrix<3> pa = Rz(theta) * pb + pa_borg;
    Serial.print("Rotation and Trans: \t");
    Serial.println(~pa);
}

void loop() {
    // Leave empty to run the math operations only once at startup
}