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
    temp = start;
    chosen = start;
    while (chosen->arrivalTime > totalTime)
    {
        chosen = chosen->link;
    }
    while (temp != NULL)
        {
            if ((temp->priority < chosen->priority) && (temp->arrivalTime >= totalTime))
            {
                chosen = temp;
            }
            temp = temp->link;
        }
}
void findPriority()
{
    int i;
    temp = start;
    for (i = 0;i < nOfPr;i++)
    {
        temp->priority = (1 + temp->waitTime) / temp->burstTime;
    }
}
void remove()
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
int main()
{
   printf("Enter no. of processes( > 1) : ");
   scanf("%d",&nOfPr);
   int i;
   for (i = 0;i < nOfPr;i++)
   {
       enqueue();
   }

}
