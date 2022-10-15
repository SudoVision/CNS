#include<bits/stdc++.h>
using namespace std;

int k=3;

int main()
{
    cout<<"\nSoumyadip Payra\nCSE A\nRoll 197178\n";
    string plain_text;
    cout<<"\nEnter the plain text to be encrypted\n";


    getline(cin,plain_text);
    // cout<<plain_text<<endl;

    string encrypted_text = plain_text;
    for (auto &it : encrypted_text)
        if (it <= 'z' && it >= 'a')
            it = char(int(it) - 32);
    
    // cout<<encrypted_text<<endl;
    // cout<<int('Z')<<endl;
    for(auto &it : encrypted_text)
        if (it <= 'Z' && it >= 'A')
            if ((int(it) + k) <= int('Z'))
                it = char((int(it) + k));
            else
                it = char((int(it) + k) % int('Z') + int('A'));

    cout<<"\nEncrypted text is : \n"<<encrypted_text<<endl;
    return 0;
}