// List.java
// Michael Quan
// midquan
// Programing Assignment 1
// Linked-list constructor and functions

public class List{
	private class Node{
		
		int data;
		Node prev;
		Node next;
		
		Node(int data){
			this.data = data;
			prev = null;
			next = null;
		}
		Node(int data, Node prev, Node next){
			this.data = data;
			this.prev = prev;
			this.next = next;
		}
	} 
	
	private Node front;
	private Node back;
	private Node cursor;
	private int numData;
	private int index;
	
	public List(){
		front = null;
		back = null;
		cursor = null;
		numData = 0;
		index = -1;
	}
		
	// Returns the number of elements in this List.
	int length(){
		return numData;
	}
	
	// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
	int index(){
		if (cursor == null){
			return -1;
		}
		return index;
	}
	
	// Returns front element. Pre: length()>0	
	int front() {
		if (numData < 1){
			throw new RuntimeException("Cannot call front() from an empty list");  
		}
		return front.data;
	}
	
	// Returns back element. Pre: length()>0
	int back(){
		if (numData < 1){
			throw new RuntimeException("Cannot call back() from an empty list");  
		}
		return back.data;	
		
	} 
	
	// Returns cursor element. Pre: length()>0, index()>=0
	int get() {
		if (numData < 1 || index == -1){
			throw new RuntimeException("Cannot call get() from an empty list");  
		}
		return cursor.data;	
	}
	
	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	boolean equals(List L) {
		boolean eq = true;
		Node test1 = L.front;
		Node test2 = front;
		while (L != null && eq != false){
			if(L.numData == this.numData){
				eq = (test1.data == test2.data);
				test1 = test1.next;
				test2 = test2.next;
			}
			return eq;	
		}
		return eq;
	}

	// Manipulation procedures
	// Resets this List to its original empty state.
	void clear(){
		front = back = cursor = null;
		numData = 0;
		index = -1;	
	}
	
	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveFront() {
		if(numData > 0){
			cursor = front;
			index = 0;
		}
	}

	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack() {
		if(numData > 0){
			cursor = back;
			index = numData - 1;
		}
	}
	 
	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev() {
		if(cursor != null ){
			if(index() == 0){
				cursor = null; 
				index = -1;
			}
			if(index > 0){
				cursor = cursor.prev;
				index--;
			}
		}
	}
	
	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void moveNext() {
		if(cursor != null){
			if(index == (numData-1)){
				cursor = null; 
				index = -1;
			}
			if(index < numData-1 && index >= 0){
				cursor = cursor.next;
				index++;
			}
		}
	}
	
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void prepend(int data) {
		Node temp = new Node(data);
		if(numData < 1){
			front = back = temp;
		}
		else{
			temp.prev = null;
			front.prev = temp;
			temp.next = front;
			front = temp;
		}
		numData++;
		if(cursor != null){
			index++;
		}
	}
	
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	void append(int data){
		Node temp = new Node(data);
		if(numData < 1){
			front = back = temp;
		}
		else{
			temp.next = null;
			back.next = temp;
			temp.prev = back;
			back = temp;
		}
		numData++;
		if(cursor != null){
			index++;
		}
		
	} 
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	void insertBefore(int data){
		if (numData < 1 || index <= -1){
			throw new RuntimeException("Cannot call insertBefore() from an empty list");  
		}
		Node temp = new Node(data,cursor.prev,cursor);
		if(cursor.next != null){
			cursor.prev.next = temp;
		}
		else{
			front = temp;
		}
		cursor.prev = temp;
		numData++;
	}
	
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(int data){
		if (numData < 1 || index <= -1){
			throw new RuntimeException("Cannot call insertAfter() from an empty list");  
		}
		Node temp = new Node(data,cursor,cursor.next);
		if(cursor.next != null){
			cursor.next.prev = temp;
		}
		else{
			back = temp;
		}
		cursor.next = temp;
		numData++;
	}
	
	// Deletes the front element. Pre: length()>0
	void deleteFront(){
		if (numData < 1){
			throw new RuntimeException("Cannot call deleteFront() from an empty list");  
		}
		if (cursor.equals(front)){
			cursor = null;
			index = -1;
		}
		front = front.next;
		front.prev = null;
		numData--;
		
	} 
	// Deletes the back element. Pre: length()>0
	void deleteBack() {
		if (numData < 1){
			throw new RuntimeException("Cannot call deleteBack() from an empty list");  
		}
		if (cursor.equals(back)){
			cursor = null;
			index = -1;
		}
		back = back.prev;
		back.next = null;
		numData--;
	}
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	void delete() {
		if (numData < 1 || index <= -1){
			throw new RuntimeException("Cannot call delete() from an empty list");  
		}
		if(cursor.equals( back)) deleteBack();
      else if(cursor.equals(front)) deleteFront();
		
      else {
         cursor.prev.next = cursor.next;
         cursor.next.prev = cursor.prev;
         cursor = null;
         index = -1;
         numData--;
		}
	}
	
	// Other methods
	
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString(){
		String print = "";
		for(Node temp = front;temp != null; temp = temp.next){
			print += String.valueOf(temp.data) + " ";
		}
		return print;
	}
	
	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
	List copy(){
		List cop = new List();
		for(Node fir = front; fir != null; fir=fir.next){
			cop.append(fir.data);
		}
		return cop;
	} 
	
}