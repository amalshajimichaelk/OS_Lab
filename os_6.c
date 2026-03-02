#include <stdio.h>

int main() {

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int p[n], at[n], bt[n], pr[n];

    for(int i = 0; i < n; i++) {
        p[i] = i + 1;

        printf("\nConfiguring Process %d (PID: %d)\n", i+1, p[i]);

        printf("Enter Arrival Time : ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time   : ");
        scanf("%d", &bt[i]);

        printf("Enter Priority     : ");
        scanf("%d", &pr[i]);
    }

    /* ============================================================
                        1. FCFS
    ============================================================ */

    int at_fcfs[n], bt_fcfs[n], p_fcfs[n];
    int ct[n], tat[n], wt[n];

    for(int i = 0; i < n; i++) {
        at_fcfs[i] = at[i];
        bt_fcfs[i] = bt[i];
        p_fcfs[i]  = p[i];
    }

    // Sort by Arrival Time
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(at_fcfs[i] > at_fcfs[j]) {
                int temp;

                temp = at_fcfs[i]; at_fcfs[i] = at_fcfs[j]; at_fcfs[j] = temp;
                temp = bt_fcfs[i]; bt_fcfs[i] = bt_fcfs[j]; bt_fcfs[j] = temp;
                temp = p_fcfs[i];  p_fcfs[i]  = p_fcfs[j];  p_fcfs[j]  = temp;
            }
        }
    }

    int time = 0;
    float avg_wt_fcfs = 0;

    for(int i = 0; i < n; i++) {

        if(time < at_fcfs[i])
            time = at_fcfs[i];

        ct[i]  = time + bt_fcfs[i];
        tat[i] = ct[i] - at_fcfs[i];
        wt[i]  = tat[i] - bt_fcfs[i];

        time = ct[i];
        avg_wt_fcfs += wt[i];
    }

    avg_wt_fcfs /= n;

    printf("\n--- FCFS Output ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p_fcfs[i], at_fcfs[i], bt_fcfs[i], ct[i], tat[i], wt[i]);

    printf("Average Waiting Time (FCFS) = %.2f\n", avg_wt_fcfs);



    /* ============================================================
                        2. SJF (Non-Preemptive)
    ============================================================ */

    int done[n];
    for(int i = 0; i < n; i++) done[i] = 0;

    time = 0;
    int completed = 0;
    float avg_wt_sjf = 0;

    printf("\n--- SJF (Non-Preemptive) Output ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    while(completed < n) {

        int shortest = -1;
        int min_bt = 9999;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && done[i] == 0 && bt[i] < min_bt) {
                min_bt = bt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
            continue;
        }

        int completion = time + bt[shortest];
        int turnaround = completion - at[shortest];
        int waiting = turnaround - bt[shortest];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[shortest], at[shortest], bt[shortest],
               completion, turnaround, waiting);

        time = completion;
        done[shortest] = 1;
        completed++;

        avg_wt_sjf += waiting;
    }

    avg_wt_sjf /= n;
    printf("Average Waiting Time (SJF) = %.2f\n", avg_wt_sjf);



    /* ============================================================
                        3. Priority (Non-Preemptive)
    ============================================================ */

    for(int i = 0; i < n; i++) done[i] = 0;

    time = 0;
    completed = 0;
    float avg_wt_priority = 0;

    printf("\n--- Priority (Non-Preemptive) Output ---\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    while(completed < n) {

        int highest = -1;
        int max_pr = -9999;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && done[i] == 0 && pr[i] > max_pr) {
                max_pr = pr[i];
                highest = i;
            }
        }

        if(highest == -1) {
            time++;
            continue;
        }

        int completion = time + bt[highest];
        int turnaround = completion - at[highest];
        int waiting = turnaround - bt[highest];

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[highest], at[highest], bt[highest], pr[highest],
               completion, turnaround, waiting);

        time = completion;
        done[highest] = 1;
        completed++;

        avg_wt_priority += waiting;
    }

    avg_wt_priority /= n;
    printf("Average Waiting Time (Priority) = %.2f\n", avg_wt_priority);



    /* ============================================================
                        4. Round Robin (Quantum = 3)
    ============================================================ */

    int rt[n];
    for(int i = 0; i < n; i++)
        rt[i] = bt[i];

    time = 0;
    completed = 0;
    float avg_wt_rr = 0;
    int quantum = 3;

    int finish[n];

    while(completed < n) {

        int executed = 0;

        for(int i = 0; i < n; i++) {

            if(at[i] <= time && rt[i] > 0) {

                executed = 1;

                if(rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                }
                else {
                    time += rt[i];
                    finish[i] = time;
                    rt[i] = 0;
                    completed++;
                }
            }
        }

        if(!executed)
            time++;
    }

    printf("\n--- Round Robin (Quantum = 3) Output ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {

        int turnaround = finish[i] - at[i];
        int waiting = turnaround - bt[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i], finish[i], turnaround, waiting);

        avg_wt_rr += waiting;
    }

    avg_wt_rr /= n;
    printf("Average Waiting Time (RR) = %.2f\n", avg_wt_rr);



    /* ============================================================
                        Final Comparison
    ============================================================ */

    float min = avg_wt_fcfs;
    char best[20] = "FCFS";

    if(avg_wt_sjf < min) {
        min = avg_wt_sjf;
        sprintf(best, "SJF");
    }

    if(avg_wt_priority < min) {
        min = avg_wt_priority;
        sprintf(best, "Priority");
    }

    if(avg_wt_rr < min) {
        min = avg_wt_rr;
        sprintf(best, "Round Robin");
    }

    printf("\n--- Overall Comparison ---\n");
    printf("Best Algorithm: %s (Average WT = %.2f)\n", best, min);

    return 0;
}
