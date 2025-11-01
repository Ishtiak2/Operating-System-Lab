#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 10

void roundRobin(int n, int bt[], int p[], int tq)
{
    int rem_bt[MAX], wt[MAX] = {0}, tat[MAX] = {0};
    float awt = 0, atat = 0;
    int done = 0;
    int currentTime = 0;

    // Copy burst times to remaining burst time array
    for (int i = 1; i <= n; i++)
    {
        rem_bt[i] = bt[i];
    }

    while (done < n)
    {
        bool allDone = true;

        for (int i = 1; i <= n; i++)
        {
            if (rem_bt[i] > 0)
            {
                allDone = false;
                int timeSlice = (rem_bt[i] < tq) ? rem_bt[i] : tq;

                rem_bt[i] -= timeSlice;
                currentTime += timeSlice;

                if (rem_bt[i] == 0)
                {
                    tat[i] = currentTime;
                    wt[i] = tat[i] - bt[i];
                    awt += wt[i];
                    atat += tat[i];
                    done++;
                }
            }
        }

        if (allDone)
            break;
    }

    cout << "\nPR\tBT\tWT\tTAT\n";
    for (int i = 1; i <= n; i++)
    {
        cout << p[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    awt /= n;
    atat /= n;

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << awt;
    cout << "\nAverage Turnaround Time: " << atat << endl;
}

int main()
{
    int n, bt[MAX], p[MAX], tq;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Burst Times:\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "Process " << i << ": ";
        cin >> bt[i];
        p[i] = i; // process IDs
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    roundRobin(n, bt, p, tq);

    return 0;
}