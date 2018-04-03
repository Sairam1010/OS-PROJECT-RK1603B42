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
}*start = NULL, *temp = NULL, *rear = NULL;
int idT = 1;
void enqueue()
{
    temp = (struct process*) malloc(sizeof(struct process));
    scanf("%d", &(temp->arrivalTime));
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
        while(temp != NULL)\
        {
            printf("%d", temp->id);
            temp = temp->link;
        }
    }
}
/*void dequeue
{

}*/
int main()
{
    int i;
    for (i = 0;i < 3;i++)
    {
        show();
        enqueue();
    }
}
