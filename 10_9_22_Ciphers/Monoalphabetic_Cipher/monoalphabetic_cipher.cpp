#include <bits/stdc++.h>
using namespace std;

int k = 11;

void encryption(map<char,char> &permute_map, string & encrypted_text)
{
    for (auto &it : encrypted_text)
        if (it <= 'Z' && it >= 'A')
            it = permute_map[it];

    cout << "Encrypted text is : \n"
         << encrypted_text << endl;
}

void decryption(map<char,char> &decrypt_map, string & encrypted_text)
{
    string plain_text;
    plain_text = encrypted_text;
    for(auto &it : plain_text)
    {
        if(it>='A' && it<='Z')
        {
            it = decrypt_map[it];
        }
    }
    cout<< "Decrypted Text is : \n"<< plain_text<<endl;
}

int main()
{
    // cout<<permute_block.size();
    cout << "\nSoumyadip Payra\nCSE A\nRoll 197178\n";
    string plain_text;
    cout << "\nEnter the plain text to be encrypted\n";

    getline(cin, plain_text);
    string encrypted_text = plain_text;
    // cout<<int('A')-int('a');

    for(auto &it : encrypted_text)
        if(it <= 'z' && it >= 'a') it = char(int(it)-32);
    
    int permute_block[26];
    for(int i=0; i<26; i++) permute_block[i] = i;

    for(int i=0; i<k; i++)
        {next_permutation(permute_block, permute_block+5);
        next_permutation(permute_block+5, permute_block + 10);
        next_permutation(permute_block+10, permute_block + 15);
        next_permutation(permute_block+15, permute_block + 20);
        next_permutation(permute_block+20, permute_block + 26);
        next_permutation(permute_block, permute_block + 15);
        next_permutation(permute_block+15, permute_block + 26);
        // next_permutation(permute_block, permute_block + 26);
        }

        // for (int i = 0; i < 26; i++)
        //     cout << permute_block[i] << " ";
        // cout << endl;

        map<char, char> permute_map;
        map<char, char> decrypt_map;
        for (int i = 0; i < 26; i++)
        {
            permute_map[char(65 + i)] = permute_block[i] + 65;
            decrypt_map[permute_block[i]+65] = char(65+i);
        }
            

    
        encryption(permute_map, encrypted_text);
        decryption(decrypt_map,encrypted_text);

        return 0;
}