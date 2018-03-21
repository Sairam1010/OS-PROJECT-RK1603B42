#include<stdio.h>
int numberOfProcesses;
int findMinimum(int priority[], int executed[])
{
    int min = 100000;
    int index = -1;
    int i;
    for (i = 0; i < numberOfProcesses; i++)
    {
        if (min > priority[i] && executed[i] == 0)
        {
            min = priority[i];
            index = i;
        }
    }
    return index;
}
int main()
{
    printf("Enter no. of processes ");
    scanf("%d", &numberOfProcesses);
    int i;
    int burstTime[numberOfProcesses], priority[numberOfProcesses], waitingTime[numberOfProcesses];
    int totalRunningTime = 0;    // Sum of Burst Times of all processes
    int turnaroundTime[numberOfProcesses], executed[numberOfProcesses];
    //Inputting Burst Time from user
    for (i = 0; i < numberOfProcesses; i++)
    {
        printf("Burst Time for process %d : ", i + 1);
        scanf("%d", &burstTime[i]);
        totalRunningTime += burstTime[i];
    }
    //Initialising every process to not executed. 1 -> executed, 0 -> not executed.
    for (i = 0; i < numberOfProcesses; i++)
    {
        executed[i] = 0;
        waitingTime[i] = 0;
    }
    int counter = 0;
    while (counter <= totalRunningTime)
    {
        for (i = 0; i < numberOfProcesses; i++)
        {
            if (executed[i] != 1)
            {
                priority[i] = ((1 + waitingTime[i]) * 100) / burstTime[i];
            }
        }
        int index = findMinimum(priority, executed);
        if (index == -1)
        {
            break;
        }
        printf("\nP%d executes\n", index);
        turnaroundTime[index] = waitingTime[index] + burstTime[index];
        printf("Turnaround Time %d\n", turnaroundTime[index]);
        printf("Waiting Time %d\n", waitingTime[index]);
        executed[index] = 1;
        counter += burstTime[index];
        int j;
        for (j = 0; j < numberOfProcesses; j++)
        {
            if (executed[j] != 1)
            {
                waitingTime[j] += burstTime[index];
            }
        }
    }
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (i = 0; i < numberOfProcesses; i++)
    {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }
    printf("\n\nAverage Turnaround Time: %f\n", (totalTurnaroundTime / (float)numberOfProcesses));
    printf("Average Waiting Time: %f\n", (totalWaitingTime / (float)numberOfProcesses));
    return 0;
}
