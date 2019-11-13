#include "matrix.h"
#include "tester/tester.h"

int main() {
    //Tester::execute();
    cout << "Hello\n";
    Matrix<int> M(2,2);
    M.print();
    M.set(1,1,11);
    M.set(0,1,01);
    M.print();
    M.print_x(1);
    M.set(1,1,12);
    M.print();
    M.print_x(1);
    auto M2 = M*2;
    M2.print();
    M2.print_x(1);
    auto M3 = M2-M;
    M3.print();
    M3.print_x(1);
//    cout << endl << M(1,0) << endl;
    return EXIT_SUCCESS;
}

