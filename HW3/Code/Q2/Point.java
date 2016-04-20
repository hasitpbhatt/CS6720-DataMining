import java.util.ArrayList;

public class Point {
	ArrayList<Double> dimensions;
	
	public Point() {
		dimensions = new ArrayList<Double>();
	}
	
	public Point(int n) {
		this();
		for(int i=0;i<n;i++) {
			dimensions.add(Math.random()*2-1);
		}
	}
	
	public String toString() {
		String s = "";
		for(double i : dimensions)
			s += i + " ";
		return s;
	}
	
	double get(int index) {
		return dimensions.get(index);
	}
	
	public double angle(Point p) {
		double dotProduct = 0;
		int n = Math.min(p.size(), size());
		for(int i=0;i<n;i++) {
			dotProduct += p.get(i)*get(i);
		}
		if(dotProduct == 0)
			return Math.acos(0);
		if(modValue() != 0)
			dotProduct /= modValue();
		if(p.modValue() != 0)
			dotProduct /= p.modValue();
		if(dotProduct > 1)
			dotProduct = 1;
		return Math.acos(dotProduct)*180/Math.PI;
	}
	
	public int size() {
		return dimensions.size(); 
	}
	
	double modValue() {
		double val = 0;
		int n = size();
		for(int i=0;i<n;i++) {
			val += Math.pow(dimensions.get(i),2);
		}
		return Math.sqrt(val);
	}
}
