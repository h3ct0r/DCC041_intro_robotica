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

    // Point C in frame C
    Matrix<4> pc = {2.0, 2.0, 0.0, 1.0};

    // --- Transformation from B to A: Tba ---
    Matrix<4> pb_aorg = {5.0, 10.0, 0.0, 1.0};
    Matrix<3, 3> Rba = Rz(45.0 * (PI / 180.0));
    
    // Construct Tba manually replacing Eigen's .block()
    Matrix<4, 4> Tba = {
        Rba(0,0), Rba(0,1), Rba(0,2), pb_aorg(0),
        Rba(1,0), Rba(1,1), Rba(1,2), pb_aorg(1),
        Rba(2,0), Rba(2,1), Rba(2,2), pb_aorg(2),
        0.0,      0.0,      0.0,      1.0
    };
    
    Serial.println("Tba:");
    Serial.println(Tba);

    // --- Transformation from C to B: Tcb ---
    Matrix<4> pc_borg = {0.0, -6.0, 0.0, 1.0};
    Matrix<3, 3> Rcb = Rz(-45.0 * (PI / 180.0));
    
    // Construct Tcb manually
    Matrix<4, 4> Tcb = {
        Rcb(0,0), Rcb(0,1), Rcb(0,2), pc_borg(0),
        Rcb(1,0), Rcb(1,1), Rcb(1,2), pc_borg(1),
        Rcb(2,0), Rcb(2,1), Rcb(2,2), pc_borg(2),
        0.0,      0.0,      0.0,      1.0
    };
    
    Serial.println("\nTcb:");
    Serial.println(Tcb);

    // --- Compound Transformation from C to A: Tac ---
    // BLA perfectly handles 4x4 matrix multiplication just like Eigen
    Matrix<4, 4> Tac = Tba * Tcb;
    
    Serial.println("\nTac:");
    Serial.println(Tac);

    // --- Final Point Calculation ---
    // Multiply the compound transformation matrix by the original point
    Matrix<4> pa = Tac * pc;
    
    Serial.println("\npa:");
    Serial.println(~pa); // Using ~ to transpose it to a row vector for horizontal printing
}

void loop() {
    // Leave empty to run the transformation math only once at startup
}