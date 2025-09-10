#ifndef MATRIX_H
#define MATRIX_H

template<typename T>
class Matrix {
public:
    Matrix();
    Matrix(size_t n);
    Matrix(size_t n, size_t m);
    Matrix(size_t n, size_t m, T rand_min, T rand_max);

    Matrix(const Matrix& m)
    Matrix& operator=(const Matrix& m);
    ~Matrix();

    T& operator()(size_t n, size_t m);
    const T& operator()(size_t n, size_t m) const;

    Matrix operator+(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);

    Matrix operator-(const Matrix& other) const;
    Matrix& operator-=(const Matrix& other);

    Matrix operator*(const Matrix& other) const;
    Matrix& operator*=(const Matrix& other);

    Matrix operator*(T scalar) const;
    Matrix& operator*=(T scalar);

    T trace() const;

    //T determinant() const;

private:
    T** data_;
    size_t n_;
    size_t m_;
};

#endif // MATRIX_H