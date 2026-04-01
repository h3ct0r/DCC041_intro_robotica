#include <matplot/matplot.h>

#include <Eigen/Dense>
#include <cmath>
#include <iostream>

void plot_frame(Eigen::VectorXd org, Eigen::MatrixXd Rorg) {
    float axis_size = 3.f;
    Eigen::MatrixXd axes = Rorg * axis_size;

    matplot::arrow(org[0], org[1], org[0] + axes(1, 1), org[1] + axes(1, 0))->color("red").line_width(3);
    matplot::arrow(org[0], org[1], org[0] + axes(0, 1), org[1] + axes(0, 0))->color("green").line_width(3);
}

Eigen::MatrixXd Rz(float theta) {
    Eigen::MatrixXd rot(3, 3);
    rot << std::cos(theta), -std::sin(theta), 0,
        std::sin(theta), std::cos(theta), 0,
        0, 0, 1;

    return rot;
}

Eigen::MatrixXd Rx(float theta) {
    Eigen::MatrixXd rot(3, 3);
    rot << 1, 0, 0,
        0, std::cos(theta), -std::sin(theta),
        0, std::sin(theta), std::cos(theta);

    return rot;
}

Eigen::MatrixXd Ry(float theta) {
    Eigen::MatrixXd rot(3, 3);
    rot << std::cos(theta), 0, std::sin(theta),
        0, 1, 0,
        -std::sin(theta), 0, std::cos(theta);

    return rot;
}

int main() {
    // theta always in radians
    float alpha = M_PI / 2;
    float beta = M_PI / 4;
    float gamma = M_PI / 3;

    Eigen::MatrixXd R = Rz(alpha) * Ry(beta) * Rx(gamma);
    std::cout
        << "R:" << std::endl
        << R << std::endl;

    // obtaining the original values for roll pitch yaw
    float cB = std::sqrt(pow(R(0, 0), 2) + pow(R(1, 0), 2));
    float beta_calc = std::atan2(-R(2, 0), cB);
    float alpha_calc = std::atan2(R(1, 0) / cB, R(0, 0) / cB);
    float gamma_calc = std::atan2(R(2, 1) / cB, R(2, 2) / cB);

    std::cout << "alpha:\t" << alpha << "\t\talpha_calc:" << alpha_calc << std::endl;
    std::cout << "beta:\t" << beta << " \tbeta_calc:" << beta_calc << std::endl;
    std::cout << "gamma:\t" << gamma << "\t\tgamma_calc:" << gamma_calc << std::endl;

    return 0;
}