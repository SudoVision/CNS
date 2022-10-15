#include <bits/stdc++.h>
using namespace std;

void remove_spaces(string &str)
{
    for (int i = 0; i < str.size(); i++)
        if (str[i] == ' ')
        {
            str.erase(str.begin() + i);
            i--;
        }
}
void remove_dup(string &str)
{
    vector<int> frequency(26, 0);
    for (int i = 0; i < str.size(); i++)
    {
        frequency[str[i] - 'a']++;
        if (frequency[str[i] - 'a'] > 1)
        {
            str.erase(str.begin() + i);
            i--;
        }
    }
}
void Generate_playfair_matrix(char mat[][5], string key)
{
    vector<char> v(26);
    for (int i = 0; i < 26; i++)
        v[i] = 'a' + i;
    v.erase(v.begin() + 9); // here we remove j
    int index1 = 0, index2 = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (index1 < key.size())
            {
                mat[i][j] = key[index1];
                v.erase(find(v.begin(), v.end(), key[index1]));
                index1++;
            }
            else
            {
                mat[i][j] = v[index2];
                index2++;
            }
        }
    }
}
void printMatrix(char mat[][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}
void searchel(char mat[][5], char ch, int &ri, int &ci)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (mat[i][j] == ch)
            {
                ri = i;
                ci = j;
            }
}
void encrypt(char mat[][5], string &str)
{
    if (str.size() % 2)
        str += 'z'; // bogus letter
    int fr, fc, sr, sc;
    for (int i = 0; i < str.size(); i += 2)
    {
        if (str[i] == str[i + 1])
            str[i + 1] = 'x'; // bogus letter
        if (str[i] == 'j')
            str[i] = 'i';
        if (str[i + 1] == 'j')
            str[i + 1] = 'i';
        searchel(mat, str[i], fr, fc);
        searchel(mat, str[i + 1], sr, sc);
        if (fc == sc)
        {
            fr = (fr + 1) % 5;
            sr = (sr + 1) % 5;
        }
        else if (fr == sr)
        {
            fc = (fc + 1) % 5;
            sc = (sc + 1) % 5;
        }
        else
            swap(fc, sc);
        str[i] = mat[fr][fc];
        str[i + 1] = mat[sr][sc];
    }
}
int main()
{
    cout << "\nSoumyadip Payra\nCSE A\nRoll 197178\n";
    cout << "\nEnter the plain text to be encrypted : ";

    string key, str;
    getline(cin, str);
    cout << "\nEnter the key : " << endl;
    cin >> key;
    char mat[5][5];
    remove_spaces(str);
    remove_dup(key);
    Generate_playfair_matrix(mat, key);
    cout << "\nThe PlayFair Matrix is : \n" << endl;
    printMatrix(mat);
    encrypt(mat, str);
    cout << "\nAfter Encryption the cipher text is : " << str << endl;
    return 0;
} 