#include<stdio.h>
int S[100],element,size,top=-1,choice,i;
void push();
void pop();
void display();
int main()
{
int choice=1;
printf("\nSTACK WITH ARRAY");
printf("\nEnter the size of the stack(max 100) :");
scanf("%d",&size);
while(choice<4&&choice!=0)
{
printf("\n\nPress 1 to PUSH element");
printf("\n\nPress 2 to POP element");
printf("\n\nPress 3 to DISPLAY elements");
printf("\n\nEnter your choice :");
scanf("%d",&choice);
switch(choice)
{
case 1:
push();
break;
case 2:
pop();
break;
case 3:
display();
break;
}
}
}
void push()
{
if(top==size-1)
{
printf("\nStack is full!!");
}
else
{
printf("\nEnter the element to push :");
scanf("%d",&element);
top++;
S[top]=element;
printf("\nInserted :%d",element);
}
}
void pop()
{
if(top==-1){
printf("\nStack is empty!!");
}
else
{
printf("Deleted :%d",S[top]);
top--;
}

}
void display()
{
if(top>=0)
{
printf("\nStack elements are given below");
for(i=top;i>=0;i--)
{
printf("\n%d",S[i]);
}
}
else
{
printf("\nStack is empty!!");
}
}