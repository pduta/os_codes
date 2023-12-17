#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<cstdlib>

using namespace std;

int main()
{
    char sourceFile[20], destFile[20];
    cout << "Source File:";
    cin >> sourceFile;
    cout << "Destination File:";
    cin >> destFile;

    int fd1 = open(sourceFile, O_RDONLY);
    if (fd1 < 0) {
        cout << "Error in opening file ";
        exit(1);
    }

    int fd2 = open(destFile, O_CREAT | O_WRONLY, 0666);
    if (fd2 < 0) {
        cout << "Error in creating file ";
        exit(1);
    }

    char buf[500];
    int count;

    while (count = read(fd1, buf, sizeof(buf))) {
        if (write(fd2, buf, count) < 0)
            cout << "Error in writing";
    }

    close(fd1);
    close(fd2);

    return 0;
}
