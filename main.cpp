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
    Matrix<int> m(2, 2, {1, 2, 3, 4});

    print_matrix(m);
    std::cout << m.determinant() << "\n\n";

    Matrix<std::complex<double>> mi(3, 3);
    mi(1, 1) = 1; mi(1, 2) = 6; mi(2, 1) = 7;
    mi(3, 3) = std::complex<double>(0, 1);
    mi(2, 2) = std::complex<double>(0, 1);
    print_matrix(mi);
    std::cout << mi.determinant();
}