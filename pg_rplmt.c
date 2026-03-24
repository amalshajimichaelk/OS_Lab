#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

void printSidewaysTable(int ref[], int table[MAX_FRAMES][MAX_PAGES], int status[], int n, int frames) {
    printf("\nReference String: ");
    for (int i = 0; i < n; i++) printf("%d  ", ref[i]);
  
printf("\n\n");
    for (int i = 0; i < frames; i++) {
        printf("Frame %d:        ", i);
        for (int j = 0; j < n; j++) {
            if (table[i][j] == -1) printf("-  ");
            else printf("%d  ", table[i][j]);
        }
        printf("\n");
    }

    printf("\nStatus:         ");
    int faults = 0,hit=0;
    for (int i = 0; i < n; i++) {
        if (status[i] == 0) {
            printf("M  ");
            faults++;
        } else {
            printf("H  ");
            hit ++;
        }
    }
    printf("\n\nTotal Page Faults = %d\n", faults);
    printf("Total Page Hits = %d\n", hit);
}

void fifo(int ref[], int n, int frames) {
    int frame[MAX_FRAMES], table[MAX_FRAMES][MAX_PAGES], status[MAX_PAGES];
    int index = 0;

    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) hit = 1;
        }

        if (!hit) {
            frame[index] = ref[i];
            index = (index + 1) % frames;
            status[i] = 0;
        } else {
            status[i] = 1;
        }

        for (int j = 0; j < frames; j++) table[j][i] = frame[j];
    }
    printf("\nFIFO Algorithm");
    printSidewaysTable(ref, table, status, n, frames);
}

void lru(int ref[], int n, int frames) {
    int frame[MAX_FRAMES], table[MAX_FRAMES][MAX_PAGES], status[MAX_PAGES], time[MAX_FRAMES];
    int counter = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        counter++;
        int hit = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                hit = 1;
                time[j] = counter;
            }
        }

        if (!hit) {
            int pos = 0;
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[pos]) pos = j;
            }
            frame[pos] = ref[i];
            time[pos] = counter;
            status[i] = 0;
        } else {
            status[i] = 1;
        }

        for (int j = 0; j < frames; j++) table[j][i] = frame[j];
    }
    printf("\nLRU Algorithm");
    printSidewaysTable(ref, table, status, n, frames);
}

void optimal(int ref[], int n, int frames) {
    int frame[MAX_FRAMES], table[MAX_FRAMES][MAX_PAGES], status[MAX_PAGES];

    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) hit = 1;
        }

        if (!hit) {
            int pos = -1, farthest = i;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                for (int j = 0; j < frames; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == ref[k]) break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }
            if (pos == -1) pos = 0;
            frame[pos] = ref[i];
            status[i] = 0;
        } else {
            status[i] = 1;
        }

        for (int j = 0; j < frames; j++) table[j][i] = frame[j];
    }
    printf("\nOptimal Algorithm:");
    printSidewaysTable(ref, table, status, n, frames);
}

int main() {
    int ref[MAX_PAGES], n, frames, choice,hit;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    while (1) {
        printf("\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\nChoice: ");
        scanf("%d", &choice);
         switch (choice) {
            case 1: 
              fifo(ref, n, frames); 
              break;
            case 2: 
              lru(ref, n, frames); 
              break;
            case 3: 
              optimal(ref, n, frames); 
              break;
            case 4: 
              printf("Exiting\n"); 
              return 0;
            default: 
              printf("Invalid choice!\n");
        }
    }
    return 0;
}
