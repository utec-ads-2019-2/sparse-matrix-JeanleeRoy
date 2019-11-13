#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *next, *down;
    unsigned x, y;
    T data;

public:
    explicit Node(): next{nullptr}, down{nullptr} {}
    explicit Node(T data): next{nullptr}, down{nullptr}, data{data} {}
    Node(T data, unsigned x, unsigned y): next{nullptr}, down{nullptr}, x{x}, y{y}, data{data} {}

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
