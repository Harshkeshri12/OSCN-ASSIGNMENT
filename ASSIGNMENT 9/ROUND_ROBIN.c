#include <stdio.h>

int main() {
    // Fixed Values as per the given data
    int AT[5] = {4, 0, 6, 2, 1};
    int BT[5] = {7, 5, 3, 9, 4};
    int n = 5, tq = 3;

    int remBT[5], CT[5], TAT[5], WT[5];
    int time = 0, completed = 0;
    int q[100], front = 0, rear = 0;
    int visited[5] = {0};

    // Copy Burst Time
    for(int i = 0; i < n; i++)
        remBT[i] = BT[i];

    // Insert first process that arrives at time = 0
    for(int i = 0; i < n; i++) {
        if(AT[i] == 0) {
            q[rear++] = i;
            visited[i] = 1;
        }
    }

    // Round Robin Algorithm
    while(completed < n) {
        if(front == rear) {  // No ready process, CPU idle
            time++;
            continue;
        }

        int i = q[front++]; // Dequeue

        if(remBT[i] > tq) {
            remBT[i] -= tq;
            time += tq;
        } else {
            time += remBT[i];
            remBT[i] = 0;
            CT[i] = time;
            completed++;
        }

        // Enqueue new processes which have arrived
        for(int j = 0; j < n; j++) {
            if(AT[j] <= time && remBT[j] > 0 && visited[j] == 0) {
                q[rear++] = j;
                visited[j] = 1;
            }
        }

        // If process not completed, reinsert in queue
        if(remBT[i] > 0)
            q[rear++] = i;
    }

    // Print Final Correct Output
    printf("\nProcess\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        printf("P%d\t%d\t%d\t%d\n", i+1, CT[i], TAT[i], WT[i]);
    }

    return 0;
}
