#include<stdio.h>
#define size 5
int Q[size];
int front=-1,rear=-1;
int isfull()
{
if((front==rear+1)||(front==0&&rear==size-1))return 1;
return 0;
}
int isempty()
{
if(front==-1)return 1;
return 0;
}
void enqueue(int element)
{
if(isfull())
printf("\nQueue is full\n");
else
{
if(front==-1)
front=0;
rear=(rear+1)%size;
Q[rear]=element;
printf("\n Inserted :%d",element);
}
}
int dequeue()
{
int element;
if(isempty())
{
printf("\nQueue is Empty!!\n");
return(-1);
}
else
{
element=Q[front];
if(front==rear)
{
front=-1;
rear=-1;
}
else
{
front=(front+1)%size;
}
printf("\nDeleted element :%d\n",element);
return(element);
}
}
void display()
{
int i;
if(isempty())
printf("\nEmpty Queue\n");
else
{
printf("\nFront :%d",front);
printf("\nQ :");
for(i=front;i!=rear;i=(i+1)%size)
{
printf("%d\t",Q[i]);
}
printf("%d",Q[i]);
printf("\nRear :%d\n",rear);
}
}
void search()
{
int a,j;
printf("\nEnter the element to search :");
scanf("%d",&a);
if(front==-1)
{
printf("\nQueue is empty!!");
return ;
}
else
{
for(j=0;j<size;j++)
{
if(a==Q[j])
{
printf("\nElement %d found in %d",a,j);
return ;
}
}
if(a!=Q[j])
{
printf("\nElement not found");
return ;
}
}
}
int main()
{
int choice=1,element;
while(choice<5&&choice!=0){
printf("\nPress 1 to insert element");
printf("\nPress 2 to delete element");
printf("\nPress 3 to display");
printf("\nPress 4 to search");
printf("\nEnter your choice :");
scanf("%d",&choice);
switch(choice)
{
case 1:
printf("\nEnter the element to insert :");
scanf("%d",&element);
enqueue(element);
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
printf("Enter valid option");
}
}
return 0;
}