#include "ypglpk.hpp"
#include <iostream>

using namespace std;

int main() {
	
    // maximize x+2y-2.5z subject to
    // ** 3x+2y+z  <= 9.9
    // ** -x+z     <= 8.24
    // ** 1.5y-z   <= 4.3
    // ** x-1.3y-z <= 5.3
    ypglpk::set_output(true);
    int n = 3, m = 4;
    vector<vector<double>> A(m, vector<double>(n));
    vector<double> b(m), c(n);
    c[0] = 1; c[1] = 2; c[2] = -2.5;
    A[0][0] = 3; A[0][1] = 2; A[0][2] = 1;     b[0] = 9.9;
    A[1][0] = -1; A[1][2] = 1;                 b[1] = 8.24; 
    A[2][1] = 1.5; A[2][2] = -1;               b[2] = 4.3;
    A[3][0] = 1; A[3][1] = -1.3; A[3][2] = -1; b[3] = 5.3;
    pair<double, vector<double>> res;
    res = ypglpk::linear_programming(A, b, c);
    cout << "\033[1;36m"
        << "LP: max=" << res.first;
    if (res.first == -ypglpk::INF) {
        cout << " INFEASIBLE OR UNBOUNDED";
    } else {
        cout << " with"
            << " x=" << res.second[0] << " y=" << res.second[1]
            << " z=" << res.second[2];
    }
    cout << "\033[0m\n";

    vector<int> vartype(n);
    vartype[0] = GLP_CV;
    vartype[1] = GLP_IV;
    vartype[2] = GLP_IV; // y,z should be integers
    res = ypglpk::mixed_integer_linear_programming(A, b, c, vartype);

    cout << "\033[1;36m"
        << "MILP: max=" << res.first;
    if (res.first == -ypglpk::INF) {
        cout << " INFEASIBLE OR UNBOUNDED";
    } else {
        cout << " with"
            << " x=" << res.second[0] << " y=" << res.second[1]
            << " z=" << res.second[2];
    }
    cout << "\033[0m\n";
}
