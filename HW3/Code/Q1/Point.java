
public class Point implements Comparable<Point>{
	int id;
	double x,y;
	boolean processed;
	double reachabilityDistance;
	double coreDistance;
	
	Point(int id,double a, double b) {
		this.id = id;
		x = a;
		y = b;
		processed = false;
		reachabilityDistance = Double.MAX_VALUE;
	}
	
	public boolean isProcessed() {
		return processed;
	}

	public double distance(Point point) {
		return Math.sqrt((point.x-x)*(point.x-x)+(point.y-y)*(point.y-y));
	}

	public double setCoreDistance(MyQueue neighbours, double epsilon, int minPoints) {
		double coreDistance = Double.MAX_VALUE;
		if(neighbours.size() >= minPoints) {
				int n = minPoints;
				MyQueue tmpQueue = new MyQueue();
				while(n-- > 0) {
					tmpQueue.add(neighbours.poll());
				}
				while(!tmpQueue.isEmpty()) {
					coreDistance = tmpQueue.peek().distance;
					neighbours.add(tmpQueue.poll());
				}
				return coreDistance;
		}
		return coreDistance;
	}
	
	public String toString() {
		return ""+x+ " " + y;
	}

	@Override
	public int compareTo(Point o) {
		if(o.x == x) {
			if(y < o.y) {
				return -1;
			}
			else if(y > o.y) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if(o.x < x){
			return 1;
		}
		else 
			return -1;
	}
}
