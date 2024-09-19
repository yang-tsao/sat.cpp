#include <cmath>
#include <complex>
#include <iostream>
#include <valarray>
namespace sat
{
    template <typename T>
    std::complex<T> normalize(std::complex<T> C)
    {
        return C / std::abs(C);
    }
    template <typename T>
    T dot(std::complex<T> C1, std::complex<T> C2)
    {
        return C1.real() * C2.real() + C1.imag() * C2.imag();
    }
    template <typename T>
    std::complex<T> edge_direction(std::complex<T> C0, std::complex<T> C1)
    {
        return C1 - C0;
    }
    template <typename T>
    std::complex<T> orthogonal(std::complex<T> C)
    {
        return {C.imag(), -C.real()};
    }
    template <typename T>
    std::valarray<std::complex<T>> vertices_to_edges(std::valarray<std::complex<T>> V)
    {
        return V.cshift(1) - V;
    }
    template <typename T>
    std::ranges::min_max_result<T>
    project(std::valarray<std::complex<T>> Vertices,
            std::complex<T> Axis)
    {
        T min = std::numeric_limits<T>::max();
        T max = -std::numeric_limits<T>::max();
        for (std::complex<T> v : Vertices)
        {
            T res = dot(v, Axis);
            if (res > max)
                max = res;
            if (res < min)
                min = res;
        }
        return {min, max};
    }
    template <typename T>
    bool overlap(std::ranges::min_max_result<T> projection1,
                 std::ranges::min_max_result<T> projection2)
    {
        return projection1.min <= projection2.max &&
               projection2.min <= projection1.max;
    }
    template <typename T>
    bool separating_axis_theorem(
        const std::valarray<std::complex<T>> V_a,
        const std::valarray<std::complex<T>> V_b)
    {
        std::valarray<std::complex<T>> axes(V_a.size() + V_b.size());
        axes[std::slice(0, V_a.size(), 1)] = vertices_to_edges(V_a);
        axes[std::slice(V_a.size(), V_b.size(), 1)] = vertices_to_edges(V_b);
        for (std::complex<T> &axis : axes)
            axis = normalize(orthogonal(axis));
        // for (auto i : axes)
        //     std::cout << i << '\n';
        for (std::complex<T> axis : axes)
        {
            std::ranges::min_max_result<T> projection_a = project(V_a, axis);
            std::ranges::min_max_result<T> projection_b = project(V_b, axis);
            // std::cout << projection_a.min << ' ' << projection_a.max << ' ' << projection_b.min << ' ' << projection_b.max << '\n';
            if (!overlap(
                    projection_a,
                    projection_b))
                return false;
        }
        return true;
    }
} // namespace sat
