#include<math.h>
#include <stdio.h>

double f(double x, double y) {
    double a = 2 * x * y / (sqrt(pow(x,2) + pow(y,2)));
    double b = pow(x + y - 1, 2) / (x * y);
    return a - b;
}

int main() {
    double x;
    double y;
    scanf("%lf %lf", &x, &y);

    printf("%.3f", f(x, y));
}