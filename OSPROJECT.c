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
int idT = 1;
int nOfPr;
int totalTime = 0;
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
void removeProcess()
{
    //printf("Hey");
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
   printf("Enter no. of processes( > 1) : ");
   scanf("%d",&nOfPr);
   if (nOfPr <= 1)
   {
       printf("No. of processes is less than 2");
       exit(0);
   }
   int i;
   for (i = 0;i < nOfPr;i++)
   {
       enqueue();
   }
    while (start != NULL)
    {
        //printf("Hi");
        findPriority();
        find();
        //printf("Hii");
        if (chosen == NULL)
        {
            //printf("Hiii");
            totalTime++;
            increaseWaiting(1);
        }
        else
        {
            int localBurst = chosen->burstTime;
            totalTime += chosen->burstTime;
            chosen->turnaround = totalTime - chosen->arrivalTime;
            printf("\n\nProcess %d with \n\nWaiting time %d\n\nTurnaround time %d\n\nended at %d\n", chosen->id, chosen->waitTime,chosen->turnaround,totalTime);
            removeProcess();
            nOfPr--;
            increaseWaiting(localBurst);
        }
    }
}
