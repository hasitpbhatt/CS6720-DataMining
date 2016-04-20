import java.util.ArrayList;

public class RangeSearch {
	ArrayList<Double> allY;
	ArrayList<Point> allPoints;
	int size;
	double X;
	
	public RangeSearch(double x,Point p) {
		this();
		X = x;
		insert(p);		
	}  
	
	RangeSearch() {
		allY = new ArrayList<Double>();
		allPoints = new ArrayList<Point>();
		size=0;
	}

	public void insert(Point p) {
		int index = binarySearch(p.y,0,size);
		if(index < 0) {
			allY.add(-index, p.y);
			allPoints.add(-index, p);
		}
		else if(index<size) {
				allY.add(index, p.y);
				allPoints.add(index, p);
		}
		else if(index == 0) {
			allY.add(index, p.y);
			allPoints.add(index, p);
		}
		else {
			System.out.println("Be aa shu thai gyu");
		}
		size++;
 		//System.out.println("Inserted" + X + " " + p.y + " " + size+ " " + allPoints.size());
	}
	
	public void rangeSearch(MyQueue neighbours, Point pa, double epsilon, double yMin, double yMax) {
		int index = binarySearch(yMin, 0, size);
		if((index <0) || (index>=size))
			return;
		for(int i=index;i<size;i++) {
			double x = allY.get(i);
			if(x > yMax)
				return;
			if(x >= yMin) {
				double d = allPoints.get(i).distance(pa);
				if(d <= epsilon)
					neighbours.add(new Neighbour(d,allPoints.get(i)));
			}
		}
	}
	
	public ArrayList<Point> rangeSearch(double yMin, double yMax) {
		ArrayList<Point> answerPoints = new ArrayList<Point>();
		int index = binarySearch(yMin, 0, size);
		if((index <0) || (index>=size))
			return answerPoints;
		for(int i=index;i<size;i++) {
			double x = allY.get(i);
			if(x > yMax)
				return answerPoints;
			if(x >= yMin) {
				answerPoints.add(allPoints.get(i));
			}
		}
		return answerPoints;
	}
	
	private int binarySearch(double x, int start, int end) {
		int mid = (start + end) / 2;
		if(start > end) {
			if(end >= size){
				return -size;
			}
			if(end < 0)
				return 0;
			if(allY.get(end) > x) {
				if(end == 0) return end;
				return end-1;
			}
			else if(allY.get(end) < x) {
				return end+1;
			}
			return -end;
		}
		if(mid >= size)
			return -size;
		try {
		double r = allY.get(mid);
		}
		catch (Exception e) {
			System.out.println(X);
			System.out.println(x);
			System.out.println(mid);
			System.out.println(size);
			throw e;
		}
		if (x > allY.get(mid)) {
			return binarySearch(x, mid + 1, end);
		} else if (x < allY.get(mid)) {
			return binarySearch(x, start, mid-1);
		} else
			return mid;
	}

}
