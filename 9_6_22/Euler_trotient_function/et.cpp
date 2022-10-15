#include<bits/stdc++.h>
using namespace std;

long long phi(long long num)
{
    long long count = 1;

    for (long long i = 2; i < num; i++)
    {
        if (__gcd(i, num) == 1)
            count++;
    }
    return count;
}

int main()
{
    long long num;
    cout<<"\nEnter the number :\n";
    cin>>num;
    long long phi_t;
    for(long long i = 1; i<=num; i++)
    {
        phi_t = phi(i);
        cout<<"Phi("<<i<<") = "<<phi_t;
        if(phi_t == i-1) cout<<" \t"<<i<<" is prime";
        cout<<endl<<endl;
    }
    return 0;
}