// Lawn.java
// Michael Quan
// midquan
// Programing Assignment 1
// Calculates area of lot vs house and mowing speed vs lawn area
import java.util.Scanner;
class Lawn{
	public static void main(String [] Args){
		Scanner sc = new Scanner(System.in);
		double lengthlot, widthlot, lengthhouse, widthhouse, area, rate;
		int totsec, hour, minutes, seconds;
		String hr, min, sec;
		final int MIN_IN_HOUR = 60;
		final int SECONDS_IN_MIN = 60;
		final int SECONDS_IN_HOURS = 3600;
		
		System.out.print("Enter the length and width of the lot, in feet: ");
		lengthlot = sc.nextDouble();
		widthlot = sc.nextDouble();
		System.out.print("Enter the length and width of the house, in feet: ");
		lengthhouse = sc.nextDouble();
		widthhouse = sc.nextDouble();
		
		area = (lengthlot*widthlot) - (lengthhouse*widthhouse);
		
		System.out.println("The lawn area is " + area + " square feet.");
		System.out.print("Enter the mowing rate, in square feet per second: ");
		rate = sc.nextDouble();
		
		totsec = (int)Math.round(area/rate);
		hour = totsec /SECONDS_IN_HOURS;
		minutes = (totsec % SECONDS_IN_HOURS) / MIN_IN_HOUR;
		seconds = (totsec % SECONDS_IN_HOURS) % SECONDS_IN_MIN;
		
		hr = (hour == 1 ? " hour, " : " hours, ");
		min = (minutes == 1 ? " minute, and " : " minutes, and ");
		sec = (seconds == 1 ? " second." : " seconds.");
		
		System.out.println("The mowing time is " + hour + hr + minutes + min + seconds + sec);
	} 
} 