#include <iostream>
#include "Matrix.h"

template<typename T>
void print_matrix(const Matrix<T>& m) {
    for (size_t i = 0; i < m.get_rows(); i++) {
        for (size_t j = 0; j < m.get_columns(); j++) {
            std::cout << m(i + 1, j + 1) << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    Matrix<int> m1 = Matrix<int>(2, 2);
    m1(2, 2) = 8;
    Matrix<int> m2(m1);
    m1(1, 1) = 8;
    m1(2, 2) = 9;
    print_matrix(m1);
    m2 = m1;
    print_matrix(m2);
}