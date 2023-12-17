#include <iostream>
#include <sys/sysinfo.h>

using namespace std;

void printMemoryInfo(const struct sysinfo& si) {
    cout << "Total RAM: " << si.totalram / (1024 * 1024) << " MB" << endl;
    cout << "Free RAM: " << si.freeram / (1024 * 1024) << " MB" << endl;
    cout << "Used RAM: " << (si.totalram - si.freeram) / (1024 * 1024) << " MB" << endl;
}

int main() {
    struct sysinfo si;

    if (sysinfo(&si) != 0) {
        cerr << "Error fetching system information." << endl;
        return 1;
    }

    cout << "System Information:" << endl;
    printMemoryInfo(si);

    return 0;
}
