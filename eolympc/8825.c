#include <stdio.h>
//https://www.eolymp.com/ru/submissions/12682676
double pow(double a, int n) {
    double result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= a;
    }
    return result;
}

double f(double x) {
    double a = pow(x, 3);
    double b = (5 * pow(x, 2)) / 7.0;
    double c = 9.0 * x;
    double d = 3.0 / x;
    return a - b + c - d + 1.0;
}

int main() {
    double x;
    scanf("%lf", &x);

    printf("%.3f", f(x));
}