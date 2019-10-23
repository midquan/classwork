//-----------------------------------------------------------------------------
//   Complex.java
//   Represents complex numbers as a pair of doubles
//
//   pa6
//   Fill in the function definitions below.  Write a ComplexTest class to
//   test all your methods. See notes from 5-22-15 for definitions of the
//   complex arithmetic operations.
//-----------------------------------------------------------------------------

class Complex{

	//--------------------------------------------------------------------------
	// Private Data Fields 
	//--------------------------------------------------------------------------
	private double re;
	private double im;

	//--------------------------------------------------------------------------
	// Public Constant Fields 
	//--------------------------------------------------------------------------
	public static final Complex ONE = Complex.valueOf(1,0);
	public static final Complex ZERO = Complex.valueOf(0,0);
	public static final Complex I = Complex.valueOf(0,1);

	//--------------------------------------------------------------------------
	// Constructors 
	//--------------------------------------------------------------------------
	Complex(double a, double b){
		this.re = a;
		this.im = b;
	}

	Complex(double a){
		this.re = a;
		this.im = 0;
	}

	Complex(String s){
	// Fill in this constructor.
	// It should accept expressions like "-2+3i", "2-3i", "3", "5i", etc..
	// Throw a NumberFormatException if s cannot be parsed as Complex.
		double [] parsed = new double[2];
		parsed = parseComplex(s);
		this.re = parsed[0];
		this.im = parsed[1];
	}
	private static double[] parseComplex(String str){
		double[] part = new double[2];
		String s = str.trim();
		String NUM = "(\\d+\\.\\d*|\\.?\\d+)";
		String SGN = "[+-]?";
		String OP =  "\\s*[+-]\\s*";
		String I =   "i";
		String OR =  "|";
		String REAL = SGN+NUM;
		String IMAG = SGN+NUM+"?"+I;
		String COMP = REAL+OR+
					IMAG+OR+
					REAL+OP+NUM+"?"+I;
      
		if( !s.matches(COMP) ){
			throw new NumberFormatException(
				"Cannot parse input string \""+s+"\" as Complex");
		}
		s = s.replaceAll("\\s","");     
		if( s.matches(REAL) ){
			part[0] = Double.parseDouble(s);
			part[1] = 0;
		}else if( s.matches(SGN+I) ){
			part[0] = 0;
			part[1] = Double.parseDouble( s.replace( I, "1.0" ) );
		}else if( s.matches(IMAG) ){
			part[0] = 0;
			part[1] = Double.parseDouble( s.replace( I , "" ) );
		}else if( s.matches(REAL+OP+I) ){
			part[0] = Double.parseDouble( s.replaceAll( "("+REAL+")"+OP+".+" , "$1" ) );
			part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+")"+I , "$1"+"1.0" ) );
		}else{   //  s.matches(REAL+OP+NUM+I) 
			part[0] = Double.parseDouble( s.replaceAll( "("+REAL+").+"  , "$1" ) );
			part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+NUM+")"+I , "$1" ) );
		}
		return part;
	}

	//---------------------------------------------------------------------------
	// Public methods 
	//---------------------------------------------------------------------------

	// Complex arithmetic -------------------------------------------------------

	// copy()
	// Return a new Complex equal to this Complex
	Complex copy(){
		Complex c = new Complex(this.re, this.im);
		return c;
	}

	// add()
	// Return a new Complex representing the sum this plus z.
	Complex add(Complex z){
		Complex c = new Complex(this.re + z.re, this.im + z.im);
		return c;
	}

	// negate()
	// Return a new Complex representing the negative of this.
	Complex negate(){
	    Complex c = new Complex(0-this.re, 0-this.im);
		return c;
	  
	}

	// sub()
	// Return a new Complex representing the difference this minus z.
	Complex sub(Complex z){
		Complex c = new Complex(this.re - z.re, this.im - z.im);
		return c;
	}

	// mult()
	// Return a new Complex representing the product this times z.
	Complex mult(Complex z){
		double a,b;
		a = ((this.re * z.re) - (this.im * z.im));
		b = ((this.re * z.im) + (this.im * z.re));
		Complex c = new Complex(a,b);
		return c;
	}

	// recip()
	// Return a new Complex representing the reciprocal of this.
	// Throw an ArithmeticException with appropriate message if 
	// this.equals(Complex.ZERO).
	Complex recip(){
	  // Fill in
		if (this.equals(Complex.ZERO)){
			throw new ArithmeticException(
				"Complex number is equal to zero.");
		} 
		double den = ((this.re * this.re) + (this.im * this.im));
		Complex c = new Complex((this.re/den), (0-this.im)/den);
		return c;
	}

	// div()
	// Return a new Complex representing the quotient of this by z.
	// Throw an ArithmeticException with appropriate message if 
	// z.equals(Complex.ZERO).
	Complex div(Complex z){
	  double a,b;
	  double den = ((z.re * z.re) + (z.im * z.im));
	  a = (((z.re * this.re) + (z.im * this.im))/den);
	  b = (((z.re * this.im) - (z.im * this.re))/den);
	  Complex c = new Complex(a,b);
	  return c;
	}

	// conj()
	// Return a new Complex representing the conjugate of this Complex.
	Complex conj(){
	  Complex c = new Complex(this.re, 0-this.im);
	  return c;
	}

	// Re()
	// Return the real part of this.
	double Re(){
	  return re;
	}

	// Im()
	// Return the imaginary part of this.
	double Im(){
	  return im;
	}

	// abs()
	// Return the modulus of this Complex, i.e. the distance between 
	// points (0, 0) and (re, im).
	double abs(){
	  double rt = this.re * this.re + this.im * this.im;
	  return Math.sqrt(rt);
	}

	// arg()
	// Return the argument of this Complex, i.e. the angle this Complex
	// makes with positive real axis.
	double arg(){
	  return Math.atan2(im, re);
	}

	// Other functions ---------------------------------------------------------

	// toString()
	// Return a String representation of this Complex.
	// The String returned will be readable by the constructor Complex(String s)
	public String toString(){
		String com;
		if (this.equals(Complex.ZERO)) com = "0";
		else if (this.re == 0 && this.im != 0) com = this.im + "i";
		else if (this.re != 0 && this.im == 0) com = this.re + "";
		else if (this.re != 0 && this.im < 0) com = this.re + "" + this.im + "i";
		else com = this.re + "+" + this.im + "i";
		return com;
	}

	// equals()
	// Return true iff this and obj have the same real and imaginary parts.
	public boolean equals(Object obj){
		Complex c;
		c = (Complex)obj;
		if(this.im==c.im&&this.re==c.re){
			return true;
		}
		else return false;
	}

	// valueOf()
	// Return a new Complex with real part a and imaginary part b.
	static Complex valueOf(double a, double b){
	  Complex c = new Complex(a, b);
	  return c;
	}

	// valueOf()
	// Return a new Complex with real part a and imaginary part 0.
	static Complex valueOf(double a){
	  Complex c = new Complex(a);
	  return c;
	}

	// valueOf()
	// Return a new Complex constructed from s.
	static Complex valueOf(String s){
	  Complex c = new Complex(s);
	  return c;
	}

}