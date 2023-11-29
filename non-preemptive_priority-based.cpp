#include <iostream>

using namespace std;

class ProcessScheduler {
private:
    struct Process {
        int pid;
        double priority;
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

    static int comparisonDesc(const void *a, const void *b) {
        return ((Process *)a)->priority < ((Process *)b)->priority;
    }

    static int comparisonAsc(const void *a, const void *b) {
        return ((Process *)a)->pid > ((Process *)b)->pid;
    }

    void computeWaitingTime() {
        for (int i = 0; i < processCount; ++i) {
            for (int j = i + 1; j < processCount; ++j) {
                if (processes[i].priority < processes[j].priority) {
                    // Swap processes[i] and processes[j]
                    Process temp = processes[i];
                    processes[i] = processes[j];
                    processes[j] = temp;
                }
            }
        }

        processes[0].waitingTime = 0;
        for (int i = 0; i < processCount - 1; i++)
            processes[i + 1].waitingTime =
                processes[i].burstTime + processes[i].waitingTime - processes[i].arrivalTime;
    }

    void computeTurnAroundTime() {
        for (int i = 0; i < processCount; i++)
            processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitingTime;

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

    void printAverageTimes(const char *unit) {
        double totalWaitingTime = 0.0;
        double totalTurnAroundTime = 0.0;
        computeWaitingTime();
        computeTurnAroundTime();

        cout << "Process ID\tPriority\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n";
        cout << "--------------------------------------------------------"
             << "-----------------------------------------\n";

        for (int i = 0; i < processCount; i++) {
            totalWaitingTime += processes[i].waitingTime;
            totalTurnAroundTime += processes[i].turnAroundTime;
            cout << processes[i].pid << "\t\t" << processes[i].priority << "\t\t"
                 << processes[i].burstTime << unit << "\t\t" << processes[i].arrivalTime << unit
                 << "\t\t" << processes[i].waitingTime << unit << "\t\t"
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
            cout << "Priority for Process " << i + 1 << ": ";
            cin >> processes[i].priority;
        }
    }
};

int main() {
    ProcessScheduler scheduler;
    scheduler.initializeProcesses();

    scheduler.printAverageTimes("units");

    return 0;
}
