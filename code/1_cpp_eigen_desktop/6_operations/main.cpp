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

int main() {
    Eigen::VectorXd pb(3);
    pb << 3.f, 7.f, 6.f;
    Eigen::VectorXd pa_borg(3);
    pa_borg << 1.f, 2.f, 0.f;

    // translation
    std::cout << "pb: \t\t" << pb.transpose() << std::endl;
    std::cout << "pa_borg: \t" << pa_borg.transpose() << std::endl;
    std::cout << "Translation: \t" << (pb + pa_borg).transpose() << std::endl;

    // rotation
    float theta = 30 * (M_PI / 180.f);
    pb << 0.f, 2.f, 0.f;
    Eigen::VectorXd pb_rotated = Rz(theta) * pb;
    std::cout << "Rotation: \t" << pb_rotated.transpose() << std::endl;

    // rotation and translation
    pb << 3.f, 7.f, 6.f;
    pa_borg << 10.f, 5.f, 0.f;
    Eigen::VectorXd pa = Rz(theta) * pb + pa_borg;
    std::cout << "Rotation and Trans: \t" << pa.transpose() << std::endl;

    return 0;
}