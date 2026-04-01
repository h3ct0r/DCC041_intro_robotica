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
    Eigen::VectorXd pb(4);
    pb << 3.f, 7.f, 0.f, 1.f;
    Eigen::VectorXd pa_borg(4);
    pa_borg << 10.f, 5.f, 0.f, 1.f;

    std::cout << "pb:" << std::endl
              << pb.transpose() << std::endl;

    std::cout << "pa_borg:" << std::endl
              << pa_borg.transpose() << std::endl;

    // theta always in radians
    float theta = 30 * (M_PI / 180.f);

    Eigen::MatrixXd Rab = Rz(theta);
    std::cout << "Rab:" << std::endl
              << Rab << std::endl;

    // Copy the smaller vector into a specific column of the large matrix
    // The block operation must match the size of the vector being assigned.
    // Here we use .block(start_row, start_col, num_rows, num_cols)
    Eigen::MatrixXd Tab(4, 4);
    Tab.block(0, 0, 3, 3) = Rab;
    Tab.block(0, 3, 4, 1) = pa_borg;
    Tab(3, 3) = 1.f;

    std::cout << "Tab:" << std::endl
              << Tab << std::endl;

    Eigen::MatrixXd pa = Tab * pb;
    std::cout << "pa:" << std::endl
              << pa.transpose() << std::endl;

    auto f = matplot::figure(false);
    f->backend()->run_command("unset warnings");
    matplot::hold(matplot::on);

    // plot A frame
    plot_frame(pa_borg, Rab);

    // plot B frame (base frame)
    plot_frame(Eigen::VectorXd::Zero(4), Eigen::MatrixXd::Identity(4, 4));

    auto e = matplot::ellipse(pa(0), pa(1), 0.4, 0.4)->color("black").fill(true);

    matplot::grid(true);
    matplot::axis({-1, 15, -1, 15});
    matplot::show();

    return 0;
}