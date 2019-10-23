// Queens.java
// Michael Quan + Daniel Lung
// midquan + dlung
// Programing Assignment 5
// Solves the n-Queens problem given a string.

import java.util.Arrays;

class Queens{
	public static boolean verbose;
	public static int[] numQueen;
	public static void main(String args[]){
		int size = 0;
		while(args.length != 0){
			if(args[0].equals("-v")){
				verbose = true;
				try{
					Integer.parseInt(args[1]);
					size = Integer.parseInt(args[1]);
					
				}catch(Exception e1){
					Usage();
				}
				
			}else {
				try{
					Integer.parseInt(args[0]);
					size = Integer.parseInt(args[0]);
					
					System.out.println(size);
				}catch(Exception e2){
					Usage();
				}
			}
			break;
		}
		if(args.length == 0){
			Usage();
		}
		int[]J = new int[size+1];
		for(int c = 1; c < size+1; c++){
			J[c] = c;			
		}
		int numCorrect=0;
		numQueen = J;
		if(isSolution(numQueen)){
				numCorrect++;
		}
		for(int i=0; i < factorial(size)-1;i++){
			nextPermutation(numQueen);
			if(isSolution(numQueen)){
				numCorrect++;
			}
		}
		System.out.println(size + "-Queens has " + numCorrect + " solutions");
		
	}
	static int factorial(int n){
		int count=1;
		for(int x = 1; x<=n; x++){
			count*=x;
		}
		return count;
	}
	static void Usage(){
		System.err.println("Usage: Queens [-v] number");
		System.err.println("Option: -v verbose output, print all solutions");
		System.exit(0);
	}
	static void nextPermutation(int[]A){
		int n = 0, piv = 0, count = 0;
		for(n = numQueen.length-1; n > 1; n--){
			if(numQueen[n-1] < numQueen[n]){
				piv = numQueen[n-1];
				count = n-1;
				break;
			}
		}
		for(n = numQueen.length-1; n>1; n--){
			if(numQueen[n] > piv){
				int temp = numQueen[count];
				numQueen[count] = numQueen[n];
				numQueen[n] = temp;
				numQueen = arrRev(numQueen, count);
				break;
			}
		}
		if(verbose){
			Arrays.toString(numQueen);
		}
	}
	static int[] arrRev(int[]C, int n){
		
		int x, y = C.length - 1;
		int[] newArr = new int [C.length - n - 1];
		for(x = 0; x < newArr.length; x++){
			newArr [x] = C[y];
			y--;
		}
		n++;
		for(x = 0; x < newArr.length; x++){
			C[n] = newArr[x];
			n++;
		}
		return C;
	}
	static boolean isSolution(int[] c){
		int [] printArr = new int [c.length - 1];
		int n, x;
		for(n=1; n<c.length; n++){
			for(x=n+1; x<c.length; x++){
				if(Math.abs(c[x]-c[n])==Math.abs(x-n)){
					return false;
				}
			}
		}
		if(verbose){
			for(int i = 0; i < printArr.length;i++){
				printArr[i] = c[i + 1];
			}
			for(int k = 0; k < printArr.length;k++){
				if(k == 0){
					System.out.print("(" + printArr[k]);
				}
				else if(k == printArr.length - 1){
					System.out.print(", " + printArr[k] + ")");
				} 
				else System.out.print(", " + printArr[k]);
			}
			System.out.println("");
		}
		return true;
	}
	




}