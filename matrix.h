#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <iostream>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned rows, columns;

public:
    Matrix(unsigned rows, unsigned columns) : rows{rows}, columns{columns} {
        Node<T> *temp = root;
        temp->next = new Node<T>;
    }

    void set(unsigned, unsigned, T);
    T operator()(unsigned, unsigned) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    void print() const {
        Node<T> *temp = root;
        if (temp->next)
            cout << "Yes\n";
    }

    //~Matrix();
};

#endif //SPARSE_MATRIX_MATRIX_H