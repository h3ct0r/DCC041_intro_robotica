#include <matplot/matplot.h>

#include <Eigen/Dense>
#include <cmath>
#include <iostream>

int main() {
    // O que vamos a definir agora e o tamanho da componente, e nao a posicao x,y
    // Declare a fixed-size vector (2 elements, float type)
    Eigen::Vector2f p;
    p << 1.0f, 2.0f;  // Use the comma initializer

    Eigen::Vector2f q;
    q << 4.0f, 3.0f;

    Eigen::Vector2f origin;
    origin << 0.0f, 0.0f;

    std::cout << "P:\n\t" << p.transpose() << std::endl;
    std::cout << "Q:\n\t" << q.transpose() << std::endl;

    // fix warning output from gnuplot
    auto f = matplot::figure(false);
    f->backend()->run_command("unset warnings");

    matplot::arrow(origin[0], origin[1], p[0], p[1])
        ->color("red")
        .line_width(3);
    matplot::arrow(origin[0], origin[1], q[0], q[1])->color("blue").line_width(3);

    matplot::axis({0, 5, 0, 5});
    matplot::hold(matplot::on);
    matplot::show();

    return 0;
}