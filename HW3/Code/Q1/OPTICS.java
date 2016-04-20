import java.util.ArrayList;
import java.util.Collections;

public class OPTICS {
	static ArrayList<Point> points;
	ArrayList<Neighbour> neighbours;
	int cnt;
	boolean flag = false;
	RangeTree rTree;

	public OPTICS() {
		cnt = 0;
	}
	
	public OPTICS(ArrayList<Point> p) {
		this(p,false);
	}

	public OPTICS(ArrayList<Point> p, boolean flag) {
		points = p;
		cnt = 0;
		neighbours = new ArrayList<Neighbour>();
		if(flag) {
			//Collections.sort(points);
			rTree = new RangeTree(points);
		}
		for(Point i : points) {
			neighbours.add(new Neighbour(Double.MAX_VALUE, i));
		}
		this.flag = flag;
	}

	/**
	 * 
	 * @param epsilon epsilon
	 * @param minPoints Minimum number of points
	 */
	public void process(double epsilon, int minPoints) {
		long s1 = System.currentTimeMillis();
		int n = points.size();
		cnt = 0;
		//for (int i = 0; i < 1; i++) {
		for (int i = 0; i < n; i++) {
			if (!points.get(i).isProcessed()) {
				//System.out.println("Processing: " + i);
				expandClusterOrder(points.get(i), epsilon, minPoints);
			}
		}
		long s2 = System.currentTimeMillis();
		System.out.println("Time taken: " + (s2-s1));
	}

	private void expandClusterOrder(Point p, double epsilon, int minPoints) {
		Point point = p;
		MyQueue neighbours = getNeighbours(point, epsilon);
		MyQueue orderSeeds = new MyQueue();
		point.processed = true;
		point.setCoreDistance(neighbours, epsilon, minPoints);
		//System.out.println(point.reachabilityDistance);
		System.out.println(epsilon);
		//System.out.println(++cnt);
		if (point.coreDistance != Double.MAX_VALUE) {
			update(orderSeeds, neighbours, point);
			while (!orderSeeds.isEmpty()) {
				point = orderSeeds.poll().point;
				neighbours = getNeighbours(point, epsilon);
				point.processed = true;
				point.setCoreDistance(neighbours, epsilon, minPoints);
				//System.out.println(point);
				System.out.println(point.reachabilityDistance);
				//System.out.println(++cnt);
				if (point.coreDistance != Double.MAX_VALUE) {
					update(orderSeeds, neighbours, point);
				}
			}
		}
	}

	private void update(MyQueue orderSeeds, MyQueue neighbours, Point point) {
		double coreDistance = point.coreDistance;
		while (!neighbours.isEmpty()) {
			Point neighbourPoint = neighbours.poll().point;
			if (!neighbourPoint.processed) {
				double newReachabilityDistance = Math.max(coreDistance, point.distance(neighbourPoint));
				if (neighbourPoint.reachabilityDistance == Double.MAX_VALUE) {
					neighbourPoint.reachabilityDistance = newReachabilityDistance;
					orderSeeds.add(this.neighbours.get(neighbourPoint.id));
				} else if (newReachabilityDistance < neighbourPoint.reachabilityDistance) {
					neighbourPoint.reachabilityDistance = newReachabilityDistance;
					this.neighbours.get(neighbourPoint.id).distance = newReachabilityDistance;
				}
			}
		}
	}

	private MyQueue getNeighbours(Point p, double epsilon) {
		MyQueue neighbours = new MyQueue();
		if(!flag) {
			int object_size = points.size();
			for (int i = 0; i < object_size; i++) {
				double d = p.distance(points.get(i));
				//System.out.println("..." + d);
				if (d <= epsilon)
					neighbours.add(new Neighbour(d, points.get(i)));
			}
		}
		else {
			rTree.rangeSearch(neighbours,p,epsilon);
			//ArrayList<Point> z = rTree.rangeSearch(p.x-epsilon-0.1, p.x+epsilon+0.1, p.y-epsilon-0.1, p.y+epsilon+0.1);
			//for(Point i : z) {
			//	double d = p.distance(i);
			//	if (d <= epsilon)
			//		neighbours.add(new Neighbour(d, i));
			//}
		}
		return neighbours;
	}

}