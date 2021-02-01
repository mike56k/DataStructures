#include <iostream>
#include <algorithm>

using namespace std;

void SumEven() {
    int sum = 0;
    for (int i = 2; i <= 20; i += 2) {
        sum += i;
    }
    cout << "Sum of even numbers from 2 to 20 is " << sum;
}

int main() {

    SumEven();

    return 0;
}