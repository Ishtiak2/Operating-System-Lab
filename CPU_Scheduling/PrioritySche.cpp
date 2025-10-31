#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 10

void priorityScheduling(int n, int bt[], int p[], int prio[])
{
    int wt[MAX], tat[MAX];

    // Sort by priority (lower number = higher priority)
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (prio[i] > prio[j])
            {
                swap(prio[i], prio[j]);
                swap(bt[i], bt[j]);
                swap(p[i], p[j]);
            }
        }
    }

    cout << "\nPR\tBT\tPriority\tWT\tTAT\n";

    for (int i = 1; i <= n; i++)
    {
        wt[i] = 0;
        tat[i] = 0;

        for (int j = 1; j < i; j++)
        {
            wt[i] += bt[j];
        }

        tat[i] = wt[i] + bt[i];

        cout << p[i] << "\t" << bt[i] << "\t" << prio[i] << "\t\t" << wt[i] << "\t" << tat[i] << endl;
    }
}

int main()
{
    int n, bt[MAX], p[MAX], prio[MAX];

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Burst Times:\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "Process " << i << ": ";
        cin >> bt[i];
        p[i] = i; // process IDs
    }

    cout << "Enter Priorities (lower number = higher priority):\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "Process " << i << ": ";
        cin >> prio[i];
    }

    priorityScheduling(n, bt, p, prio);

    return 0;
}