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
    Eigen::MatrixXd z_rot(3, 3);
    z_rot << std::cos(theta), -std::sin(theta), 0,
        std::sin(theta), std::cos(theta), 0,
        0, 0, 1;

    return z_rot;
}

int main() {
    Eigen::VectorXd pa_borg(3);
    pa_borg << 4.f, 3.f, 0.f;
    std::cout << "pa_borg:" << std::endl
              << pa_borg.transpose() << std::endl;

    float theta = 30 * (M_PI / 180.f);
    Eigen::MatrixXd Rab = Rz(theta);
    std::cout << "Rab:" << std::endl
              << Rab << std::endl;

    // Copy the smaller vector into a specific column of the large matrix
    // The block operation must match the size of the vector being assigned.
    // Here we use .block(start_row, start_col, num_rows, num_cols)
    Eigen::MatrixXd Tab(4, 4);
    Tab.block(0, 0, 3, 3) = Rab;
    Tab.block(0, 3, 3, 1) = pa_borg;
    Tab(3, 3) = 1.f;
    std::cout << "Tab:" << std::endl
              << Tab << std::endl;

    // inverse Tab
    Eigen::MatrixXd iTab(4, 4);
    iTab.block(0, 0, 3, 3) = Rab.transpose();
    iTab.block(0, 3, 3, 1) = -Rab.transpose() * pa_borg;
    iTab(3, 3) = 1.f;
    std::cout << "iTab:" << std::endl
              << iTab << std::endl;

    std::cout << "Inverse of Tab:" << std::endl
              << Tab.inverse() << std::endl;

    return 0;
}