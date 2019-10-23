/* 
GCD.c
Michael Quan
midquan
Lab 8 
Solve GCD given two given positive ints
*/
#include<stdio.h>
int solver(int a, int b){
	int temp,r;
	
	if (b > a){
		temp = a;
		a = b;
		b = temp;
	}
	while(1){
		r = a % b ;
		a = b;
		if(r > 0) b = r;
		else break;
	}
	return b;
}

int main(){
	int in1,in2;
	char str[100];
	
	printf("Enter a positive integer: ");
	int i = scanf(" %d", &in1);
	while(1){
		if(i != 1){
			scanf("%s", str); 
			printf("Please enter a positive integer: ");
			i = scanf(" %d", &in1);
		}else if(in1 < 0){
			printf("Please enter a positive integer: ");
			i = scanf(" %d", &in1);
		}else{
			break;
		}
	}
	
	printf("Enter another positive integer: ");
	i = scanf(" %d", &in2);
	while(1){
		if(i != 1){
			scanf("%s", str); 
			printf("Please enter a positive integer: ");
			i = scanf(" %d", &in2);
		}else if(in2 < 0){
			printf("Please enter a positive integer: ");
			i = scanf(" %d", &in2);
		}else{
			break;
		}
	}
	printf("The GCD of %d and %d is %d \n",in1,in2,solver(in1,in2));
	return 0;
}
