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
    Eigen::VectorXd pc(4);
    pc << 2.f, 2.f, 0.f, 1.f;

    // transformation form b to a: Tba
    Eigen::VectorXd pb_aorg(4);
    pb_aorg << 5.f, 10.f, 0.f, 1.f;
    Eigen::MatrixXd Rba = Rz(45 * (M_PI / 180.f));
    Eigen::MatrixXd Tba(4, 4);
    Tba.block(0, 0, 3, 3) = Rba;
    Tba.block(0, 3, 4, 1) = pb_aorg;
    std::cout << "Tba" << std::endl
              << Tba << std::endl;

    // transformation form c to b: Tcb
    Eigen::VectorXd pc_borg(4);
    pc_borg << 0.f, -6.f, 0.f, 1.f;
    Eigen::MatrixXd Rcb = Rz(-45 * (M_PI / 180.f));
    Eigen::MatrixXd Tcb(4, 4);
    Tcb.block(0, 0, 3, 3) = Rcb;
    Tcb.block(0, 3, 4, 1) = pc_borg;
    std::cout << "Tcb:" << std::endl
              << Tcb << std::endl;

    Eigen::MatrixXd Tac = Tba * Tcb;
    std::cout << "Tac:" << std::endl
              << Tac << std::endl;

    Eigen::VectorXd pa = Tac * pc;
    std::cout << "pa:" << std::endl
              << pa << std::endl;

    auto f = matplot::figure(false);
    f->backend()->run_command("unset warnings");
    matplot::hold(matplot::on);

    // plot A frame
    plot_frame(Eigen::VectorXd::Zero(4), Eigen::MatrixXd::Identity(4, 4));

    // plot B frame
    plot_frame(pb_aorg, Rba);

    // plot C frame
    plot_frame(pc_borg, Rcb);

    auto e = matplot::ellipse(pa(0), pa(1), 0.4, 0.4)->color("black").fill(true);

    matplot::grid(true);
    matplot::axis({-10, 15, -10, 15});
    matplot::show();

    return 0;
}