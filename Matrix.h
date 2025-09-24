#ifndef MATRIX_H
#define MATRIX_H
#include <random>
#include <ostream>

template <typename T>
class Matrix {
public:
    Matrix();
    Matrix(size_t n);
    Matrix(size_t n, size_t m);
    Matrix(size_t n, size_t m, T rand_min, T rand_max);
    Matrix(size_t n, size_t m, const std::vector<T>& arr);

    size_t get_rows() const;
    size_t get_columns() const;

    Matrix(const Matrix& m);
    Matrix<T>& operator=(const Matrix<T>& m);
    ~Matrix();

    T& operator()(size_t n, size_t m);
    T operator()(size_t n, size_t m) const;

    bool operator==(const Matrix<T>& other) const;

    Matrix<T>& operator+=(const Matrix<T>& other);

    Matrix<T>& operator-=(const Matrix<T>& other);

    Matrix<T>& operator*=(const Matrix<T>& other);

    Matrix<T>& operator*=(T scalar);
    Matrix<T>& operator/=(T scalar);

    T trace() const;

    T determinant() const;

    void transpose();

    Matrix<T> get_transposed() const;

private:
    void allocate_();
    void destroy_();
    void copy_data_(const Matrix& m);

    T random_(T min, T max) const;
    bool is_equal_(T a, T b) const;
    bool is_greaterq_(T a, T b) const;

    inline static std::random_device rd_;
    inline static std::mt19937 random_int_ = std::mt19937(rd_());
    inline static const double EPSILON_ = 0.0001; // Константа для сравнения чисел с плавающей точкой

    T** data_ = nullptr;
    size_t rows_;
    size_t columns_;
};

template <typename T>
bool operator==(const Matrix<T>& a,  const Matrix<T>& b) {
    return a==(b);
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& m,  T scalar) {
    return Matrix<T>(m) *= scalar;
}

template <typename T>
Matrix<T> operator*(T scalar, const Matrix<T>& m) {
    return Matrix<T>(m) *= scalar;
}

template <typename T>
Matrix<T> operator/(const Matrix<T>& m,  T scalar) {
    return Matrix<T>(m) /= scalar;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& m1, const Matrix<T>& m2) {
    return Matrix<T>(m1) += m2;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& m1, const Matrix<T>& m2) {
    return Matrix<T>(m1) += m2;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2) {
    return Matrix<T>(m1) *= m2;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    for (size_t i = 0; i < m.get_rows(); i++) {
        for (size_t j = 0; j < m.get_columns(); j++) {
            os << m(i+1, j+1) << " ";
        }
        os << "\n";
    }
    return os;
}

#endif // MATRIX_H