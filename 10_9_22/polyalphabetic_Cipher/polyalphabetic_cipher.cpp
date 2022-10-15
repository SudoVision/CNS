#include <bits/stdc++.h>
using namespace std;

void Encryption(string &str, string key)
{
    int n = key.size();
    int count = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
            continue;
        str[i] = 'a' + (str[i] - 97 + key[count % n] - 97) % 26;
        count++;
    }
}
void Decryption(string &str, string key)
{
    int n = key.size();
    int count = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
            continue;
        str[i] = 'a' + (str[i] - 97 - (key[count % n] - 97) + 26) % 26;
        count++;
    }
}

string remove_spaces(string &str)
{
    string temp = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (!(str[i] == ' '))
            temp += str[i];
    }
    return temp;
}

int main()
{
    cout << "\nSoumyadip Payra\nCSE A\nRoll 197178\n";
    cout << "\nEnter the plain text to be encrypted : ";

    string str, key, temp;
    cout << "Enter the plain text to be Encryptioned : " << endl;
    getline(cin, str);
    temp = remove_spaces(str);
    cout << "Enter the key : " << endl;

    cin >> key;
    Encryption(temp, key);
    cout << "On Encryptionion the cipher text is : " << temp << endl;
    Decryption(temp, key);
    cout << "After Decryptionion the plain text is : " << temp << endl;
    return 0;
}