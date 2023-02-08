#include <iostream>

int main() {
    int z = 1, y;
    using namespace std;
    for (y = 1; y++ < 9; y++)
    {
        z += y++;
    }
    cout << z << endl << endl;
    
}