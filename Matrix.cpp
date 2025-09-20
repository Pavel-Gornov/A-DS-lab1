#include "Matrix.h"
#include <complex>
#include <iostream>


template <typename T>
Matrix<T>::Matrix(): rows_(), columns_() {}

template <typename T>
Matrix<T>::Matrix(size_t n): rows_(n), columns_(n) { this->allocate_(); }

template <typename T>
Matrix<T>::Matrix(size_t n, size_t m): rows_(n), columns_(m) { this->allocate_(); }

template <typename T>
size_t Matrix<T>::get_rows() const { return rows_; }

template <typename T>
size_t Matrix<T>::get_columns() const { return columns_; }

template <typename T>
Matrix<T>::Matrix(size_t n, size_t m, T rand_min, T rand_max): rows_(n), columns_(m) {
    // if (rand_min > rand_max) {
    //     throw std::logic_error("Минимальный элемент должен быть меньше максимального");
    // }
    this->allocate_();
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < rows_; j++) {
            data_[i][j] = random_(rand_min, rand_max);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(size_t n, size_t m, const std::vector<T>& arr) {
    rows_ = n;
    columns_ = m;
    this->allocate_();
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < rows_; j++) {
            data_[i][j] = arr[(i * n) + j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& m) {
    this->rows_ = m.rows_;
    this->columns_ = m.columns_;
    this->allocate_();
    this->copy_data_(m);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
    if (this != &m) {
        if (this->rows_ != m.rows_ || this->columns_ != m.columns_) {
            this->destroy_();
            this->rows_ = m.rows_;
            this->columns_ = m.columns_;
            this->allocate_();
        }
        copy_data_(m);
    }
    return *this;
}

template <typename T>
Matrix<T>::~Matrix() {
    this->destroy_();
}

template <typename T>
T& Matrix<T>::operator()(size_t n, size_t m) {
    return this->data_[n - 1][m - 1];
}

template <typename T>
const T& Matrix<T>::operator()(size_t n, size_t m) const {
    return this->data_[n - 1][m - 1];
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &other) const {
    if (rows_ != rows_ || columns_ != columns_) { 
        return false; 
    }
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < rows_; j++) {
            if (!is_equal_(data_[i][j], other.data_[i][j])) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other) {
    if (rows_ != other.rows_ || columns_ != other.columns_) {
        throw std::logic_error("Матрицы разных размеров");
    }
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            data_[i][j] += other.data_[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other) {
    if (rows_ != other.rows_ || columns_ != other.columns_) {
        throw std::logic_error("Матрицы разных размеров");
    }
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            data_[i][j] -= other.data_[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &other) {
    if (columns_ != other.rows_) {
        throw std::logic_error("Матрицы не совместны");
    }
    Matrix<T> res(rows_, other.columns_);
    
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < other.columns_; j++) {
            for (size_t r = 0; r < columns_; r++) {
                res.data_[i][j] += data_[i][r] * other.data_[r][j];
            }
        }
    }
    *this = res;
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T scalar) {
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            data_[i][j] *= scalar;
        }
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(T scalar) {
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            data_[i][j] /= scalar;
        }
    }
    return *this;
}

template <typename T>
T Matrix<T>::trace() const {
    if (rows_ != columns_) {
        throw std::logic_error("Матрица не является квадратной");
    }
    T sum = T();
    for (size_t i = 0; i < rows_; i++) {
        sum += data_[i][i];
    }
    return sum;
}

template <typename T>
T Matrix<T>::determinant() const {
    if (rows_ != columns_) {
        throw std::logic_error("Матрица не является квадратной");
    }
    // Рекурсивное вычисление определителя через миноры матрицы
    if (rows_ == 0) return 1;
    if (rows_ == 1) return data_[0][0];
    if (rows_ == 2) return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];

    T result = T();

    for (size_t v = 0; v < rows_; v++) {

        Matrix<T> m = Matrix(rows_- 1, columns_ - 1);

         for (size_t i = 1; i < rows_; i++) {
            size_t z = 0;
            for (size_t j = 0; j < columns_; j++) {
                if (j != v) {
                    m.data_[i-1][z] = data_[i][j];
                    z++;
                }
            }
        }
        if (v % 2 == 0)
            result += (data_[0][v] * m.determinant());
        else
            result += (-data_[0][v] * m.determinant());
    }

    return result;
}

template <typename T>
void Matrix<T>::allocate_() {
    this->data_ = new T*[rows_];
    for (size_t i = 0; i < rows_; i++) {
        this->data_[i] = new T[columns_];
        for (size_t j = 0; j < columns_; j++) {
            this->data_[i][j] = T();
        }
    }
}

template <typename T>
void Matrix<T>::destroy_() {
    for (size_t i = 0; i < rows_; i++) {
        delete[] data_[i];
    }
    delete[] data_;
}

template <typename T>
void Matrix<T>::copy_data_(const Matrix& m) {
    for (size_t i = 0; i < m.rows_; i++) {
        for (size_t j = 0; j < m.columns_; j++) {
            this->data_[i][j] = m.data_[i][j];
        }
    }
}

template <typename T>
bool Matrix<T>::is_equal_(T a, T b) const {
    return a == b;
}

template <>
bool Matrix<float>::is_equal_(float a, float b) const {
    return (a > b? (a - b): (b - a)) < EPSILON_;
}

template <>
bool Matrix<double>::is_equal_(double a, double b) const {
    return (a > b? (a - b): (b - a)) < EPSILON_;
}

template <>
bool Matrix<std::complex<float>>::is_equal_(std::complex<float> a, std::complex<float> b) const {
    std::complex<float> dif = (a - b);
    return std::abs(dif) < EPSILON_;
}

template <>
bool Matrix<std::complex<double>>::is_equal_(std::complex<double> a, std::complex<double> b) const {
    std::complex<double> dif = (a - b);
    return std::abs(dif) < EPSILON_;
}

template <typename T>
T Matrix<T>::random_(T min, T max) const {
    return T(); // Нет общей реализации
}

template <>
int Matrix<int>::random_(int min, int max) const {
    return (random_int_() % (max + 1)) + min;
}

template <>
float Matrix<float>::random_(float min, float max) const {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random_int_);
}

template <>
double Matrix<double>::random_(double min, double max) const {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(random_int_);
}

template <>
std::complex<float> Matrix<std::complex<float>>::random_(std::complex<float> min, std::complex<float> max) const {
    std::uniform_real_distribution<float> real_dist(min.real(), max.real());
    std::uniform_real_distribution<float> imag_dist(min.imag(), max.imag());
    return std::complex<float>(real_dist(random_int_), imag_dist(random_int_));
}

template <>
std::complex<double> Matrix<std::complex<double>>::random_(std::complex<double> min, std::complex<double> max) const {
    std::uniform_real_distribution<double> real_dist(min.real(), max.real());
    std::uniform_real_distribution<double> imag_dist(min.imag(), max.imag());
    return std::complex<double>(real_dist(random_int_), imag_dist(random_int_));
}

// т.к. реализация вынесена в отдельный файл, то компиляция происходит для этих типов заранее
template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<std::complex<float>>;
template class Matrix<std::complex<double>>;