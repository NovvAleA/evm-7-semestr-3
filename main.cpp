#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
//S = 1, (p,q) = (2,1), r = 3

double epsilon_d(){ // Вычисление машинного эпсилон double
    double eps = 1.;
    while (1. + eps / 2 > 1.){
        eps = eps / 2.;
    }
    return eps;
}
double du(char* f, double x) { // функция для дифференцирования
    if (string(f) == "sin(x)") {
        return cos(x);
    }
    if (string(f) == "10^5*sin(x)") {
        return 100000*cos(x);
    }
    if (string(f) == "tan(x)") {
        return 1/(cos(x)*cos(x));
    }
    return 0;
}
double u(char* f, double x) { // функция для дифференцирования
    if (string(f) == "sin(x)") {
        return sin(x);
    }
    if (string(f) == "10^5*sin(x)") {
        return 100000*sin(x);
    }
    if (string(f) == "tan(x)") {
        return tan(x);
    }
    return 0;
}

double h_min(char* f, double meps) { // функция для дифференцирования
    if (string(f) == "sin(x)") {
        return 3.3*pow(meps,0.33333);
    }
    if (string(f) == "10^5*sin(x)") {
        return 3.3*pow(meps,0.33333);
    }
    if (string(f) == "tan(x)") {
        //return pow(meps*2*pow(10.,10),0.33333); //на бумаге такая оценка, но она не работает у меня, поэтому ставлю просто корень из эпсилон
        return 3.3*pow(meps,0.33333);
    }
    return 0;
}

double solver(){
    char list_f[3][15] {"sin(x)", "10^5*sin(x)", "tan(x)"};
    double x0 = 1., u0 = 0, du0 = 0, h = 0, duh = 0, meps = 0, temp;
    int k = 5, i;
    h = pow(10., double(k))*pow(meps,0.5);
    meps = epsilon_d();
    ofstream fout;
    fout.open("diff.out");
    fout <<"S = 1, (p,q) = (2,1), r = 3, x0 = 1.59" << endl;
    h = pow(meps,0.33333);
    for(auto & f : list_f){
        h = pow(10., double(k))*h_min(f,meps);
        u0 = u(f,x0);
        du0 = du(f,x0);
        fout << endl << f <<" h_min  = " << h_min(f,meps) << endl;
        for (i = k; i >= -k; h /= 10., i--){
            duh = (-2*u(f,x0 - h) -3*u(f,x0) + 6*u(f,x0 + h) - u(f,x0 + 2*h)) / (6*h);
            fout  << "h = " << h << ", ошибка = " << fabs((duh - du0) / du0)<<endl;
        }
    }
    fout.close();
    return 0;
}

int main() {
    solver();
    return 0;
}

