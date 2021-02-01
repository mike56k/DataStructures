#include <iostream>
#include <algorithm>

using namespace std;

void Sum100() {
    int sum = 0, k = 101;
    while (--k) {
        sum += k;
    }
    cout << "Sum is " << sum << endl;
}

int main() {

    Sum100();

    return 0;
}