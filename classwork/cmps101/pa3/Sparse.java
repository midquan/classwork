// Sparse.java
// Michael Quan
// midquan
// Programing Assignment 3
// Parses inputs and outputs for a Sparse Matrix	
	
	
import java.io.*;
import java.util.Scanner;
	
public class Sparse{
	public static void main (String args[]) throws IOException {
	
		//Intitialize variables
		Scanner infile = null;
		PrintWriter out = null;
		String line = null;
		int lineNumber = 0;
		
		//If invalid usage given
		if(args.length < 2) {
		System.out.printf("Usage: Sparse infile outfile%n");
		System.exit(1);
		}
		
		
		infile = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
		Matrix A = new Matrix(1);
		Matrix B = new Matrix(1);
		int n = 0;
		int a = 0;
		int b = 0;
		int i, row, col, tl;
		double val;
		String[] token = null;

		// Initialize Matrices A and B
		while( infile.hasNextLine() ) {
			++lineNumber;
			line = infile.nextLine()+" "; // add extra space so split works right
			token = line.split("\\s+"); // split line around white space
			tl = token.length;

			if ( lineNumber <= 1 ) {
				n = (int)Integer.parseInt(token[0]);
				a = (int)Integer.parseInt(token[1]);
				b = (int)Integer.parseInt(token[2]);
				A = new Matrix(n);
				B = new Matrix(n);
			}
			// Skip empty line then start parsing input for Matrix A
			else if ( lineNumber > 2 ) {
				if ( lineNumber <= a+2 ) {
					row = (int)Integer.parseInt(token[0]);
					col = (int)Integer.parseInt(token[1]);
					val = (double)Double.parseDouble(token[2]);
					A.changeEntry(row,col,val);
			  }
			  // Skip another empty line then start parsing input for Matrix B
				else if ( lineNumber >= a+4 ) {
					row = (int)Integer.parseInt(token[0]);
					col = (int)Integer.parseInt(token[1]);
					val = (double)Double.parseDouble(token[2]);
					B.changeEntry(row,col,val);
			  }
			}
		}
		
		// Double check to make sure A and B have given non-zero values if not 
		// Exit program and print error message
		if ( a != A.getNNZ() || b != B.getNNZ() ) {
			System.err.printf("Error: Incorrect number of non-zero values initialized%n");
			System.exit(1);
		}
		
		//Print out values onto an output file.
		out.println("A has " + A.getNNZ() + " non-zero entries:");
		out.println(A);
			
		out.println("B has " + B.getNNZ() + " non-zero entries:");
		out.println(B);

		out.println("(1.5)*A =");
		out.println(A.scalarMult(1.5));

		out.println("A+B =");
		out.println(A.add(B));
		
		out.println("A+A =");
		out.println(A.add(A));

		out.println("B-A =");
		out.println(B.sub(A));
		
		out.println("A-A =");
		out.println(A.sub(A));
		
		out.println("Transpose(A) =");
		out.println(A.transpose());
		
		out.println("A*B =");
		out.println(A.mult(B));
		
		out.println("B*B =");
		out.println(B.mult(B));
		
		infile.close();
		out.close();
	}
}