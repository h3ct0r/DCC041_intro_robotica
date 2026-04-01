#include <BasicLinearAlgebra.h>

// Use the BLA namespace for easier access to BasicLinearAlgebra classes
using namespace BLA;

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    
    // Give the serial monitor a brief moment to initialize
    delay(100); 

    // Create a statically-sized 2x2 matrix of floats
    Matrix<2, 2> m;

    Serial.println("My BLA Matrix (Hello World!) (2x2):");
    Serial.println(m); // FIXED: Use standard println

    // Assign values to matrix elements
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    
    Serial.println("\nUpdate matrix values:");
    Serial.println(m); // FIXED: Use standard println

    // Perform a calculation for the last element
    m(1, 1) = m(1, 0) + m(0, 1);

    // Print the final matrix to the Serial Monitor
    Serial.println("\nPerform:  m(1, 1) = m(1, 0) + m(0, 1)");
    Serial.println(m); // FIXED: Use standard println
}

void loop() {
    // The loop is left empty since we only want to run the calculation once
}