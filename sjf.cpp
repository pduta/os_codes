#include <iostream>

using namespace std;

class ProcessScheduler {
private:
    struct Process {
        int pid;
        double burstTime;
        double arrivalTime;
        double waitingTime;
        double turnAroundTime;
    };

    Process *processes;
    int processCount;

public:
    ProcessScheduler() : processes(nullptr), processCount(0) {}

    ~ProcessScheduler() {
        delete[] processes;
    }

    void sortByArrivalTime() {
        for (int i = 0; i < processCount - 1; ++i) {
            for (int j = 0; j < processCount - i - 1; ++j) {
                if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                    // Swap processes[j] and processes[j + 1]
                    Process temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }
    }

    void sortForSJF() {
        // Simple implementation for SJF scheduling
        for (int i = 0; i < processCount - 1; ++i) {
            for (int j = i + 1; j < processCount; ++j) {
                if (processes[i].burstTime > processes[j].burstTime) {
                    // Swap processes[i] and processes[j]
                    Process temp = processes[i];
                    processes[i] = processes[j];
                    processes[j] = temp;
                }
            }
        }
    }

    void sortByPID() {
        for (int i = 0; i < processCount - 1; ++i) {
            for (int j = 0; j < processCount - i - 1; ++j) {
                if (processes[j].pid > processes[j + 1].pid) {
                    // Swap processes[j] and processes[j + 1]
                    Process temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }
    }

    void computeWaitingTime() {
        double startTime = 0.0;
        processes[0].waitingTime = 0;
        for (int i = 1; i < processCount; i++) {
            startTime += processes[i - 1].burstTime;
            processes[i].waitingTime = startTime - processes[i].arrivalTime;
        }
    }

    void computeTurnAroundTime() {
        for (int i = 0; i < processCount; i++)
            processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;
    }

    void printAverageTimes(const char *unit) {
        double totalWaitingTime = 0.0;
        double totalTurnAroundTime = 0.0;

        for (int i = 0; i < processCount; i++) {
            totalWaitingTime += processes[i].waitingTime;
            totalTurnAroundTime += processes[i].turnAroundTime;
        }

        cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n";
        cout << "--------------------------------------------------------"
                "-------------------------\n";

        for (int i = 0; i < processCount; i++) {
            cout << processes[i].pid << "\t\t" << processes[i].burstTime << unit
                 << "\t\t" << processes[i].arrivalTime << unit << "\t\t"
                 << processes[i].waitingTime << unit << "\t\t"
                 << processes[i].turnAroundTime << unit << "\n";
        }

        cout << "\nAverage Waiting Time = " << totalWaitingTime / processCount << unit;
        cout << "\nAverage Turn-Around time = " << totalTurnAroundTime / processCount << unit
             << "\n";
    }

    void initializeProcesses() {
        cout << "Enter Time Unit: ";
        char unit[4] = {'\0'};
        cin.getline(unit, 4);

        cout << "Enter Number of Processes: ";
        cin >> processCount;

        processes = new Process[processCount];

        for (int i = 0; i < processCount; i++) {
            processes[i].pid = i + 1;
            cout << "Burst Time for Process " << i + 1 << ": ";
            cin >> processes[i].burstTime;
            cout << "Arrival Time for Process " << i + 1 << ": ";
            cin >> processes[i].arrivalTime;
        }
    }
};

int main() {
    ProcessScheduler scheduler;
    scheduler.initializeProcesses();

    scheduler.sortByArrivalTime();
    scheduler.sortForSJF();
    scheduler.computeWaitingTime();
    scheduler.computeTurnAroundTime();
    scheduler.sortByPID();

    scheduler.printAverageTimes("units");

    return 0;
}
