// Guess.java
// Michael Quan
// midquan
// Programing Assignment 2
// Generate a random number and then let the user guess and say if its high,low, or right
import java.util.Scanner;
class Guess{
	public static void main(String [] Args){
		Scanner sc = new Scanner(System.in);
		int answer = (int)((Math.random()*10)+1);
		int guess,count;
		String ordinal = "first";
		count = 1;
		System.out.println("I'm thinking of an integer in the range 1 to 10. You have three guesses. \n");
		
		
		while(count < 4){
			if(count == 2){
				ordinal = "second";
			}
			if(count == 3){
				ordinal = "third";
			}			
			
			System.out.print("Enter your " + ordinal + " guess: ");
			guess = sc.nextInt();
			if(answer == guess){
				System.out.println("You win! \n");
				break;
			}
			if(answer > guess){
				System.out.println("Your answer is too low. \n");
				count++;
			}
			if(answer < guess){
				System.out.println("Your answer is too high. \n");
				count++;	
			}
		if(count == 4){
			System.out.println("You lose. The number was " + answer + ". \n");
		}
		}
		
		
	}	
}