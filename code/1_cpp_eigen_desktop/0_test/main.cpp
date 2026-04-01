#include <matplot/matplot.h>

#include <Eigen/Dense>
#include <cmath>
#include <iostream>

Eigen::MatrixXd Rz(float theta) {
    Eigen::MatrixXd z_rot(3, 3);
    z_rot << std::cos(theta), -std::sin(theta), 0,
        std::sin(theta), std::cos(theta), 0,
        0, 0, 1;

    return z_rot;
}

void plot_frame(Eigen::VectorXd org, Eigen::MatrixXd Rorg) {
    float axis_size = 3.f;
    Eigen::MatrixXd axes = Rorg * axis_size;

    matplot::arrow(org[0], org[1], org[0] + axes(1, 1), org[1] + axes(1, 0))->color("red").line_width(3);
    matplot::arrow(org[0], org[1], org[0] + axes(0, 1), org[1] + axes(0, 0))->color("green").line_width(3);
}

int main() {
    // Eigen::VectorXd aorg(3);
    // aorg << 0.f, 0.f, 0.f;

    // Eigen::VectorXd pb(3);
    // pb << 0.f, 2.f, 0.f;

    // // rotation
    // float theta = 30 * (M_PI / 180.f);
    // Eigen::VectorXd ap = Rz(theta) * pb;
    // std::cout << "ap: \t" << ap.transpose() << std::endl;

    auto f = matplot::figure(false);
    f->backend()->run_command("unset warnings");
    matplot::hold(matplot::on);

    // plot A frame
    plot_frame(Eigen::VectorXd::Zero(3), Eigen::MatrixXd::Identity(4, 4));
    matplot::grid(true);
    matplot::axis({-1, 15, -1, 11});
    matplot::show();

    // plot B frame (base frame)
    Eigen::VectorXd B_org(3);
    B_org << 10.f, 5.f, 0.f;
    std::cout << "B_org:" << std::endl
              << B_org.transpose() << std::endl;
    theta = 3 * (M_PI / 180.f);
    plot_frame(B_org, Eigen::VectorXd::Identity(4, 4));

    return 0;
}