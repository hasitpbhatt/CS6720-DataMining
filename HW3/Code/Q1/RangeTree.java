import java.util.ArrayList;

/**
 * Assumes the points inserted are in ascending order
 * 
 * @author Hasit Bhatt
 *
 */
public class RangeTree {
	ArrayList<RangeSearch> allXRS;
	ArrayList<Double> allX;
	int size;

	RangeTree() {
		allXRS = new ArrayList<RangeSearch>();
		allX = new ArrayList<Double>();
		size = 0;
	}

	public RangeTree(ArrayList<Point> points) {
		this();
		for (Point p : points)
			insert(p);
	}

	public void insert(Point p) {
		int index = binarySearch(p.x, 0, allX.size());
		//System.out.println("...." + index);
		if(index < 0) {
			allX.add(-index, p.x);
			allXRS.add(-index, new RangeSearch(p.x,p));
		}
		else {
			if((index<size) && (allX.get(index)==p.x)) {
				//System.out.println("////");
				allXRS.get(index).insert(p);
				size--;
			}
			else {
				//System.out.println("////\\\\");
				allX.add(index, p.x);
				allXRS.add(index, new RangeSearch(p.x,p));
			}
		}
		size++;
	}

	private int binarySearch(double x, int start, int end) {
		int mid = (start + end) / 2;
		if(start > end) {
			if(end >= size){
				return -size;
			}
			if(end < 0)
				return 0;
			if(allX.get(end) > x) {
				if(end == 0) return end;
				return end-1;
			}
			else if(allX.get(end) < x) {
				return end+1;
			}
			return -end;
		}
		if(mid >= size)
			return -size;
		if (x > allX.get(mid)) {
			return binarySearch(x, mid + 1, end);
		} else if (x < allX.get(mid)) {
			return binarySearch(x, start, mid-1);
		} else
			return mid;
	}

	public void rangeSearch(MyQueue neighbours, Point pa, double epsilon, double xMin, double xMax, double yMin, double yMax) {
		int index = binarySearch(xMin, 0, size);
		if((index <0) || (index>=size))
			return;
		for(int i=index;i<size;i++) {
			double x = allX.get(i);
			if(x > xMax)
				return;
			if(x >= xMin) {
				allXRS.get(i).rangeSearch(neighbours, pa, epsilon, yMin, yMax);
			}
		}
	}
	
	public ArrayList<Point> rangeSearch(double xMin, double xMax, double yMin, double yMax) {
		ArrayList<Point> answerPoints = new ArrayList<Point>();
		int index = binarySearch(xMin, 0, size);
		if((index <0) || (index>=size))
			return answerPoints;
		for(int i=index;i<size;i++) {
			double x = allX.get(i);
			if(x > xMax)
				return answerPoints;
			if(x >= xMin) {
				answerPoints.addAll(allXRS.get(i).rangeSearch(yMin, yMax));
			}
		}
		return answerPoints;
	}

	public void rangeSearch(MyQueue neighbours, Point p, double epsilon) {
		rangeSearch(neighbours, p, epsilon, p.x-epsilon, p.x+epsilon, p.y-epsilon, p.y+epsilon);
	}
	
	

}
