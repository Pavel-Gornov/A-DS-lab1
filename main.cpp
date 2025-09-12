#include <iostream>
#include "Matrix.h"

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
    Matrix<int> m1 = Matrix<int>(2, 2);
    m1(1, 1) = 1; m1(1, 2) = 2;
    m1(2, 1) = 3; m1(2, 2) = 4;

    Matrix<int> m2 = Matrix<int>(2, 2);
    m2(1, 1) = 1; m2(1, 2) = 1;
    m2(2, 1) = 1; m2(2, 2) = 1;
    
    print_matrix(m1 * m2);
    print_matrix(m2 * m1);
}