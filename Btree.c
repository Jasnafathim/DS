#include<stdio.h>
#include "stdlib.h"
#define M 5
typedef struct _node {
int n;
int keys[M - 1];
struct _node *p[M];
} node;
node *root = NULL;
typedef enum KeyStatus {
Duplicate,
SearchFailure,
Success,
InsertIt,
LessKeys,
} KeyStatus;
void insert(int key);
void display(node *root, int);
void DelNode(int x);
void search(int x);
KeyStatus ins(node *r, int x, int* y, node** u);
int searchPos(int x, int *key_arr, int n);
KeyStatus del(node *r, int x);
void eatline(void);
void inorder(node *ptr);
int totalKeys(node *ptr);
void printTotal(node *ptr);
int getMin(node *ptr);
int getMax(node *ptr);
void getMinMax(node *ptr);
int max(int first, int second, int third);
int maxLevel(node *ptr);
void printMaxLevel(node *ptr);
int main() {
int key;
int choice;
printf("Creation of B tree for M=%d\n", M);
printf("1.Insert\n");
printf("2.Delete\n");
printf("3.Search\n");
printf("4.Display\n");
printf("5.Quit\n");
printf("6.Enumerate\n");
printf("7.Total Keys\n");
printf("8.Min and Max Keys\n");
printf("9.Max Level\n");
while (1) {
printf("Enter your choice : ");
scanf("%d", &choice); eatline();
switch (choice) {
case 1:
printf("Enter the key : ");
scanf("%d", &key); eatline();
insert(key);
break;
case 2:
printf("Enter the key : ");
scanf("%d", &key); eatline();
DelNode(key);
break;
case 3:
printf("Enter the key : ");
scanf("%d", &key); eatline();
search(key);
break;
case 4:
printf("Btree is :\n");
display(root, 0);
break;
case 5:
exit(1);
case 6:
printf("Btree in sorted order is:\n");
inorder(root); putchar('\n');
break;
case 7:
printf("The total number of keys in this tree is:\n");
printTotal(root);
break;
case 8:
getMinMax(root);
break;
case 9:
printf("The maximum level in this tree is:\n");
printMaxLevel(root);
break;
default:
printf("Wrong choice\n");
break;
}/*End of switch*/
}/*End of while*/
return 0;
}/*End of main()*/
void insert(int key) {
node *newnode;
int upKey;
KeyStatus value;
value = ins(root, key, &upKey, &newnode);
if (value == Duplicate)
printf("Key already available\n");
if (value == InsertIt) {
node *uproot = root;
root = (node*)malloc(sizeof(node));
root->n = 1;
root->keys[0] = upKey;
root->p[0] = uproot;
root->p[1] = newnode;
}/*End of if */
}/*End of insert()*/
KeyStatus ins(node *ptr, int key, int *upKey, node **newnode) {
node *newPtr, *lastPtr;
int pos, i, n, splitPos;
int newKey, lastKey;
KeyStatus value;
if (ptr == NULL) {
*newnode = NULL;
*upKey = key;
return InsertIt;
}
n = ptr->n;
pos = searchPos(key, ptr->keys, n);
if (pos < n && key == ptr->keys[pos])
return Duplicate;
value = ins(ptr->p[pos], key, &newKey, &newPtr);
if (value != InsertIt)
return value;
if (n < M - 1) {
pos = searchPos(newKey, ptr->keys, n);
for (i = n; i>pos; i--) {
ptr->keys[i] = ptr->keys[i - 1];
ptr->p[i + 1] = ptr->p[i];
}
/*Key is inserted at exact location*/
ptr->keys[pos] = newKey;
ptr->p[pos + 1] = newPtr;
++ptr->n;
return Success;
}/*End of if */
if (pos == M - 1) {
lastKey = newKey;
lastPtr = newPtr;
}
else {
lastKey = ptr->keys[M - 2];
lastPtr = ptr->p[M - 1];
for (i = M - 2; i>pos; i--) {
ptr->keys[i] = ptr->keys[i - 1];
ptr->p[i + 1] = ptr->p[i];
}
ptr->keys[pos] = newKey;
ptr->p[pos + 1] = newPtr;
}
splitPos = (M - 1) / 2;
(*upKey) = ptr->keys[splitPos];
(*newnode) = (node*)malloc(sizeof(node));/*Right node after split*/
ptr->n = splitPos; /*No. of keys for left splitted node*/
(*newnode)->n = M - 1 - splitPos;/*No. of keys for right splitted node*/
for (i = 0; i < (*newnode)->n; i++) {
(*newnode)->p[i] = ptr->p[i + splitPos + 1];
if (i < (*newnode)->n - 1)
(*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
else
(*newnode)->keys[i] = lastKey;
}
(*newnode)->p[(*newnode)->n] = lastPtr;
return InsertIt;
}/*End of ins()*/
void display(node *ptr, int blanks) {
if (ptr) {
int i;
for (i = 1; i <= blanks; i++)
printf(" ");
for (i = 0; i < ptr->n; i++)
printf("%d ", ptr->keys[i]);
printf("\n");
for (i = 0; i <= ptr->n; i++)
display(ptr->p[i], blanks + 10);
}/*End of if*/
}/*End of display()*/
void search(int key) {
int pos, i, n;
node *ptr = root;
printf("Search path:\n");
while (ptr) {
n = ptr->n;
for (i = 0; i < ptr->n; i++)
printf(" %d", ptr->keys[i]);
printf("\n");
pos = searchPos(key, ptr->keys, n);
if (pos < n && key == ptr->keys[pos]) {
printf("Key %d found in position %d of last dispalyed node\n", key, i);
return;
}
ptr = ptr->p[pos];
}
printf("Key %d is not available\n", key);
}/*End of search()*/
int searchPos(int key, int *key_arr, int n) {
int pos = 0;
while (pos < n && key > key_arr[pos])
pos++;
return pos;
}/*End of searchPos()*/
void DelNode(int key) {
node *uproot;
KeyStatus value;
value = del(root, key);
switch (value) {
case SearchFailure:
printf("Key %d is not available\n", key);
break;
case LessKeys:
uproot = root;
root = root->p[0];
free(uproot);
break;
default:
return;
}/*End of switch*/
}/*End of delnode()*/
KeyStatus del(node *ptr, int key) {
int pos, i, pivot, n, min;
int *key_arr;
KeyStatus value;
node **p, *lptr, *rptr;
if (ptr == NULL)
return SearchFailure;
/*Assigns values of node*/
n = ptr->n;
key_arr = ptr->keys;
p = ptr->p;
min = (M - 1) / 2;
pos = searchPos(key, key_arr, n);
// p is a leaf
if (p[0] == NULL) {
if (pos == n || key < key_arr[pos])
return SearchFailure;
/*Shift keys and pointers left*/
for (i = pos + 1; i < n; i++)
{
key_arr[i - 1] = key_arr[i];
p[i] = p[i + 1];
}
return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
}/*End of if */
//if found key but p is not a leaf
if (pos < n && key == key_arr[pos]) {
node *qp = p[pos], *qp1;
int nkey;
while (1) {
nkey = qp->n;
qp1 = qp->p[nkey];
if (qp1 == NULL)
break;
qp = qp1;
}/*End of while*/
key_arr[pos] = qp->keys[nkey - 1];
qp->keys[nkey - 1] = key;
}/*End of if */
value = del(p[pos], key);
if (value != LessKeys)
return value;
if (pos > 0 && p[pos - 1]->n > min) {
pivot = pos - 1;
lptr = p[pivot];
rptr = p[pos];
rptr->p[rptr->n + 1] = rptr->p[rptr->n];
for (i = rptr->n; i>0; i--) {
rptr->keys[i] = rptr->keys[i - 1];
rptr->p[i] = rptr->p[i - 1];
}
rptr->n++;
rptr->keys[0] = key_arr[pivot];
rptr->p[0] = lptr->p[lptr->n];
key_arr[pivot] = lptr->keys[--lptr->n];
return Success;
}/*End of if */
//if (posn > min)
if (pos < n && p[pos + 1]->n > min) {
pivot = pos;
lptr = p[pivot];
rptr = p[pivot + 1];
lptr->keys[lptr->n] = key_arr[pivot];
lptr->p[lptr->n + 1] = rptr->p[0];
key_arr[pivot] = rptr->keys[0];
lptr->n++;
rptr->n--;
for (i = 0; i < rptr->n; i++) {
rptr->keys[i] = rptr->keys[i + 1];
rptr->p[i] = rptr->p[i + 1];
}/*End of for*/
rptr->p[rptr->n] = rptr->p[rptr->n + 1];
return Success;
}/*End of if */
if (pos == n)
pivot = pos - 1;
else
pivot = pos;
lptr = p[pivot];
rptr = p[pivot + 1];
/*merge right node with left node*/
lptr->keys[lptr->n] = key_arr[pivot];
lptr->p[lptr->n + 1] = rptr->p[0];
for (i = 0; i < rptr->n; i++) {
lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
lptr->p[lptr->n + 2 + i] = rptr->p[i + 1];
}
lptr->n = lptr->n + rptr->n + 1;
free(rptr); /*Remove right node*/
for (i = pos + 1; i < n; i++) {
key_arr[i - 1] = key_arr[i];
p[i] = p[i + 1];
}
return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
}
void eatline(void) {
char c;
while ((c = getchar()) != '\n');
}
void inorder(node *ptr) {
if (ptr) {
if (ptr->n >= 1) {
inorder(ptr->p[0]);
printf("%d ", ptr->keys[0]);
inorder(ptr->p[1]);
if (ptr->n == 2) {
printf("%d ", ptr->keys[1]);
inorder(ptr->p[2]);
}
}
}
}
int totalKeys(node *ptr) {
if (ptr) {
int count = 1;
if (ptr->n >= 1) {
count += totalKeys(ptr->p[0]);
count += totalKeys(ptr->p[1]);
if (ptr->n == 2) count += totalKeys(ptr->p[2]) + 1;
}
return count;
}
return 0;
}
void printTotal(node *ptr) {
printf("%d\n", totalKeys(ptr));
}
int getMin(node *ptr) {
if (ptr) {
int min;
if (ptr->p[0] != NULL) min = getMin(ptr->p[0]);
else min = ptr->keys[0];
return min;
}
return 0;
}
int getMax(node *ptr) {
if (ptr) {
int max;
if (ptr->n == 1) {
if (ptr->p[1] != NULL) max = getMax(ptr->p[1]);
else max = ptr->keys[0];
}
if (ptr->n == 2) {
if (ptr->p[2] != NULL) max = getMax(ptr->p[2]);
else max = ptr->keys[1];
}
return max;
}
return 0;
}
void getMinMax(node *ptr) {
printf("%d %d\n", getMin(ptr), getMax(ptr));
}
int max(int first, int second, int third) {
int max = first;
if (second > max) max = second;
if (third > max) max = third;
return max;
}
int maxLevel(node *ptr) {
if (ptr) {
int l = 0, mr = 0, r = 0, max_depth;
if (ptr->p[0] != NULL) l = maxLevel(ptr->p[0]);
if (ptr->p[1] != NULL) mr = maxLevel(ptr->p[1]);
if (ptr->n == 2) {
if (ptr->p[2] != NULL) r = maxLevel(ptr->p[2]);
}
max_depth = max(l, mr, r) + 1;
return max_depth;
}
return 0;
}
void printMaxLevel(node *ptr) {
int max = maxLevel(ptr) - 1;
if (max == -1) printf("tree is empty\n");
else printf("%d\n", max);
}