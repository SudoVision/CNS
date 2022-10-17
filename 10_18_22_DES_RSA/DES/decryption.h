#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

extern string key;

void printVec(vector<int> &in);
void findInverse();
int binToDecimal(vector<int> &bin);
vector<int> decimalToBin(int dec, int sizeOut);
void charToBinaryMap();
vector<int> convertStringToBin(string s);
void binaryToCharMap();
string convertBinToString(vector<int> in);
void bitwisePermute(vector<int> &plainText, int permuteTable[]);
vector<int> expansionFunction(vector<int> &input);
void XOR(vector<int> &b1, vector<int> &b2);
vector<int> SBox(vector<int> &in);
vector<int> fFunction(vector<int> &in, vector<int> &roundKey);
void circularRightShift(vector<int> &in);
void keyTransform(vector<int> &roundKey, int roundNum);
void decryptionRound(vector<int> &in, vector<int> &roundKey);
void DES(vector<int> &cipherText, vector<int> &key);