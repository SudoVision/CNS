#include "encryption.h"

int main()
{

    cout<<endl<<"\nSoumyadip Payra\nCSE A\nRoll : 197178\n"<<endl;

    findInverse();
    charToBinaryMap();
    vector<int> keyBin = convertStringToBin(key);
    mkfifo("fifo", 0666);

    int wfd = open("fifo", O_WRONLY);

    while (1)
    {
        cout << "Enter message [ 8 characters ] = ";
        string in;
        cin >> in;
        vector<int> msgBin = convertStringToBin(in);
        cout << "Input message as binary:\n";
        printVec(msgBin);
        DES(msgBin, keyBin);

        char buff[100];
        int j = 0;
        for (int i = 0; i < msgBin.size(); i++)
            buff[j++] = (msgBin[i] == 0) ? '0' : '1';
        buff[j] = '\0';
        cout << "\nEncrypted Message = " << buff << "\n";
        write(wfd, buff, sizeof(buff));
    }
    return 0;
}