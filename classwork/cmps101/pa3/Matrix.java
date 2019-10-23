// Matrix.java
// Michael Quan
// midquan
// Programing Assignment 3
// Parses inputs and outputs an alphabetized list

// Constructor

// Makes a new n x n zero Matrix. pre: n>=1
public class Matrix{
	private class Entry{
		
		//fields for Entry
		int column;
		double value;
		
		Entry(int column, double value){
			this.column = column;
			this.value = value;
		}
		
		public String toString(){
			return "(" + column + ", " + value + ")"; 	
		}
		
		//Overides object's default equals
		public boolean equals(Object x){ 
			boolean eq = false;
         Entry that;
         if(x instanceof Entry){
            that = (Entry) x;
            eq = (this.column == that.column && this.value == that.value);
         }
         return eq;
			
		}	
	}
	private List [] row;
	private int size;
	
	Matrix(int n){
		if(n < 1) throw new RuntimeException("Cannot create a matrix with negative column value.");  
		row = new List [n + 1];
		n = size;
		for(int i = 1;i < (n+1); i++)	row[i] = new List();
	}
	
	


	// Access functions
	// Returns n, the number of rows and columns of this Matrix
	int getSize(){
		return row.length - 1;
	}

	// Returns the number of non-zero entries in this Matrix
	int getNNZ(){
		int count = 0;
		for(int i = 1; i < this.size; i++) count += row[i].length();
		return count;
	}

	// overrides Object's equals() method
	public boolean equals(Object x){
      Matrix Q;

      if(x instanceof Matrix){
         Q = (Matrix)x;
			if(Q.size != this.size) return false;
         for(int i = 1; i <= this.size; i++) {
				if(row[i].equals(Q.row[i])) return false;	
			}
      }
      return true;
	}

	// Manipulation procedures
	// sets this Matrix to the zero state
	void makeZero(){
		for(int i = 1; i <= this.size; i++) this.row[i] = new List();
	}
	 
	// returns a new Matrix having the same entries as this Matrix
	Matrix copy(){
		Matrix M = new Matrix(this.size);
		for(int i = 1;i < this.size; i++){
			row[i].moveFront();
			while(row[i].index() >= 0){
				Entry temp = (Entry) row[i].get();
            M.changeEntry(i, temp.column, temp.value);
				row[i].moveNext();
			}
		}
		return M;
	}

	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x){
		if(i < 1 || i > getSize() || j < 1 || j > getSize()){
			throw new RuntimeException("Cannot call changeentry() on an undefined ith, jth position");
		}
		//Tests for if the value is zero. 
		if(x == 0){
			if(this.row[i].length() > 0){
				row[i].moveFront();
				while((!(row[i].cur_null())) && ((Entry) row[i].get()).column < j){
					row[i].moveNext();
				}
				if ((!(row[i].cur_null())) && (((Entry) row[i].get()).column == j)) {
					row[i].delete();
				}
			}
		}
		
		//Loop into this if value is non-zero
		else{
			Entry temp = new Entry(j, x);
			boolean tempi = (temp == null);
			System.out.println(tempi);
			if (row[i].length() < 1) row[i].append(temp);
			else{
				row[i].moveFront();
				while((!(row[i].cur_null())) && ((Entry) row[i].get()).column < j){
					row[i].moveNext();
				}
				if(row[i].cur_null()) row[i].append(temp);
				else if (j == ((Entry) row[i].get()).column) {
					row[i].insertBefore(temp);
					row[i].delete();
				}
				else row[i].insertBefore(temp);
			 }
		}
	}	
	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x){
		Matrix temp = this.copy();
		for(int i = 1; i <= this.size; i++){
			temp.row[i].moveFront();
			while(temp.row[i].index() > -1) {
				Entry e = (Entry) temp.row[i].get();
				temp.changeEntry(i, e.column, x * e.value);
				temp.row[i].moveNext();
			}
      }
      return temp;
	}


	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.size
	Matrix add(Matrix M){
		if(this.size != M.size) throw new RuntimeException("Cannot add two matrices of different sizes");  
		//Special case if equivalent matrices thus 2M = M + this
		if(M == this) return M.copy().scalarMult(2);
		
      Matrix temp = new Matrix(this.size);
      for(int i = 1; i <= this.size; i++) {
          temp.row[i] = arithmetic(row[i], M.row[i], 1);
      }
      return temp;
	}

	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.size
	Matrix sub(Matrix M){
		if(this.size != M.size) throw new RuntimeException("Cannot subtract two matrices of different sizes");  
		//Special case if equivalent matrices thus 0M = M - this
		if(M == this) return new Matrix(this.size);
      Matrix temp = new Matrix(this.size);
      for(int i = 1; i <= this.size; i++) {
         temp.row[i] = arithmetic(row[i], M.row[i], -1);
      }
      return temp;
	}
	
	private List arithmetic(List P, List Q, int sign){
		
		//Intialize List and put P and Q at the front of their lists
		List L = new List();
		P.moveFront();
		Q.moveFront();
		boolean add = (sign == 1);
		while(!(P.cur_null()) || !(Q.cur_null())){
			//If both not null
			if(!(P.cur_null()) && !(Q.cur_null())){
				Entry p_get = (Entry) P.get();
				Entry q_get = (Entry) Q.get();
				//Sign works via sign * value to do subrtration.
				if(p_get.column > q_get.column){
					L.append(new Entry(q_get.column, sign * q_get.value));
					Q.moveNext();
				}
				else if(p_get.column < q_get.column){
					L.append(new Entry(p_get.column, sign * p_get.value));
					P.moveNext();		
				}
				else if(p_get.column == q_get.column){
					if((add && (p_get.value + q_get.value != 0)) || (!add && (p_get.value - q_get.value != 0))){
						L.append(new Entry(p_get.column, p_get.value + (sign * q_get.value) ));
					}
					P.moveNext();
					Q.moveNext();
				} 
			}
			//If one is null
			else if(!(P.cur_null())) {
            Entry a = (Entry) P.get();
            L.append(new Entry(a.column, a.value));
            P.moveNext();
         } 
			else{
            Entry b = (Entry) Q.get();
            L.append(new Entry(b.column, (sign * b.value)));
            Q.moveNext();
			}
		}
		return L;
	}

	// returns a new Matrix that is the transpose of this Matrix
	Matrix transpose(){
		Matrix M = new Matrix(this.size);
		for(int i = 1; i <= this.size; i++){
			row[i].moveFront();
			while(row[i].index() >= 0) {
				//Flips Matrix Entries to its transpose
				M.changeEntry(((Entry)row[i].get()).column, i, ((Entry)row[i].get()).value);
				row[i].moveNext();
			}
		}
		return M;
	}


	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.size
	Matrix mult(Matrix M){
		if(this.size != M.size) throw new RuntimeException("Cannot multiply two matrices of different sizes");  
		Matrix temp = new Matrix(this.size);
		
		//Uses transpose as a helper function
		Matrix trans = M.transpose();
		for(int i = 1;i <= this.size; i++){
			if(row[i].length() == 0) continue;
			for(int j = 1; j <= this.size; j++){
				if(trans.row[j].length() == 0) continue;
				temp.changeEntry(i,j,dot(row[i],temp.row[j]));
			}	
		}
		return temp;
	}
	
	//Helper method for multiplication creating the dot product.
	private static double dot(List P, List Q){
		int p_column;
		int q_column;
		double p_value;
		double q_value;
		double sum = 0;
		P.moveFront();
		Q.moveFront();
		
		//Matches up when the column numbers are equal and then sums it up and return that sum.
		while(!(P.cur_null())&& !(Q.cur_null())){
			p_column = ((Entry) (P.get())).column;
			q_column = ((Entry) (Q.get())).column;
			p_value = ((Entry) (P.get())).value;
			q_value = ((Entry) (Q.get())).value;
			
			if(p_column < q_column) P.moveNext();
			else if(q_column < p_column) Q.moveNext();
			else{
				sum += p_value * q_value;
				P.moveNext();
				Q.moveNext();
			}
		} 
		return sum;
	}
	// Other functions
	// overrides Object's toString() method
	public String toString(){
		String str = "";
		for (int i=1; i <= size; i++) {
		if ( row[i-1].length() != 0 ) {
			str += String.valueOf(i) + ": ";
			str += row[i-1].toString() + "\n";
      }
    }
    return str;
	}

}
