#include <iostream>

using namespace std;

class Process {
public:
    int pid;
    double burstTime;
    double arrivalTime;
    double waitingTime;
    double turnAroundTime;

    Process(int id, double burst, double arrival)
        : pid(id), burstTime(burst), arrivalTime(arrival), waitingTime(0.0), turnAroundTime(0.0) {}

    // Default constructor needed for dynamic memory allocation
    Process() {}
};

void sortByArrivalTime(Process *processes, int processCount) {
    for (int i = 0; i < processCount; ++i) {
        for (int j = i + 1; j < processCount; ++j) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                // Swap processes[i] and processes[j]
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void sortByPID(Process *processes, int processCount) {
    for (int i = 0; i < processCount; ++i) {
        for (int j = i + 1; j < processCount; ++j) {
            if (processes[i].pid > processes[j].pid) {
                // Swap processes[i] and processes[j]
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void computeWaitingTime(Process *processes, int processCount) {
    double completionTime = 0.0;
    processes[0].waitingTime = 0.0;
    for (int i = 1; i < processCount; i++) {
        completionTime += processes[i - 1].burstTime;
        processes[i].waitingTime = completionTime - processes[i].arrivalTime;
    }
}

void computeTurnAroundTime(Process *processes, int processCount) {
    for (int i = 0; i < processCount; i++)
        processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
}

void printAverageTimes(Process *processes, int processCount, const char *unit) {
    double totalWaitingTime = 0.0;
    double totalTurnAroundTime = 0.0;

    sortByArrivalTime(processes, processCount);
    computeWaitingTime(processes, processCount);
    computeTurnAroundTime(processes, processCount);
    sortByPID(processes, processCount);

    cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n";
    cout << "--------------------------------------------------------"
            "-------------------------\n";

    for (int i = 0; i < processCount; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
        cout << processes[i].pid << "\t\t" << processes[i].burstTime << unit
             << "\t\t" << processes[i].arrivalTime << unit << "\t\t"
             << processes[i].waitingTime << unit << "\t\t"
             << processes[i].turnAroundTime << unit << "\n";
    }

    cout << "\nAverage Waiting Time = " << totalWaitingTime / processCount << unit;
    cout << "\nAverage Turn-Around time = " << totalTurnAroundTime / processCount << unit
         << "\n";
}

int main() {
    int processCount;
    char unit[4] = {'\0'};

    cout << "Enter Time Unit: ";
    cin.getline(unit, 4);

    cout << "Enter Number of Processes: ";
    cin >> processCount;

    Process *processes = new Process[processCount];

    for (int i = 0; i < processCount; i++) {
        processes[i].pid = i + 1;
        cout << "Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Arrival Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
    }

    cout << "\n";

    printAverageTimes(processes, processCount, unit);

    delete[] processes;

    return 0;
}
