import java.sql.*;
import java.io.*;
import java.util.*;

/**
 * A class that connects to PostgreSQL and disconnects.
 * You will need to change your credentials below, to match the usename and password of your account
 * in the PostgreSQL server.
 * The name of your database in the server is the same as your username.
 * You are asked to include code that tests the methods of the TaxesApplication class
 * in a similar manner to the sample RunStoresApplication.java program.
*/


public class RunTaxesApplication
{
    public static void main(String[] args) {
    	
    	Connection connection = null;
    	try {
    	    //Register the driver
    		Class.forName("org.postgresql.Driver"); 
    	    // Make the connection.
            // You will need to fill in your real username
            // and password for your Postgres account in the arguments of the
            // getConnection method below.
            connection = DriverManager.getConnection(
                                                     "jdbc:postgresql://cmps180-db.lt.ucsc.edu/midquan",
                                                     "midquan",
                                                     "omgomgom180");
            
            if (connection != null)
                System.out.println("Connected to the database!");

            /* Include your code below to test the methods of the TaxesApplication class
             * The sample code in RunStoresApplication.java should be useful.
             * That code tests other methods for a different database schema.
             * Your code below: */
            
			/*
			*Output of getIRSagentsWithManyDelinquents
			*when the parameter numberOfDelinquents is 2.
			output here
			*/
			TaxesApplication app = new TaxesApplication(connection);
			
			int numberOfDelinquents = 2;
			List<Integer> delinquents = app.getIRSagentsWithManyDelinquents(numberOfDelinquents);
			for(Integer delinquent : delinquents){
				System.out.println(delinquent);
			}
				
			
			/*
			*Output of increaseTaxOwed when the increment is 125.00
			output here
			*/
			float taxincrease = 125.00; 
			System.out.println("Number of tax increased = " + app.increaseTaxOwed("843 Ante Ave",taxincrease));
				
            /*******************
            * Your code ends here */
            
    	}
    	catch (SQLException | ClassNotFoundException e) {
    		System.out.println("Error while connecting to database: " + e);
    		e.printStackTrace();
    	}
    	finally {
    		if (connection != null) {
    			// Closing Connection
    			try {
					connection.close();
				} catch (SQLException e) {
					System.out.println("Failed to close connection: " + e);
					e.printStackTrace();
				}
    		}
    	}
    }
}
