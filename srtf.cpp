#include <iostream>
#include <limits>

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

    void computeWaitingTurnaroundTime() {
        double end;
        int smallest, count = 0;
        Process *temp = new Process[processCount + 1];

        for (int i = 0; i < processCount; i++)
            temp[i] = processes[i];

        smallest = processCount + 1;
        temp[smallest].burstTime = numeric_limits<double>::max();
        for (double time = 0; count != processCount; time++) {
            for (int i = 0; i < processCount; i++) {
                if (processes[i].arrivalTime <= time &&
                    processes[i].burstTime < temp[smallest].burstTime &&
                    processes[i].burstTime > 0) {
                    smallest = i;
                }
            }
            temp[smallest].burstTime--;
            if (temp[smallest].burstTime == 0) {
                count++;
                end = time + 1;
                processes[count].waitingTime +=
                    end - processes[smallest].arrivalTime - temp[smallest].burstTime;
                processes[count].turnAroundTime += end - processes[smallest].arrivalTime;
            }
        }

        delete[] temp;
    }

    void printAverageTimes(const char *unit) {
        double totalWaitingTime = 0.0;
        double totalTurnAroundTime = 0.0;
        computeWaitingTurnaroundTime();

        cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n";
        cout << "--------------------------------------------------------"
             << "-------------------------\n";

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
    scheduler.printAverageTimes("units");

    return 0;
}
