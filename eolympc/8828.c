#include<math.h>
#include <stdio.h>

//https://www.eolymp.com/ru/submissions/12682722

double f(double x) {
    double a = (2 * x - 1) / pow(x,2);
    double b = sqrt(pow(x,2) + 1) /2;
    return a + b;
}

int main() {
    double x;
    scanf("%lf ", &x);

    printf("%.3f", f(x));
}