#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 10

void fcfs(int n, int bt[], int at[]) {

   int pid[MAX], wt[MAX], tat[MAX];

   // Assign process IDs
   for (int i = 1; i <= n; i++) {
      pid[i] = i;
    }

   // Sort by arrival time
   for (int i = 1; i <= n - 1; i++) {
      for (int j = i + 1; j <= n; j++) {
         if (at[i] > at[j]) {
               swap(at[i], at[j]);
               swap(bt[i], bt[j]);
               swap(pid[i], pid[j]);
         }
      }
   }

   int currentTime = 0;

   cout << "\nProcess\tAT\tBT\tWT\tTAT\n";

   for (int i = 1; i <= n; i++) {
      if (currentTime < at[i])
         currentTime = at[i]; // CPU idle if process not yet arrived

      wt[i] = currentTime - at[i];
      tat[i] = wt[i] + bt[i];

      currentTime += bt[i]; //Very important
      

      cout << "P" << pid[i] << "\t" 
            << at[i] << "\t" 
            << bt[i] << "\t" 
            << wt[i] << "\t" 
            << tat[i] << endl;
   }

}

int main() {
   int n, bt[MAX], at[MAX];

   cout << "Enter number of processes: ";
   cin >> n;

   cout << "Enter Burst Times:\n";
   for (int i = 1; i <= n; i++) {
      cout << "Process " << i << ": ";
      cin >> bt[i];
   }

   cout << "Enter Arrival Times:\n";
   for (int i = 1; i <= n; i++) {
      cout << "Process " << i << ": ";
      cin >> at[i];
   }

   fcfs(n, bt, at);

   return 0;
}
