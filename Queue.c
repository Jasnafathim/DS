#include<stdio.h>
#include<stdlib.h>
int Q[100],size,element,front=-1,rear=-1,i,choice=1;
void enqueue();
void dequeue();
void display();
void search();
int main()
{
printf("\nQUEUE");
printf("\n\nEnter the size of the queue max 100 :");
scanf("%d",&size);
printf("\n1.Insert \n2.Delete \n3.Display \n4.Search");
while(choice<5&&choice!=0)
{
printf("\nEnter your choice :");
scanf("%d",&choice);
switch(choice)
{
case 1:
enqueue();
break;
case 2:
dequeue();
break;
case 3:
display();
break;
case 4:
search();
break;
default:
printf("\nEnter valid choice");
}
}
}
void enqueue()
{
if(rear==size-1)
{
printf("\nQueue is full!!");
}
else if(front==-1&&rear==-1)
{
front=0;
rear=0;
printf("\nEnter the element to insert :");
scanf("%d",&element);
Q[rear]=element;
printf("\nInserted %d",element);
}
else
{
rear++;
printf("\nEnter the element to insert :");
scanf("%d",&element);
Q[rear]=element;
printf("\nInserted %d",element);
}
}
void dequeue()
{
if(front==-1&&rear==-1)
{
printf("\nQueue is empty!!");
}
else if(front==rear)
{
element=Q[front];
printf("\nDeleted %d",element);
front=-1;
rear=-1;
}
else
{
element=Q[front];
printf("\nDeleted %d",Q[front]);
front++;
}
}
void display()
{
if(front==-1&&rear==-1)
{
printf("\nQueue is empty!!");
}
else
{
printf("\nFront :%d\n",front);
for(i=front;i<=rear;i++)
{
printf("%d\t",Q[i]);
}
printf("\nRear :%d",rear);
}
}
void search()
{
if(front!=-1&&rear!=-1)
{
printf("\nEnter the elment to search :");
scanf("%d",&element);
for(i=front;i<=rear;i++)
{
if(element==Q[i])
printf("\nElement %d found in location %d",element,i);
}
}
else
{
printf("\nQueue is empty!!");
}
}