#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 10

void sjf(int n, int bt[], int p[])
{
    int wt[MAX], tat[MAX];

    // Sort by burst time (SJF)
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            if (bt[j] > bt[j + 1])
            {
                swap(bt[j], bt[j + 1]);
                swap(p[j], p[j + 1]);
            }
        }
    }


    cout << "\nPR\tBT\tWT\tTAT\n";

    for (int i = 1; i <= n; i++)
    {
        wt[i] = 0;
        tat[i] = 0;

        for (int j = 1; j < i; j++)
        {
            wt[i] += bt[j];
        }

        tat[i] = wt[i] + bt[i];
        
        cout << p[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

}

int main()
{
    int n, bt[MAX], p[MAX];

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Burst Times:\n";
    for (int i = 1; i <= n; i++)
    {
        cout << "Process " << i << ": ";
        cin >> bt[i];
        p[i] = i; // process IDs
    }

    sjf(n, bt, p);

    return 0;
}
