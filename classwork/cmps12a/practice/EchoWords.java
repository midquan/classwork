import java.util.Scanner;
class EchoWords {
	public static void main(String [] args){
		Scanner sc = new Scanner(System.in);
		String str = sc.next();
		while(!(str.equals("galumph"))){
		    System.out.println(str);
		    str = sc.next();
		}
		System.out.println("bye!");
	}
}