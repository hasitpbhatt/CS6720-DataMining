import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int numberOfDimensions = scanner.nextInt();
		
		ArrayList<Point> points = new ArrayList<Point>();
		
		for(int i=0;i<1000;i++) {
			points.add(new Point(numberOfDimensions));
		}
		
		for(int i=0;i<1000;i++) {
			for(int j=0;j<1000;j++) {
				System.out.println(points.get(i).angle(points.get(j)));
			}
		}
		scanner.close();

	}
}
