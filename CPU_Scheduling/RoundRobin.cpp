#include <bits/stdc++.h>
using namespace std;
const int MAX = 10;

void round_robin(int n, int bt[], int p[], int qt)
{
    int wt[MAX] = {0}, tat[MAX] = {0}, last[MAX] = {0};
    int bt_orig[MAX];

    for (int i = 0; i < n; i++)
    {
        bt_orig[i] = bt[i]; // store original burst time
    }

    int curr_time = 0;
    int completed = 0;

    while (completed < n)
    {
        bool done = true;
        for (int i = 0; i < n; i++)
        {
            if (bt[i] > 0)
            {
                done = false;
                wt[i] += curr_time - last[i];

                if (bt[i] <= qt)
                {
                    curr_time += bt[i];
                    bt[i] = 0;
                    completed++;
                }

                else
                {
                    curr_time += qt;
                    bt[i] -= qt;
                }

                last[i] = curr_time;
            }
        }

        if (done)
            break;
    }

    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt_orig[i];
    }

    cout << "\nProcess\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << p[i] << "\t" << bt_orig[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }
}

int main()
{
    int n, bt[MAX], p[MAX], qt;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Burst Times:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << ": ";
        cin >> bt[i];
        p[i] = i + 1;
    }

    cout << "Enter Time Quantum: ";
    cin >> qt;

    round_robin(n, bt, p, qt);

    return 0;
}