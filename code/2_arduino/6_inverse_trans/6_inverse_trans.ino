#include <BasicLinearAlgebra.h>
#include <math.h>

// Use the BLA namespace
using namespace BLA;

// Z-axis rotation matrix (3x3)
Matrix<3, 3> Rz(float theta) {
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

    // 3x1 Translation vector
    Matrix<3> pa_borg = {4.0, 3.0, 0.0};
    
    Serial.println("pa_borg:");
    Serial.println(~pa_borg); // Print as row vector

    // theta always in radians
    float theta = 30.0 * (PI / 180.0);
    
    Matrix<3, 3> Rab = Rz(theta);
    Serial.println("\nRab:");
    Serial.println(Rab);

    // --- Construct Tab ---
    // Manually mapping the 3x3 rotation and 3x1 translation into the 4x4 matrix
    Matrix<4, 4> Tab = {
        Rab(0,0), Rab(0,1), Rab(0,2), pa_borg(0),
        Rab(1,0), Rab(1,1), Rab(1,2), pa_borg(1),
        Rab(2,0), Rab(2,1), Rab(2,2), pa_borg(2),
        0.0,      0.0,      0.0,      1.0
    };
    
    Serial.println("\nTab:");
    Serial.println(Tab);

    // --- Manual Inverse of Tab (iTab) ---
    // The inverse of a homogeneous transform is: [ R^T , -R^T * p ]
    //                                            [  0  ,    1     ]
    Matrix<3, 3> Rab_T = ~Rab;                   // Transpose of rotation
    Matrix<3> p_inv = -Rab_T * pa_borg;          // Inverse translation component
    
    Matrix<4, 4> iTab = {
        Rab_T(0,0), Rab_T(0,1), Rab_T(0,2), p_inv(0),
        Rab_T(1,0), Rab_T(1,1), Rab_T(1,2), p_inv(1),
        Rab_T(2,0), Rab_T(2,1), Rab_T(2,2), p_inv(2),
        0.0,        0.0,        0.0,        1.0
    };
    
    Serial.println("\niTab (Manual Inverse):");
    Serial.println(iTab);

    // --- BLA's Built-in Inverse ---
    // BLA has an Inverse() function that uses Gauss-Jordan elimination
    Matrix<4, 4> Tab_inv = Inverse(Tab);
    
    Serial.println("\nInverse of Tab (BLA Function):");
    Serial.println(Tab_inv);
}

void loop() {
    // Leave empty to run the transformation math only once at startup
}