#include <matplot/matplot.h>

#include <Eigen/Dense>  // Include the dense module for MatrixXd
#include <cmath>
#include <iostream>

int main() {
    std::vector<double> x = matplot::linspace(0, 2 * M_PI);
    std::vector<double> y = matplot::transform(x, [](auto x) { return sin(x); });

    // fix warning output from gnuplot
    auto f = matplot::figure(false);
    f->backend()->run_command("unset warnings");

    matplot::plot(x, y, "-o");
    auto a = matplot::arrow(2.5, 6.5, 5, 5);
    a->color("blue");
    matplot::hold(matplot::on);
    matplot::plot(x, matplot::transform(y, [](auto y) { return -y; }), "--xr");
    matplot::plot(x, matplot::transform(x, [](auto x) { return x / M_PI - 1.; }), "-:gs");
    matplot::plot({1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1}, "k");
    matplot::show();

    return 0;
}