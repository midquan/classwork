#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int GCD(int n1, int n2){
    if(n1 % n2 == 0){
        return n2;
    }
    else{
        int num = n1%n2;
        return GCD(n2, num);
    }
}

int main(void){
  int num1;
  int num2;

  printf("Enter a positive integer: ");
  int n = scanf(" %d", &num1);
  while(1){
    if(n != 1){
      printf("\nPlease enter a positive integer: ");
      n = scanf(" %d", &num1);
    } else if(num1 < 0){
      printf("\nPlease enter a positive integer: ");
      n = scanf(" %d", &num1);
    } else{
      break;
    }
  }

  printf("Enter another positive integer: ");
  n = scanf(" %d", &num2);
  while(1){
    if(n != 1){
      printf("\nPlease enter a positive integer: ");
      n = scanf(" %d", &num2);
    } else if(num1 < 0){
      printf("\nPlease enter a positive integer: ");
      n = scanf(" %d", &num2);
    } else{
      break;
    }
  }

  printf("The GCD of %d and %d is %d", num1, num2, GCD(num1, num2));
  return 0;
}