#include <stdio.h>
int main() {
	int a[10],b[10],f,s, i,j,temp,total,size=0;
	printf("Enter size in first array : ");
	scanf("%d",&f);
	printf("\nEnter elemenst\n");
	for(i=0;i<f;i++){
	scanf("%d",&a[i]);
	}
	printf("\nEnter size in second array : ");
	scanf("%d",&s);
	printf("\nEnter elemenst\n",s);
	for(i=0;i<s;i++){
	scanf("%d",&b[i]);
	}
	total=f+s;
	for(i=f;i<total;i++){
		a[i]=b[size];
		size=size+1;
	}
	for(i=total;i>0;i--){
	for(j=0;j<total-1;j++){
			if(a[j]>a[j+1]){	
			temp=a[j];
			a[j]=a[j+1];
			a[j+1]=temp;
			}
		}
	}
	
	printf("\n...............\n");
	

	printf("Array elements are : \n");
	for(i=0;i<total;i++){
		printf("%d\n",a[i]);
	}
	return 0;
}