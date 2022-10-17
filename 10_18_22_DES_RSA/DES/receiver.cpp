#include "decryption.h"

int main()
{

    findInverse();
    charToBinaryMap();
    binaryToCharMap();
    vector<int> keyBin = convertStringToBin(key);

    mkfifo("fifo", 0666);

    int rfd = open("fifo", O_RDONLY);

    while (1)
    {
        struct pollfd pfd[1];
        pfd[0].fd = rfd;
        pfd[0].events = POLLIN;
        poll(pfd, 1, -1);

        if (pfd[0].revents & POLLIN)
        {
            char buff[100];
            read(rfd, buff, sizeof(buff));

            vector<int> msg(64);
            for (int i = 0; i < 64; i++)
                msg[i] = buff[i] - '0';
            cout << "Encrypted message\n";
            printVec(msg);
            DES(msg, keyBin);
            cout << "Decrpyted message in binary\n";
            printVec(msg);
            cout << "Decrpyted message = " << convertBinToString(msg) << "\n";
        }
    }
    return 0;
}
