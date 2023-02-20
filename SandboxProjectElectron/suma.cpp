#include <iostream>
using namespace std;
int suma(int n)
{
    if (n == 0)
        return 0;
    else
        return suma(n / 10) + n % 10;
}
long prim(long n, int d)
{
    if(d == 1) return 1;
    else if(n % d == 0) return 0;
    else return prim(n, d - 1);
}
int main()
{
    int n;
    cin >> n;
    cout << prim(n, n/2);
}