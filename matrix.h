#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    unsigned rows, columns;
    vector<Node<T>*> Row, Column;

    void killRow(Node<T> *ptr) {
        if (ptr->next) killRow(ptr->next);
        delete ptr;
    }
    void buildHeaders() {
        for (size_t i = 0; i < rows; ++i)
            Row.push_back(new Node<int>());
        for (size_t i = 0; i < columns; ++i)
            Column.push_back(new Node<int>());
    }

public:
    Matrix(unsigned rows, unsigned columns) : rows{rows}, columns{columns} {
        buildHeaders();
    }

    Matrix(const Matrix &mx) : rows{mx.rows}, columns{mx.columns} {
        buildHeaders();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                set(i,j,mx.operator()(i,j));
    }

    void set(unsigned x, unsigned y, T data) {
        //if (x < 0 || y < 0 || x >= columns || y >= rows)
        if (!(x >= 0 && x < rows && y >= 0 && y < columns))
            throw out_of_range("Out of range");

        Node<T> *temp_x = Row[x], *temp_y = Column[y];
        while (temp_x->next && temp_x->next->y < y)
            temp_x = temp_x->next;
        while (temp_y->down && temp_y->down->x < x)
            temp_y = temp_y->down;

        if (temp_x->next && temp_x->next->y == y) {
            if (data != 0)
                temp_x->next->data = data;
            else {
                temp_x->next = temp_x->next->next;
                auto aux = temp_y->down;
                temp_y->down = aux->down;
                delete aux;
            } return;
        }
        if (data != 0) {
            auto set = new Node<T>(data,x,y);
            set->next = temp_x->next;
            temp_x->next = set;
            set->down = temp_y->down;
            temp_y->down = set;
        }
    }

    T operator()(unsigned x, unsigned y) const {
        if (x > y) {
            Node<T>* temp = Row[x];
            while (temp->next && temp->next->y < y)
                temp = temp->next;
            if (temp->next && temp->next->y == y)
                return temp->next->data;
            return 0;
        } else {
            Node<T>* temp = Column[y];
            while (temp->down && temp->down->x < x)
                temp = temp->down;
            if (temp->down && temp->down->x == x)
                return temp->down->data;
            return 0;
        }
    }

    // Tus operaciones serán más lentas si utilizas los métodos públicos en vez de los punteros directamente

    Matrix<T> operator*(T scalar) const {
        Matrix<T> Scalar(rows,columns);
        for (int i = 0; i < rows; ++i) {
            Node<T> *temp = Row[i];
            while (temp->next) {
                temp = temp->next;
                Scalar.set(temp->x, temp->y, temp->data*scalar);
            }
        }
        return Scalar;
    }

    Matrix<T> operator*(Matrix<T> other) const {
        if (columns != other.rows)
            throw out_of_range("Rows/Columns error");
        Matrix<T> Mtx(rows,other.columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.columns; ++j) {
                T sum = 0;
                for (int k = 0; k < columns; ++k)
                    sum += this->operator()(i,k)*other.operator()(k,j);
                Mtx.set(i,j,sum);
            }
        }
        return Mtx;
    }

    Matrix<T> operator+(Matrix<T> other) const {
        if (rows != other.rows || columns != other.columns)
            throw out_of_range("Rows/Columns error");
        Matrix<T> Mtx(rows,columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                T sum =  this->operator()(i,j)+other.operator()(i,j);
                Mtx.set(i,j,sum);
            }
        }
        return Mtx;
    }

    Matrix<T> operator-(Matrix<T> other) const {
        if (rows != other.rows || columns != other.columns)
            throw out_of_range("Rows/Columns error");
        Matrix<T> Mtx(rows,columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                T res =  this->operator()(i,j)-other.operator()(i,j);
                Mtx.set(i,j,res);
            }
        }
        return Mtx;
    }

    Matrix& operator=(const Matrix &that) {
        for (int i = 0; i < that.rows; ++i)
            for (int j = 0; j < that.columns; ++j)
                set(i,j,that.operator()(i,j));
        return (*this);
    }

    Matrix<T> transpose() const {
        Matrix<T> Mtx(columns,rows);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                Mtx.set(j,i,this->operator()(i,j));
        return Mtx;
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            auto temp = Row[i]->next;
            for (int j = 0; j < columns; ++j) {
                if (temp && temp->y == j) {
                    cout << temp->data << "\t\t";
                    temp = temp->next;
                } else
                    cout << 0 << "\t\t";
            } cout << endl;
        } cout << endl;
    }

    ~Matrix() {
        for (auto y : Column)
            delete y;
        for (auto x : Row)
            killRow(x);
    }
};

#endif //SPARSE_MATRIX_MATRIX_H