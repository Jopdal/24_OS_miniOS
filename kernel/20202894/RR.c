#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep 함수를 사용하기 위해 필요한 헤더 파일
#include <time.h>

#define MAX_PROCESSES 10
#define TIME_SLICE 1

typedef struct Process {
    int id;
    int remaining_time;
} Process;

void run_round_robin(Process processes[], int num_processes) {
    int total_remaining = num_processes;
    int current_process = 0;

    while (total_remaining > 0) {
        if (processes[current_process].remaining_time > 0) {
            printf("Processing process %d\n", processes[current_process].id);
            sleep(TIME_SLICE);
            processes[current_process].remaining_time -= TIME_SLICE;
            
            if (processes[current_process].remaining_time <= 0) {
                printf("Process %d completed\n", processes[current_process].id);
                total_remaining--;
            }
        }

        current_process = (current_process + 1) % num_processes;
    }
}

int rr() {
    int num_processes, i;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    if (num_processes > MAX_PROCESSES) {
        printf("Exceeded maximum number of processes\n");
        return 1;
    }

    srand(time(NULL));

    for (i = 0; i < num_processes; i++) {
        processes[i].id = i+1;
        processes[i].remaining_time = rand() % 10 + 1; // Generating random processing time (1 to 10)
    }

    printf("Starting Round Robin Scheduling...\n");
    run_round_robin(processes, num_processes);

    return 0;
}
