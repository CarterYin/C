#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
void reverse(int a[], int length, int index){
	int i=index;
	int j=length;
	int temp;
	while(i<=j){
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
		i++;
		j--;
	}
}
 
bool next_permutation(int a[], int length){
	int i;
	for(i=length; i>=1; i--){			//从最后一个数开始找到第一个不是升序的数 
		if(i-1 == 0) return false;
		if(a[i]>a[i-1]) break;
	}
	
	int start=i-1;						//记录上面找到的数：start 
	while(a[start]<a[i]){				//从start之后找到第一个刚好大于它的数 
		i++;
	}
	
	int temp=a[i-1];					//记录找到的数：temp将它与之前找到的数：start交换 
	a[i-1]=a[start];
	a[start]=temp;
	reverse(a, length, start+1);				//将start后面的数倒置 
	return true;
}
 
int main(){
	int n;
	scanf("%d", &n);
	int a[15]={0};
	int i;
	for(i=1; i<=n; i++){
		a[i]=i;
	}
	
	do{
		for(i=1; i<=n; i++){
			printf("%d ", a[i]);
		}	
		putchar('\n');
	}
	while(next_permutation(a, n));
	
	return 0;
}
 