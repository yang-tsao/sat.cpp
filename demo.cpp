#include "sat.hpp"
#include <iostream>
using namespace sat;
int main()
{
    std::valarray<std::complex<double>>
        a_vertices{{0, 0}, {70, 0}, {0, 70}},
        b_vertices{{70, 70}, {150, 70}, {70, 150}},
        c_vertices = {{30, 30}, {150, 70}, {70, 150}};

    std::cout << separating_axis_theorem(a_vertices, b_vertices) << '\n';
    std::cout << separating_axis_theorem(a_vertices, c_vertices) << '\n';
    std::cout << separating_axis_theorem(b_vertices, c_vertices) << '\n';
    return 0;
}