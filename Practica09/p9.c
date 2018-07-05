#include <stdio.h>

int main() {
    printf("Doble precisión:\n");
    double x = 665857;
    double y = 470832;
    double z = x*x*x*x -4*y*y*y*y -4*y*y;
    printf("%f\n\n", z);
    printf("Simple precisión:\n");
    float x2 = 665857;
    float y2 = 470832;
    float z2 = x2*x2*x2*x2 -4*y2*y2*y2*y2 -4*y2*y2;
    printf("%f\n\n", z2);
    printf("Long integer precisión:\n");
    long long x3 = 665857;
    long long y3 = 470832;
    long long z3 = x3*x3*x3*x3 -4*y3*y3*y3*y3 -4*y3*y3;
    printf("%lld\n", z3);
}

/*
bc
x = 665857
y = 470832
z = x^4 -4*y^4-4*y^2
z

//////////

Medio 2: Calculadora
Realizar la operación con la calculadora

*/

//gcc -o p9 p9.c
//gcc SumMulMat.c tiempo.c -o SumMulMat
//gcc -O2 SumMulMat.c tiempo.c -o SumMulMat
