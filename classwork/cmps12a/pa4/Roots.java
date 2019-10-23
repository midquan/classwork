import java.util.Scanner;
class Roots{
	public static void main(String args[]){
		double resolution = 0.01, tolerance = 0.0000001, threshold = 0.001;	
		double lowEnd, highEnd, lE, hE;
		int x;
		double[] coeff, differ, hold;
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the degree: ");
		int deg = sc.nextInt();
		coeff = new double[deg+1];
		differ = new double[deg];
		hold = new double[deg];
		
		System.out.print("Enter " + (deg+1) + " coefficients: ");
		for(x=0; x<=deg; x++){
			coeff[x] = sc.nextDouble();
		}
		System.out.println("Enter the left and right endpoints: ");
		lE = lowEnd = sc.nextDouble();
		highEnd = sc.nextDouble();
		hE = lE+resolution;
		int count = 0;
		for(x=0; hE<=highEnd; x++){
			if(poly(coeff, lE)*poly(coeff, hE)<=0){
				hold[count] = findRoot(coeff, lE, hE, tolerance);
				count++;
			}
			lE += resolution;
			hE += resolution;
		}
		lE = lowEnd;
		hE = lE + resolution;
		differ = diff(coeff);
		for(x=0; hE<=highEnd; x++){
			if(poly(differ, lE)*poly(differ, hE)<=0){
				double r = findRoot(differ, lE, hE, tolerance);
				if(Math.abs(poly(coeff, r))<threshold){
					hold[count] = r;
					count++;
				}
			}
			lE += resolution;
			hE += resolution;
		}
		bubbleSort(hold, count);
		
		
	}
	static double poly(double[] C, double x){
		double sum = 0;
		for(int j=0; j<C.length; j++){
			sum += C[j]*Math.pow(x,j);
		}
		return sum;
	}
	static double[] diff(double[] C){
		double[] newCoeff;
		newCoeff = new double[C.length-1];
		for(int j=0; j<C.length-1; j++){
			newCoeff[j] = C[j+1]*(j+1);
		}
		return newCoeff;
	}
	static double findRoot(double[] C, double a, double b, double tolerance){
		double width = Math.abs(b-a);
		double mid = 0.0;
		while(width > tolerance){
			mid = (a+b)/2;
			if( (poly(C, a) * poly(C, mid))<=0 ){  
            b = mid;            
			} else {               
            a = mid;            
			}
			width = b-a;
		}
		
		return mid;
	
	}
	static void bubbleSort(double[] hold, int c){
		int n = hold.length;
		double[] newHold = new double[c];
		for(int p = 0; p < c; p++){
			newHold[p] = hold[p];
		}
		for(int i = 0; i < c;i++){
			for(int j = 0; j < (c-1);j++){
				if(newHold[j] > newHold[j+1]){
				double temp = newHold[j];
                newHold[j] = newHold[j + 1];
                newHold[j + 1] = temp;
				}
			}
			
		}
		for(int q = 0; q < c; q++){
			System.out.printf("Root found at %.5f%n", newHold[q]);
		}
	}

}
