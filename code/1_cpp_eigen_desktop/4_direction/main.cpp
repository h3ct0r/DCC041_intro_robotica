#include <matplot/matplot.h>

#include <Eigen/Dense>
#include <cmath>
#include <iostream>

int main() {
    Eigen::Vector2f p;
    p << 1.0f, 2.0f;

    Eigen::Vector2f q;
    q << 4.0f, 3.0f;

    Eigen::Vector2f origin;
    origin << 0.0f, 0.0f;

    // vetor de deslocamento
    Eigen::Vector2f v = q - p;
    std::cout << "V:\n\t" << v.transpose() << std::endl;

    // orientacao
    float a = std::atan2(v[1], v[0]);
    std::cout << "Orientacao:\n"
              << "\trad:" << a << std::endl
              << "\tdeg:" << a * (180.0 / M_PI) << std::endl;

    // vetor unitario (direcao)
    // Norma(magnitude)
    float m = v.norm();
    Eigen::Vector2f u = v / m;
    std::cout << "Unit vector:\n"
              << "\tMagnitude:" << m << std::endl
              << "\t" << u.transpose() << std::endl;

    // fix warning output from gnuplot
    auto f = matplot::figure(false);
    f->backend()->run_command("unset warnings");
    matplot::hold(matplot::on);

    matplot::arrow(origin[0], origin[1], p[0], p[1])
        ->color("red")
        .line_width(3);
    matplot::arrow(origin[0], origin[1], q[0], q[1])->color("blue").line_width(3);

    // plotando vetor deslocamento
    // matplot::quiver(std::vector<double>{p[0]},
    //                 std::vector<double>{p[1]},
    //                 std::vector<double>{v[0]},
    //                 std::vector<double>{v[1]}, v.norm())
    //     ->color("cyan")
    //     .line_width(3);

    matplot::arrow(p[0], p[1], p[0] + v[0], p[1] + v[1])
        ->color("cyan")
        .line_width(3);

    // plotando vetor direcao
    matplot::quiver(std::vector<double>{p[0]},
                    std::vector<double>{p[1]},
                    std::vector<double>{u[0]},
                    std::vector<double>{u[1]}, u.norm())
        ->color("green")
        .line_width(3);
    // matplot::arrow(p[0], p[1], p[0] + u[0], p[1] + u[1])->color("green").line_width(3);

    matplot::grid(true);
    matplot::axis({0, 5, 0, 5});
    matplot::show();

    return 0;
}