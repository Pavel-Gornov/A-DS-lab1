#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix {
public:
    Matrix();
    Matrix(size_t n);
    Matrix(size_t n, size_t m);
    Matrix(size_t n, size_t m, T rand_min, T rand_max);

    size_t get_rows() const;
    size_t get_columns() const;

    Matrix(const Matrix& m);
    Matrix<T>& operator=(const Matrix<T>& m);
    ~Matrix();

    T& operator()(size_t n, size_t m);
    const T& operator()(size_t n, size_t m) const;

    bool operator==(const Matrix<T>& other);

    Matrix<T>& operator+=(const Matrix<T>& other);

    Matrix<T>& operator-=(const Matrix<T>& other);

    Matrix<T>& operator*=(const Matrix<T>& other);

    Matrix<T>& operator*=(T scalar);
    Matrix<T>& operator/=(T scalar);

    T trace() const;

    // T determinant() const;

private:
    void allocate_();//Matrix<T> operator+(const Matrix<T>& other) const;
    void destroy_();
    void copy_data_(const Matrix& m);

    T** data_ = nullptr;
    size_t rows_;
    size_t columns_;
};

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

#endif // MATRIX_H