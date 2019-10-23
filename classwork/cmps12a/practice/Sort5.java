//----------------------------------------------------------------------------
//  Sort4.java
//  Sorts 4 numbers input by user using an algorithm called Bubble Sort
// 
//  Exercise: write Sort5.java and Sort6.java by following the same pattern
//----------------------------------------------------------------------------

import java.util.Scanner;

class Sort5{

   public static void main( String[] args ){
      
      int a, b, c, d, e, temp;
      Scanner sc = new Scanner(System.in);

      // get a, b, c, d, e from user
      System.out.print("Enter five integers separated by spaces: ");
      a = sc.nextInt();
      b = sc.nextInt();
      c = sc.nextInt();
      d = sc.nextInt();
	  e = sc.nextInt();

      // sort a, b, c, d in increasing order
	  if( a>b ){ temp=a; a=b; b=temp; }  // swap a <--> b 
      if( b>c ){ temp=b; b=c; c=temp; }  // swap b <--> c
      if( c>d ){ temp=c; c=d; d=temp; }  // swap c <--> d
	  if( d>e ){ temp=d; d=e; e=temp; }  // swap d <--> e
	  
      if( a>b ){ temp=a; a=b; b=temp; }  // swap a <--> b 
      if( b>c ){ temp=b; b=c; c=temp; }  // swap b <--> c
      if( c>d ){ temp=c; c=d; d=temp; }  // swap c <--> d

      if( a>b ){ temp=a; a=b; b=temp; }  // swap a <--> b
      if( b>c ){ temp=b; b=c; c=temp; }  // swap b <--> c

      if( a>b ){ temp=a; a=b; b=temp; }  // swap a <--> b

      // print numbers in increasing order
      System.out.println(a + " " + b + " " + c + " " + d + " " + e);

   }
}