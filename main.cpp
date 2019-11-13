#include "matrix.h"
#include "tester/tester.h"

int main() {
    //Tester::execute();
    Matrix<int> M(2,2);
    M.print();
    M.set(1,1,11);
    M.set(0,1,01);
    M.print();
    M.set(1,1,12);
    M.print();
    M.set(0,1,0);
    M.print();
    /*auto M2 = M*2;
    M2.print();
    auto M3 = M2-M;
    M3.print();
    auto M4 = M3.transpose();
    M4.print();
    cout << endl << M(1,0) << endl;*/
    return EXIT_SUCCESS;
}

