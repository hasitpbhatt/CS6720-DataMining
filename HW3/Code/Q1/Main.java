import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	ArrayList<Point> points;
	
	boolean getInput(String fileName, int threshold) {
		File file = new File(fileName);
		double a, b;
		try {
			Scanner scanner = new Scanner(file);
			points = new ArrayList<Point>();
			int cnt = 0;
			while(scanner.hasNextDouble() && (cnt < threshold)) {
				a = scanner.nextDouble();
				b = scanner.nextDouble();
				points.add(new Point(cnt, a, b));
				cnt++;
			}
			scanner.close();
		}
		catch ( Exception e) {
			return false;
		}
		return true;
	}
	
	public static void main(String[] args) {
		
		Main main = new Main();
		
		String fileName = "output.dat";
		int threshold = 200000;
		//String fileName = "my.dat";
		if(args.length != 0) {
			fileName = args[0];
		}
		boolean flag = false;
		if(args.length >= 2) {
			if(Integer.parseInt(args[1]) == 1)
				flag = true;
			else
				flag = false;
		}
		if(args.length == 3) {
			threshold = Integer.parseInt(args[2]);
		}
		if(main.getInput(fileName, threshold)) {
			System.err.println("" + flag);
			OPTICS optics = new OPTICS(main.points,flag);
			optics.process(10, 10);
		}
	}
}
