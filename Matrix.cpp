#include "Matrix.h"
#include <complex>
#include <random>


template<typename T>
Matrix<T>::Matrix(): rows_(1), columns_(1) { this->allocate_(); }

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
    this->allocate_(); // TODO: Реализовать заполнение случайными значениями
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
        else {
            copy_data_(m);
        }
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
void Matrix<T>::allocate_()
{
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
        delete data_[i];
    }
    delete data_;
}

template <typename T>
void Matrix<T>::copy_data_(const Matrix& m) {
    for (size_t i = 0; i < m.rows_; i++) {
        for (size_t j = 0; j < m.columns_; j++) {
            this->data_[i][j] = m.data_[i][j];
        }
    }
}

// т.к. реализация вынесена в отдельный файл, то компиляция происходит для этих типов заранее
template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<std::complex<float>>;
template class Matrix<std::complex<double>>;