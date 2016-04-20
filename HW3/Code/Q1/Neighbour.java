
public class Neighbour implements Comparable<Neighbour>{
	Point point;
	double distance;
	
	public Neighbour() {
	}
	
	Neighbour(double distance, Point p) {
		this.distance = distance;
		point = p;
	}

	@Override
	public int compareTo(Neighbour o) {
		if(distance-o.distance < 0)
			return -1;
		else if(distance == o.distance) {
			return 0;
		}
		else {
			return 1;
		}
	}
}
