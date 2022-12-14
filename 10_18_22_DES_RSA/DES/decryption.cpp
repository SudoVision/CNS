#include "decryption.h"

string key = "DeFdAbBc";

int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2,
              60, 52, 44, 36, 28, 20, 12, 4,
              62, 54, 46, 38, 30, 22, 14, 6,
              64, 56, 48, 40, 32, 24, 16, 8,
              57, 49, 41, 33, 25, 19, 9, 1,
              59, 51, 43, 35, 27, 19, 11, 3,
              61, 53, 45, 37, 29, 21, 13, 5,
              63, 55, 47, 39, 31, 23, 15, 7};

int IPinv[64];

int E[48] = {32, 1, 2, 3, 4, 5,
             4, 5, 6, 7, 8, 9,
             8, 9, 10, 11, 12, 13,
             12, 13, 14, 15, 16, 17,
             16, 17, 18, 19, 20, 21,
             20, 21, 22, 23, 24, 25,
             24, 25, 26, 27, 28, 29,
             28, 29, 30, 31, 32, 1};

int SBoxTable[4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};

map<vector<int>, char> binCharMap;
map<char, vector<int>> charBinMap;

void printVec(vector<int> &in)
{
    for (int i = 0; i < in.size(); i++)
        cout << in[i];
    cout << "\n";
}

void findInverse()
{
    for (int i = 0; i < 64; i++)
        IPinv[IP[i] - 1] = i + 1;
}

int binToDecimal(vector<int> &bin)
{
    int out = 0;
    for (int i = 0; i < bin.size(); i++)
        out = out * 2 + bin[i];
    return out;
}

vector<int> decimalToBin(int dec, int sizeOut)
{
    vector<int> ans(sizeOut, 0);
    int i = sizeOut - 1;
    while (dec > 0)
    {
        ans[i] = (dec % 2);
        dec /= 2;
        i--;
    }
    return ans;
}
void charToBinaryMap()
{
    char c = 'a';
    for (int i = 0; i < 26; i++)
    {
        charBinMap[c] = decimalToBin(i, 8);
        c++;
    }
    c = 'A';
    for (int i = 26; i < 52; i++)
    {
        charBinMap[c] = decimalToBin(i, 8);
        c++;
    }
}
vector<int> convertStringToBin(string s)
{
    vector<int> out;
    for (int i = 0; i < s.size(); i++)
    {
        vector<int> val = charBinMap[s[i]];
        for (int j = 0; j < (val.size()); j++)
            out.push_back(val[j]);
    }
    return out;
}
void binaryToCharMap()
{
    char c = 'a';
    for (int i = 0; i < 26; i++)
    {
        binCharMap[decimalToBin(i, 8)] = c;
        c++;
    }
    c = 'A';
    for (int i = 26; i < 52; i++)
    {
        binCharMap[decimalToBin(i, 8)] = c;
        c++;
    }
}
string convertBinToString(vector<int> in)
{
    string out;
    for (int i = 0; i < in.size(); i += 8)
    {
        vector<int> block(in.begin() + i, in.begin() + i + 8);
        char val = binCharMap[block];
        out.push_back(val);
    }
    return out;
}
void bitwisePermute(vector<int> &plainText, int permuteTable[])
{
    vector<int> ptCopy(plainText);
    for (int i = 0; i < plainText.size(); i++)
        plainText[i] = ptCopy[permuteTable[i] - 1];
}

vector<int> expansionFunction(vector<int> &input)
{
    vector<int> output(48);
    for (int i = 0; i < 48; i++)
        output[i] = input[E[i] - 1];
    return output;
}
void XOR(vector<int> &b1, vector<int> &b2)
{
    for (int i = 0; i < b1.size(); i++)
        b1[i] = b1[i] ^ b2[i];
}
vector<int> SBox(vector<int> &in)
{

    vector<int> row, col(in.begin() + 1, in.end() - 1);
    row.push_back(in[0]);
    row.push_back(in[in.size() - 1]);
    int rowNum = binToDecimal(row), colNum = binToDecimal(col);

    int subValue = SBoxTable[rowNum][colNum];
    return decimalToBin(subValue, 4);
}

vector<int> fFunction(vector<int> &in, vector<int> &roundKey)
{
    vector<int> Eout = expansionFunction(in);
    /*
    cout<<"Expansion fun output: \n";
    printVec(Eout);
    */
    XOR(Eout, roundKey);
    /*
    cout<<"After XOR with subkey: \n";
    printVec(Eout);
    */
    vector<int> outSbox;
    for (int i = 0; i < Eout.size(); i += 6)
    {
        vector<int> block(Eout.begin() + i, Eout.begin() + i + 6);
        /*
        cout<<"SBOX block starting at "<<i<<"\n";
        printVec(block);
        */
        vector<int> outBlock = SBox(block);
        /*
        cout<<"SBOX block output starting at "<<i<<"\n";
        printVec(outBlock);
        */
        for (int j = 0; j < outBlock.size(); j++)
            outSbox.push_back(outBlock[j]);
    }
    int P[32] = {16, 7, 20, 21, 29, 12, 28, 17,
                 1, 15, 23, 26, 5, 18, 31, 10,
                 2, 8, 24, 14, 32, 27, 3, 9,
                 19, 13, 30, 6, 22, 11, 4, 25};

    bitwisePermute(outSbox, P);
    return outSbox;
}

void circularRightShift(vector<int> &in)
{
    int msb = in[in.size() - 1];
    in.pop_back();
    in.insert(in.begin(), msb);
}
void keyTransform(vector<int> &roundKey, int roundNum)
{

    // No rotation in case of round 1
    if (roundNum == 1)
        return;
    // splitting into left and right half
    int mid = roundKey.size() / 2;
    vector<int> left(roundKey.begin(), roundKey.begin() + mid), right(roundKey.begin() + mid, roundKey.end());

    circularRightShift(left);
    circularRightShift(right);

    if (!(roundNum == 2 || roundNum == 9 || roundNum == 16))
    {
        circularRightShift(left);
        circularRightShift(right);
    }
    // preparing input for key schedule next round
    for (int i = 0; i < roundKey.size(); i++)
        roundKey[i] = (i < mid) ? left[i] : right[i - mid];
}
void decryptionRound(vector<int> &in, vector<int> &roundKey)
{

    // splitting into left and right parts
    int mid = in.size() / 2;
    vector<int> left(in.begin(), in.begin() + mid), right(in.begin() + mid, in.end());

    // Applying f function to right half
    vector<int> intermediate = fFunction(right, roundKey);
    /*
    cout<<"after f fun right half is \n";
    printVec(intermediate);
    */
    // XOR of result with left half
    XOR(intermediate, left);

    // output is right half followed by the result above

    int j = 0;
    for (int i = 0; i < right.size(); i++)
        in[j++] = right[i];
    for (int i = 0; i < intermediate.size(); i++)
        in[j++] = intermediate[i];
}
void DES(vector<int> &cipherText, vector<int> &key)
{

    // remove parity bits of key and perform permutation choice
    int PC1[56] = {57, 49, 41, 33, 25, 17, 9, 1,
                   58, 50, 42, 34, 26, 18, 10, 2,
                   59, 51, 43, 35, 27, 19, 11, 3,
                   60, 52, 44, 36, 63, 55, 47, 39,
                   31, 23, 15, 7, 62, 54, 46, 38,
                   30, 22, 14, 6, 61, 53, 45, 37,
                   29, 21, 13, 5, 28, 20, 12, 4};

    int PC2[48] = {14, 17, 11, 24, 1, 5, 3, 28,
                   15, 6, 21, 10, 23, 19, 12, 4,
                   26, 8, 16, 7, 27, 20, 13, 2,
                   41, 52, 31, 37, 47, 55, 30, 40,
                   51, 45, 33, 48, 44, 49, 39, 56,
                   34, 53, 46, 42, 50, 36, 29, 32};

    // PC-1 on key
    vector<int> roundKey(56);

    for (int i = 0; i < 56; i++)
        roundKey[i] = key[PC1[i] - 1];

    // Initial Permutation
    bitwisePermute(cipherText, IP);
    /*
    cout<<"After init permutation: ";
    printVec(plainText);
    */
    for (int i = 0; i < 16; i++)
    {
        keyTransform(roundKey, i + 1);

        vector<int> permutedSubKey(48);
        for (int j = 0; j < 48; j++)
            permutedSubKey[j] = roundKey[PC2[j] - 1];

        decryptionRound(cipherText, permutedSubKey);
        /*
        cout<<"After round "<<(i+1)<<" cipher is \n";
        printVec(cipherText);
        */
    }
    int mid = cipherText.size() / 2;
    for (int i = 0; i < mid; i++)
        swap(cipherText[i], cipherText[i + mid]);
    bitwisePermute(cipherText, IPinv);
}