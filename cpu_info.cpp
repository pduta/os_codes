#include <iostream>
#include <fstream>
#include <sys/utsname.h>

using namespace std;

void printKernelInfo() {
    struct utsname unameData;

    if (uname(&unameData) != 0) {
        cerr << "Error fetching kernel information." << endl;
        return;
    }

    cout << "Kernel Version: " << unameData.release << endl;
    cout << "System Name: " << unameData.sysname << endl;
    cout << "Node Name: " << unameData.nodename << endl;
    cout << "Machine Architecture: " << unameData.machine << endl;
}

void printCPUInfo() {
    ifstream cpuInfoFile("/proc/cpuinfo");
    if (!cpuInfoFile) {
        cerr << "Error opening /proc/cpuinfo." << endl;
        return;
    }

    const int bufferSize = 256;
    char buffer[bufferSize];

    while (cpuInfoFile.getline(buffer, bufferSize)) {
        cout << buffer << endl;
    }

    cpuInfoFile.close();
}

int main() {
    cout << "Kernel and CPU Information:" << endl;

    cout << "\nKernel Information:" << endl;
    printKernelInfo();

    cout << "\nCPU Information:" << endl;
    printCPUInfo();

    return 0;
}
