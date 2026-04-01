#include <Eigen/Dense>  // Include the dense module for MatrixXd
#include <iostream>

// Use the Eigen namespace for easier access to Eigen classes
using Eigen::MatrixXd;

int main() {
    // Create a dynamic-size matrix of doubles (MatrixXd)
    MatrixXd m(2, 2);
    std::cout << "My Eigen Matrix (Hello World!) (2x2):" << std::endl;
    std::cout << m << std::endl;

    // Assign values to matrix elements
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    std::cout << "\n\nUpdate matrix values:\n"
              << m << std::endl;

    // Perform a calculation for the last element
    m(1, 1) = m(1, 0) + m(0, 1);

    // Print the matrix to the standard output
    std::cout << "\n\nPerform:  m(1, 1) = m(1, 0) + m(0, 1)\n"
              << m << std::endl;

    return 0;
}