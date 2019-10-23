# A simple Makefile for the Queens program by Michael Quan and Daniel Lung
# Michael Quan + Daniel Lung
# midquan + dlung 
# Programming Assignment 5
# Solves the n-Queens problem given an input of size of board
Queens: Queens.class
	echo Main-class: Queens > Manifest
	jar cvfm Queens Manifest Queens.class
	rm Manifest
	chmod u+x Queens

Queens.class: Queens.java
	javac -Xlint Queens.java

clean:
	rm -f Queens.class Queens

submit: Makefile Queens.java 
	submit cmps012a-pt.f15 pa5 Makefile Queens.java
