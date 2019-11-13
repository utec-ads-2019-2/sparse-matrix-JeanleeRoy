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
            throw invalid_argument("Node not found");
        } else {
            Node<T>* temp = Column[y];
            while (temp->down && temp->down->x < x)
                temp = temp->down;
            if (temp->down && temp->down->x == x)
                return temp->down->data;
            throw invalid_argument("Node not found");
        }
    }
    Matrix<T> operator*(T scalar) const {

    }
    Matrix<T> operator*(Matrix<T> other) const {

    }
    Matrix<T> operator+(Matrix<T> other) const {

    }
    Matrix<T> operator-(Matrix<T> other) const {

    }
    Matrix<T> transpose() const {

    }
    void print() const {
        cout << "\t\t";
        for (auto i : Column)
            cout << i->data << "\t\t";
        cout << endl;
        for (int i = 0; i < columns; ++i) {
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