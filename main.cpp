#include <iostream>
#include "Matrix.h"
#include <complex>

template <typename T>
void print_matrix(const Matrix<T>& m) {
    for (size_t i = 0; i < m.get_rows(); i++) {
        for (size_t j = 0; j < m.get_columns(); j++) {
            std::cout << m(i + 1, j + 1) << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    Matrix<int> m1 = Matrix<int>(3, 3, 0, 1);

    Matrix<int> m2 = Matrix<int>(3, 3, 0, 1);

    print_matrix(m1 * m2);
    print_matrix(m2 * m1);

    Matrix<double> md1 = Matrix<double>(1, 1);
    md1(1, 1) = 1;

    Matrix<double> md2 = Matrix<double>(1, 1);
    md2(1, 1) = 0.9999;

    print_matrix(md1);
    print_matrix(md2);
    std::cout << (md1 == md2);

}