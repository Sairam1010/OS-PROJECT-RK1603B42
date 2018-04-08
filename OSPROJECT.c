#include<stdio.h>
#include<stdlib.h>
struct process
{
    int arrivalTime;
    int waitTime;
    int priority;
    int turnaround;
    int id;
    int burstTime;
    struct process *link;
}*start = NULL, *temp = NULL, *rear = NULL, *prev = NULL, *next = NULL, *chosen = NULL;

//Variable to automatically assign ID to a process
int idT = 1;
//Number Of Processes
int nOfPr;
//Total Time collapsed
int totalTime = 0;

//Function to add processes in the queue
void enqueue()
{
    temp = (struct process*) malloc(sizeof(struct process));
    printf("\nEnter arrival time : ");
    scanf("%d", &(temp->arrivalTime));
    printf("\nEnter burst time : ");
    scanf("%d", &(temp->burstTime));
    if ((temp->burstTime <= 0) || (temp->arrivalTime < 0))
    {
        printf("Wrong process details entered\n");
        exit(0);
    }
    temp->priority = 0;
    temp->waitTime = 0;
    temp->id = idT;
    temp->link = NULL;
    idT++;
    if (start == NULL)
    {
        start = temp;
        rear = temp;
    }
    else
    {
        rear->link = temp;
        rear = rear->link;
    }
}
//Function to check if addition of processes in queue is working correctly
void show()
{
    temp = start;
    if (start == NULL)
    {
        printf("Queue empty");
    }
    else
    {
        while(temp != NULL)
        {
            printf("%d", temp->id);
            temp = temp->link;
        }
    }
}
//Function to find a process which is ready for execution and with top priority
void find()
{
    //printf("find");
    temp = start;
    chosen = NULL;
    while (temp != NULL)
    {
        if (chosen == NULL)
        {
            if (temp->arrivalTime <= totalTime)
            {
                chosen = temp;
            }
        }
        else
        {
            if ((chosen->priority > temp->priority) && (temp->arrivalTime <= totalTime))
            {
                chosen = temp;
            }
        }
        temp = temp->link;
    }
}
//Calculate the priorities of all processes
void findPriority()
{
    //printf("Prio");
    int i;
    temp = start;
    while(temp != NULL)
    {
        temp->priority = (1 + temp->waitTime) / temp->burstTime;
        temp = temp->link;
    }
}
//Remove a process once it has finished execution
void removeProcess()
{
    if (chosen == start)
    {
        start = start = start->link;
    }
    else if (chosen != NULL)
    {
        prev = start;
        while(prev ->link != chosen)
        {
            prev = prev->link;
        }
        prev->link = chosen->link;
        chosen->link = NULL;
    }
}
//Function to increase waiting time of all the processes that have arrived
void increaseWaiting(int cycles)
{
    temp = start;
    while(temp != NULL)
    {
        if (temp->arrivalTime <= totalTime)
        {
            temp->waitTime += cycles;
        }
        temp = temp->link;
    }
}
int main()
{
   float avgTurn = 0, avgWait = 0;
   printf("Enter no. of processes( > 1) : ");
   scanf("%d",&nOfPr);
   int loc = nOfPr;
   //Processes should always be greater than 1. Or else no sheduling is required
   if (nOfPr <= 1)
   {
       printf("No. of processes is less than 2");
       //Exit if condition not met
       exit(0);
   }
   int i;
   //Adding the processes
   for (i = 0;i < nOfPr;i++)
   {
       enqueue();
   }
    //Keep executing until all processes have finished i.e. queue becomes empty
    while (start != NULL)
    {
        //Calculate priority at each step as priority is dynamic
        findPriority();
        //Finding the process with top priority
        find();
        //If no process has arrived right now. Then increment total time and try searching for processes again.
        if (chosen == NULL)
        {
            totalTime++;
            //Increase waiting time of all arrived processes by 1 cycle
            increaseWaiting(1);
        }
        //If process found then execute it.
        else
        {
            int localBurst = chosen->burstTime;
            totalTime += chosen->burstTime;
            chosen->turnaround = totalTime - chosen->arrivalTime;
            //Print to user the information about the process
            printf("\n\nProcess %d with \n\nWaiting time %d\n\nTurnaround time %d\n\nended at %d\n", chosen->id, chosen->waitTime,chosen->turnaround,totalTime);
            avgTurn += chosen->turnaround;
            avgWait += chosen->waitTime;
            //Remove the process
            removeProcess();
            //Decrement the number of processes in the queue
            nOfPr--;
            //Increase waiting time of all arrived processes by the burst time of executed process
            increaseWaiting(localBurst);
        }
    }
    avgTurn = avgTurn/loc;
    avgWait = avgWait/loc;
    printf("\nAverage turnaround time: %f \nAverage Waiting time: %f",avgTurn,avgWait);
}
