#ifndef MATRIX_H
#define MATRIX_H

template<typename T>
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

    // Matrix operator+(const Matrix& other) const;
    // Matrix& operator+=(const Matrix& other);

    // Matrix operator-(const Matrix& other) const;
    // Matrix& operator-=(const Matrix& other);

    // Matrix operator*(const Matrix& other) const;
    // Matrix& operator*=(const Matrix& other);

    // Matrix operator*(T scalar) const;
    // Matrix& operator*=(T scalar);

    // T trace() const;

    // T determinant() const;

private:
    void allocate_();
    void destroy_();
    void copy_data_(const Matrix& m);

    T** data_ = nullptr;
    size_t rows_;
    size_t columns_;
};

#endif // MATRIX_H