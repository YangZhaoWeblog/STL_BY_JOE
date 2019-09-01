#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <numeric>
using namespace std;

int main()
{
    vector<int> a = { 3, 2, 7, 4, 2, 6, 9, 99};

    int sum_val = 0;
    for_each(a.begin(), a.end(), [&sum_val](const int& val)
    {
        cout << val << endl;
        sum_val += val;
    });
    cout << "summ val is: " << sum_val << endl;
    return 0;
}


