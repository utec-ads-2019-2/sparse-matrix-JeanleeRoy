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
    //Node<T> *root;
    unsigned rows, columns;
    vector<Node<T>*> Row, Column;

public:
    Matrix(unsigned rows, unsigned columns) : rows{rows}, columns{columns} {
        for (size_t i = 0; i < rows; ++i)
            Row.push_back(new Node<int>(i));
        for (size_t i = 0; i < columns; ++i)
            Column.push_back(new Node<int>(i));
    }

    void set(unsigned x, unsigned y, T data) {
        if (x < 0 || y < 0 || x >= columns || y >= rows)
            throw out_of_range("Out of range");

        Node<T> *temp = Row[x];
        while (temp->next && temp->next->y < y)
            temp = temp->next;
        if (temp->next && temp->next->y == y) {
            if (data != 0) {
                cout << "\nUpdated position (" <<x<<","<<y<<"): " << temp->next->data <<"-->"<<data<<"\n\n";
                temp->next->data = data;
                return;
            } else {
                auto aux = temp->next;
                temp->next = aux->next;
            }
        }
        if (data != 0) {
            auto to_set = new Node<T>(data,x,y);
            to_set->next = temp->next;
            temp->next = to_set;
            cout << "SETx ";
            temp = Column[y];
            while (temp->down && temp->down->x < x)
                temp = temp->down;
            to_set->down = temp->down;
            temp->down = to_set;
            cout << "SETy\n";
        } else {
            temp = Column[y];
            while (temp->down && temp->down->x < x)
                temp = temp->down;
            if (temp->down && temp->down->x == x) {
                auto aux = temp->down;
                temp->down = aux->down;
                delete aux;
                cout << "\nTo Delete position (" <<x<<","<<y<<")\n\n";
                return;
            }
        }
    }
    T operator()(unsigned x, unsigned y) const {
        if (x < y) {
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
    Matrix<T> transpose() const {

    }
    void print() const {
        cout << "\t\t";
        for (auto i : Column)
            cout << i->data << "\t\t";
        cout << endl;
        for (int i = 0; i < rows; ++i) {
            auto temp = Row[i];
            cout << temp->data << "\t\t";
            temp = temp->next;
            while (temp) {
                cout << temp->data << "(" << temp->x << "," << temp->y << ")\t\t";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void print_x(unsigned col) const {
        cout << endl;
        auto temp = Column[col];
        cout << temp->data << endl;
        temp = temp->down;
        while (temp) {
            cout << temp->data << "(" << temp->x << "," << temp->y << ")\n";
            temp = temp->down;
        }
    }

    //~Matrix();
};

#endif //SPARSE_MATRIX_MATRIX_H