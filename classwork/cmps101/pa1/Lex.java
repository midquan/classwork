// Lex.java
// Michael Quan
// midquan
// Programing Assignment 1
// Parses inputs and outputs an alphabetized list

import java.io.*;
import java.util.Scanner;

class Lex{
	public static void main(String args[]) throws IOException{
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] in_array = null;
		int lineNumber = -1;
		int lines = 0;
		
		//Check for inputs not exactly 2
		if(args.length != 2){
			System.err.println("Usage: java Lex input_file output_file");
			System.exit(1);
		}
		
		in = new Scanner(new File(args[0]));
		
		//Count lines via .hasNextLine
		while( in.hasNextLine() ){
			lines++;
			in.nextLine();
		}
		
		//Close file to allow for rescan
		in.close();
		in = null;
		
		//Assign the variables for the project
		List linked = new List();
		in = new Scanner(new File(args[0]));
		in_array = new String[lines];
		out = new PrintWriter(new FileWriter(args[1]));
		
		//Insert input into array 
		while(in.hasNextLine() ){
			in_array[++lineNumber] = in.nextLine();
		}
		
		linked.append(0);
		
		//Start the Pseudo-Insertion Sort
		for(int i = 1;i<in_array.length; i++){
			String temp = in_array[i];
			int j = i - 1;
			
			//Start from end of list
			linked.moveBack();
			
			//Work backwards
			while(j >= 0 && temp.compareTo(in_array[linked.get()]) <= 0){
				--j;
				linked.movePrev();
			}
			
			if(linked.index() >= 0) linked.insertAfter(i);
			else linked.prepend(i);
		}
				
		linked.moveFront();
		
		//Write the output file after sorted indexes
		while(linked.index() > -1) {
         out.println(in_array[linked.get()]);
         linked.moveNext();
      }
		
		
		
		in.close();
		out.close();
	}
	
	
}
