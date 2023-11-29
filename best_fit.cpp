#include <iostream>

using namespace std;

void bestFit(int* blockSize, int m, int* processSize, int n)
{
    int* allocation = new int[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\nBest-Fit Allocation Strategy\n";
    cout << "=========================================\n";
    cout << "Process No.\tProcess Size\tBlock No.\n";
    cout << "=========================================\n";
    for (int i = 0; i < n; i++)
    {
        cout << "   " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }

    delete[] allocation;
}

int main()
{
    int holes, processes;

    cout << "Enter Number of Holes: ";
    cin >> holes;
    cout << "Enter Number of Processes: ";
    cin >> processes;

    int* holeSizes = new int[holes];
    int* processSizes = new int[processes];

    for (int i = 0; i < holes; i++)
        cin >> holeSizes[i];

    for (int i = 0; i < processes; i++)
        cin >> processSizes[i];

    bestFit(holeSizes, holes, processSizes, processes);

    delete[] holeSizes;
    delete[] processSizes;

    return 0;
}
