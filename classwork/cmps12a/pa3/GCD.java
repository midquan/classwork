// GCD.java
// Michael Quan
// midquan
// Programing Assignment 3
// Find the GCD between two Ints
import java.util.Scanner;
class GCD{
	public static void main(String [] Args){
		int in1, in2, gcd;
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter a positive integer: ");
		in1 = check(); 
		System.out.print("Enter another positive integer: ");
		in2 = check();
		gcd = solver(in1,in2);
		System.out.println("The GCD of " + in1 + " and " + in2 + " is " + gcd);
	} 
	static int check(){
		Scanner sc = new Scanner(System.in);
		int x = -5;
		while(true){
			if(!sc.hasNextInt()){
				System.out.print("Please enter a positive integer: ");
				sc.next();
			}
			else {
			x = sc.nextInt();
				if(x > 0) break;
				else System.out.print("Please enter a positive integer: ");
			}
		}
		return x;
		
	}
	static int solver(int a, int b){
		int temp,r;
		if (b > a){
			temp = a;
			a = b;
			b = temp;
		}
		while(true){
			r = a % b ;
			a = b;
			if(r > 0) b = r;
			else break;
		}
		return b;
	}
} 